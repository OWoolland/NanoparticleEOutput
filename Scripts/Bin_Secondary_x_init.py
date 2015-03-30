import csv
import sys, getopt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
from pylab import *

### Take command line parameters
def main(argv): 
  try:
    opts, args = getopt.getopt(argv,"hi:t:c:",["ifile=","title=","csv="])
  except getopt.GetoptError:
    print('You buggered it: Bin_Secondary_x_init.py -i <inputfile> -t <title> -c')
    sys.exit(2)
    
  csvBool = False
  for opt, arg in opts:
    if opt == '-h':
      print('Bin_Secondary_init.py -i <inputfile> -t <title> -c')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg
    elif opt in ("-c", "--csv"):
      csvBool = True

  ### Import data

  data = np.genfromtxt(inputfile,delimiter=",")

  ### Extract particle types

  particle = data[:,7]
  
  ### Select electrons

  data = data[particle == 1]

  ### Extract initial positions

  x = data[:,1]
  process = data[:,8]
  x_init = x[process==1]

  ### Find plot scaling

  min_depth = np.amin((x_init))
  max_depth = np.amax(x_init)
  dif_depth = max_depth - min_depth

  ### Binning data 

  #x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth)/100)
  
  ### Sum in bins
  hist_x, edges = np.histogram(x_init,bins=50)#, bins=x_bins)

  ### plotting

  plot = plt.plot(hist_x, 'ro-')

  plt.xlabel('Depth (100um)')
  plt.ylabel('Count')
  plt.title(title)
  
  plt.show()

  odata = zip(*np.histogram(x_init,bins=50))
  np.savetxt('Bin_Secondary_x_init.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
