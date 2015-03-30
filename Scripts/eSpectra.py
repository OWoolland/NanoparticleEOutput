import csv
import sys, getopt
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from pylab import *

### Take command line parameters
def main(argv): 
  try:
    opts, args = getopt.getopt(argv,"hi:t:",["ifile=","title="])
  except getopt.GetoptError:
    print('eSpectra.py <inputfile>')
    sys.exit(2)
    
  for opt, arg in opts:
    if opt == '-h':
      print('eSpectra.py -i <inputfile> -t <title>')
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
  Edep =data[:,4]
  Energy = data[:,5]
  Time = data[:,6]
  Particle = data[:,7]
  Process = data[:,8]

  electron_id = ParticleID[Particle==1]
  electron_energy = Energy[Particle==1]
  electron_time = Time[Particle==1]
  electron_process = Process[Particle==1]

  electron_energy_init = electron_energy[electron_process==1] # if init_step
  hist1 = plt.hist(electron_energy_init[electron_energy_init<10000],20)
  
  plt.xlabel('Energy (eV)')
  plt.ylabel('Count')
  plt.title(title)

  plt.show()

### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
