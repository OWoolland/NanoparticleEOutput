import csv
import sys, getopt
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
from pylab import *

### Take command line parameters
def main(argv): 
  try:
    opts, args = getopt.getopt(argv,"hi:t:",["ifile=","title="])
  except getopt.GetoptError:
    print('Bin_eDeps_x.py -i <inputfile> -t <title>')
    sys.exit(2)
    
  for opt, arg in opts:
    if opt == '-h':
      print('Bin_eDeps_x.py -i <inputfile> -t <title>')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg

  data = np.genfromtxt(inputfile,delimiter=",")

  ParticleID = data[:,0]
  x = data[:,1]
  y = data[:,2]
  z = data[:,3]
  edep =data[:,4]
  Energy = data[:,5]
  Time = data[:,6]
  Particle = data[:,7]

  # Remove elastic interactions?
  x = x[edep>0.1]
  edep = edep[edep>0.1]

  ### Binning perameters
  min_depth = np.amin(x)
  max_depth = np.amax(x)
  dif_depth = max_depth - min_depth

  ### Binning data 
  x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth)/100)
  
  ### Sum in bins
  hist_x, edges = np.histogram(x, bins=x_bins, weights=edep)
  
  ### plotting
  plt.plot(hist_x, 'ko-')

  xlow,xhigh,ylow,yhigh = plt.axis()
  plt.axis((xlow,xhigh,ylow,yhigh))
  
  plt.xlabel('Depth (100um)')
  plt.ylabel('Energy Deposition (eV)')
  plt.title(title)

  plt.show()

  odata = zip(*np.histogram(x,bins=x_bins))
  np.savetxt('Bin_eDeps_x.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
