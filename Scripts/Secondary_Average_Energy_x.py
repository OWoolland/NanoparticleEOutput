import csv
import sys, getopt
import numpy as np
#import matplotlib.pyplot as plt
#from pylab import *

### Take command line parameters
def main(argv): 
  try:
    opts, args = getopt.getopt(argv,"hi:t:c:",["ifile=","title=","csv="])
  except getopt.GetoptError:
    print('You buggered it: Secondary_Average_Energy_x.py -i <inputfile> -t <title> -c')
    sys.exit(2)
    
  csvBool = False
  for opt, arg in opts:
    if opt == '-h':
      print('Secondary_Average_Energy_x.py -i <inputfile> -t <title> -c')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg
    elif opt in ("-c", "--csv"):
      csvBool = True

  ### Import data

  data = np.genfromtxt(inputfile,delimiter=",")

  ### Extract particle types and creation process
  ### Select electrons and first steps

  particle = data[:,7]
  data = data[particle == 1]
  del particle

  process = data[:,8]
  data = data[process == 1]
  del process

  ### Extract initial energies

  x = data[:,1]
  energy = data[:,5]

  del data

  ### Find plot scaling

  min_depth = np.amin(x)
  max_depth = np.amax(x)
  dif_depth = max_depth - min_depth

  ### Binning data 

#  x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth)/100)
  x_bins = np.linspace(min_depth, max_depth, num=500)
  
  ### Sum in bins
  hist_energy_total, edges = np.histogram(x, bins=x_bins, weights=energy)
  del energy

  hist_energy_count, edges = np.histogram(x, bins=x_bins)
  del x

  hist_energy_average = np.true_divide(hist_energy_total,hist_energy_count) 
  del hist_energy_total
  del hist_energy_count

  ### plotting

#  plot = plt.plot(edges[1:np.size(edges)], hist_energy_average, 'ro-')

#  plt.xlabel('Depth (um)')
#  plt.ylabel('Average Energy (eV)')
#  plt.title(title)
  
#  plt.show()

  odata = hist_energy_average
  np.savetxt('Secondary_Average_Energy_x.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
