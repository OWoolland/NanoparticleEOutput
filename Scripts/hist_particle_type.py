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
      print('hist_particle_type.py -i <inputfile> -t <title>')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      inputfile = arg
    elif opt in ("-t", "--title"):
      title = arg

  ### Import data

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

  # filter particle 
  Particle=Particle[Process==1]

  fig = plt.figure()
  ax = fig.add_subplot(211)

  #plt.subplot(211)
  plt.yscale('log')
  hist1 = ax.hist(Particle,bins=[1,2,3,4,5,6])
  locs, labels = xticks([1.5,2.5,3.5,4.5,5.5], ['Electron','Proton','Generic Ion','Gamma','Positron'])
  ## label bars with values
  outstr = 'Electron: %s\nProton: %s\nGeneric Ion: %s\nGamma: %s\nPositron: %s'%(hist1[0][0],hist1[0][1],hist1[0][2],hist1[0][3],hist1[0][4])
  ax.text(0.7,0.9,outstr,horizontalalignment='left',verticalalignment='top',transform=ax.transAxes,bbox={'facecolor':'white', 'pad':10})

  plt.ylabel('Count')
  plt.title('Particle Breakdown')

  ax2 = fig.add_subplot(212)
  plt.yscale('log')
  plt.xticks(rotation=70)
  hist2 = ax2.hist(Process,bins=[1,2,3,4,5,6,7,8,9,10,11,12,13])
  locs, labels = xticks([1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5], ['Inital\nStep','Multiple\nScattering','Hadron\nIonization','Electron\nIonization','Transportation','Electron\nBremsstrahlung','Compton\nScattering','Photoelectric\nAbsorbtion','Rayleigh\nScattering','Gamma\nConversion','Annihilation','Final\nStep'])
  ## label bars with values
  outstr = 'Initial Step: %s\nMultiple Scattering: %s\nHadron Ionization: %s\nElectron Ionization: %s\nTransportation: %s\nElectron Bremsstrahlung: %s\nCompton Scattering: %s\nPhotoelectric Absorbtion: %s\nRayleigh Scattering: %s\nGamma Conversion: %s\nAnihilation: %s\nFinal Step: %s'%(hist2[0][0],hist2[0][1],hist2[0][2],hist2[0][3],hist2[0][4],hist2[0][5],hist2[0][6],hist2[0][7],hist2[0][8],hist2[0][9],hist2[0][10],hist2[0][11])
  ax2.text(0.7,0.9,outstr,horizontalalignment='left',verticalalignment='top',transform=ax2.transAxes,bbox={'facecolor':'white', 'pad':10})

  plt.ylabel('Count')
  plt.title('Process Breakdown')

  #plt.suptitle('Breakdown of Particles and Processes [1000, 10MeV Photons]')
  plt.suptitle(title)

  #plt.show()  
  
### Class declarations
if __name__ == "__main__":
  main(sys.argv[1:])
