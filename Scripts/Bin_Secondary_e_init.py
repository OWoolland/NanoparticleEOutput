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
    print('You buggered it: Bin_Secodnary_e_init.py -i <inputfile> -t <title> -c')
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
  E = data[:,5]
  process = data[:,8]
  E_init = E[process==1]
  x_init = x[process==1]
  
  ### Sum in bins
  hist_E, edges = np.histogram(x_init,bins=50,weights=E_init)
  hist_n, edges = np.histogram(x_init,bins=50)

  hist_avg = np.true_divide(hist_E,hist_n)

  ### plotting

  plot = plt.plot(hist_avg, 'ro-')

  plt.xlabel('Depth (100um)')
  plt.ylabel('Count')
  plt.title(title)
  
  plt.show()

  odata = zip(hist_avg,edges[1:])
  np.savetxt('Bin_Secodnary_e_init.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
