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
    print('Bin_Energy_x.py -i <inputfile> -t <title>')
    sys.exit(2)
    
  title = "no title specified"
  for opt, arg in opts:
    if opt == '-h':
      print('Bin_Energy_x.py -i <inputfile> -t <title>')
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

  proton_x = x[Particle == 2]+10000
  proton_energy = Energy[Particle == 2]

  proton_energy = proton_energy[proton_x>0]
  proton_x = proton_x[proton_x>0]

  ### Binning perameters
  min_depth = np.amin(proton_x)
  max_depth = np.amax(proton_x)
  dif_depth = max_depth - min_depth

  ### Binning data 
  #x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth)/500)
  
  ### Sum in bins
  hist_x, edges = np.histogram(proton_x, bins=75, weights=proton_energy)
  hist_n, edges = np.histogram(proton_x, bins=75)

  #edges = edges[hist_n>0]
  hist_x_avg = hist_x[hist_n>0]/hist_n[hist_n>0]
  edges = edges[hist_n>0]

  ### plotting
  plt.plot(edges,hist_x_avg, 'ko-')

  xlow,xhigh,ylow,yhigh = plt.axis()
  plt.axis((xlow,xhigh,ylow,yhigh))
  
  plt.xlabel('Depth (um)')
  plt.ylabel('Energy (eV)')
  plt.title(title)

  plt.show()

  print('3db point is: %.2e ' % (0.707*np.amax(hist_x_avg)))

  odata = zip(hist_x_avg,edges)
  np.savetxt('Bin_Energy_x.csv', odata, delimiter=',')

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
