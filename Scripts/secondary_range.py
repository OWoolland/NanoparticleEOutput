import sys, getopt
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from pylab import *

### Take command line parameters
def main(argv): 
  try:
    opts, args = getopt.getopt(argv,"hi:",["ifile="])
  except getopt.GetoptError:
    print('test.py <inputfile>')
    sys.exit(2)
    
  for opt, arg in opts:
    if opt == '-h':
      print('secondary_range.py -i <inputfile>')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg

  ### Import data

  data = np.genfromtxt(inputfile,delimiter=",")

  ### Extract particle types

  particle = data[:,7]

  ### Select electrons

  data_electrons = data[particle==1]

  ### Extract initial and final positions 

  id = data_electrons[:,0]
  x = data_electrons[:,1]
  process = data_electrons[:,8]

  ### cleanup
  
  del data
  del data_electrons

  ### find starting and finishing positions

  x_init = x[process==1]
  x_fin = x[process==12]

  x_init_id = id[process==1]
  x_fin_id = id[process==12]

  # filter repeated starts or stops
  x_init_id, unique_index = np.unique(x_init_id,return_index=True)
  x_init = x_init[unique_index]

  x_fin_id, unique_index = np.unique(x_fin_id,return_index=True)
  x_fin = x_fin[unique_index]
  
  # filter starts without stops and vice versa

  x_init = x_init[np.in1d(x_init_id,x_fin_id)]
  x_init_id = x_init_id[np.in1d(x_init_id,x_fin_id)]

  x_fin = x_fin[np.in1d(x_fin_id,x_init_id)]
  x_fin_id = x_fin_id[np.in1d(x_fin_id,x_init_id)]

  # sort the arrays by id

  x_init_sorted = x_init[np.argsort(x_init_id)] # sort by id
  x_fin_sorted = x_fin[np.argsort(x_fin_id)] 
    
  ### 1 D approx of range
    
  ranges = x_fin_sorted - x_init_sorted
  ranges = np.absolute(ranges)

  # bodging away the weird data
  ranges = ranges[ranges<0.1]

  # removing local energy deposit events
#  ranges = ranges[ranges!=0]

  ### Find plot scaling

  min_depth = np.amin(ranges)
  max_depth = np.amax(ranges)
  dif_depth = max_depth - min_depth

  ### Binning data 

 #x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth))

  ### Sum in bins
  hist_ranges, edges = np.histogram(ranges)

  ### plotting

  fig = plt.figure()
  ax = fig.add_subplot(111)
    
  #plt.yscale('log')
  hist1 = ax.hist(ranges)
  plt.xlabel('Range (um)')
  plt.ylabel('Count')
  plt.title('Scondary Electron Ranges [1000, 100keV Photons]')
    
  plt.show()

  odata = zip(hist_ranges,edges[1:])
  np.savetxt('secondary_range_nm.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
