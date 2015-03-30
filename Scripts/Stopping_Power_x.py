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
    print('Stopping_Power_x.py -i <inputfile> -t <title>')
    sys.exit(2)
    
  title = "no title entered"
  for opt, arg in opts:
    if opt == '-h':
      print('Stopping_Power_x.py -i <inputfile> -t <title>')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg

  data = np.genfromtxt(inputfile,delimiter=",")

  ParticleID = data[:,0]
  x = data[:,1]
  edep =data[:,4]
  Particle = data[:,7]

  # Remove elastic interactions?
  ParticleID = ParticleID[edep>0.1]
  x = x[edep>0.1]
  edep = edep[edep>0.1]
  Particle = Particle[edep>0.1]

  indexes=np.argsort(np.unique(ParticleID)) # sort all by id
  ParticleID = ParticleID[indexes]
  x = x[indexes]
  edep = edep[indexes]
  Particle = Particle[indexes]

  # remove local edep 
  stopping_power = np.true_divide(edep[1:][diff(x)>0],diff(x)[diff(x)>0])
  x = x[diff(x)>0]

  ### Binning perameters
  min_depth = np.amin(x)
  max_depth = np.amax(x)
  dif_depth = max_depth - min_depth

  ### Binning data 
#  x_bins = np.linspace(min_depth, max_depth, num=100)
  
  ### Sum in bins
  hist_x, edges = np.histogram(x, bins=100, weights=stopping_power)
  
  ### plotting
  plt.plot(edges[1:]+10000, hist_x, 'ko-')

  xlow,xhigh,ylow,yhigh = plt.axis()
  plt.axis((xlow,xhigh,ylow,yhigh))
  
  plt.xlabel('Depth (um)')
  plt.ylabel('Stopping Power (eV/um)')
  plt.title(title)

  plt.show()

  odata = zip(hist_x,edges[1:]+10000)
  np.savetxt('Stopping_Power_x.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
