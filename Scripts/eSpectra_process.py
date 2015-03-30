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
    print('eSpectra_process.py <inputfile>')
    sys.exit(2)
    
  for opt, arg in opts:
    if opt == '-h':
      print('eSpectra_process.py -i <inputfile> -t <title>')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg

  data = np.genfromtxt(inputfile,delimiter=",")

  Energy = data[:,5]
  Particle = data[:,7]
  Process = data[:,8]
  Creator_Process = data[:,9]

  electron_energy = Energy[Particle==1]
  electron_process = Process[Particle==1]
  electron_creator_process = Creator_Process[Particle==1]

  # create 3d array of data
## this will not work because the creator process will always be init step
  electron_energy_init = electron_energy[electron_process==1] # if init_step
  electron_energy_init_process = electron_creator_process[electron_process==1] # if init_step

  min_energy = np.amin(electron_energy_init)
  max_energy = np.amax(electron_energy_init)
  dif_energy = max_energy - min_energy

  ### Binning data 

  x_bins = np.logspace(np.log10(min_energy), np.log10(max_energy))
  plt.xscale('log') 
  plt.yscale('log')

  labels = ("","Initial Step","Multiple Scattering","Hadron Ionizatopm","Electron Ionization","Transportation","Electron Bremsstrahlung","Compton Scattering","Photoelectric Effect","Rayleigh Scattering","Gamma Conversion","Annihilation","Final Step");
  electron_energy_init_by_process=[]
  for i in range(1,13):
    if electron_energy_init[electron_energy_init_process==i].any()!=0:
      plt.hist(electron_energy_init[electron_energy_init_process==i],bins=x_bins,alpha=0.5,label=labels[i])
 
  plt.xlabel('Energy (eV)')
  plt.ylabel('Count')
  plt.title(title)

  plt.legend()

  plt.show()

  hist_process, edges = np.histogram(electron_energy_init_process, bins=[1,2,3,4,5,6,7,8,9,10,11,12,13])
  odata = zip(hist_process,labels)
  np.savetxt('eSpectra_process.csv', odata, delimiter=',')


### Class declarations

if __name__ == "__main__":
  main(sys.argv[1:])
