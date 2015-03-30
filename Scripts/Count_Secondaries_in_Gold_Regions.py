### no current implimentatin of volume reporting
### based on hardcoded coordinates

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

  ### Find those in the first gold section
  
  x_g1 = x_init[(x_init>-10)&(x_init<10)]
  x_g2 = x_init[(x_init>4090)&(x_init<5010)]
  x_g3 = x_init[(x_init>7090)&(x_init<8010)]
  x_g4 = x_init[(x_init>8390)&(x_init<8410)]
  x_w = x_init[(x_init>-5100)&(x_init<-4900)]

  print(np.size(x_g1))
  print(np.size(x_g2))  
  print(np.size(x_g3))
  print(np.size(x_g4))
  print(np.size(x_w))

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
