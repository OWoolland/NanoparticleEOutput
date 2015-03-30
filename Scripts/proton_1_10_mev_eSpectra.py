import numpy as np
import matplotlib.pyplot as plt
import csv

##
### 1 MeV
##

data = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_gold.csv",delimiter=",")

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

plt.subplot(2, 2, 1)
electron_energy_init = electron_energy[electron_process==1] # if init_step
hist1 = plt.hist(electron_energy_init[electron_energy_init<10000],20)

#plt.xlabel('Energy (eV)')
plt.ylabel('Count')
plt.title('<10keV Zoom [1000, 1MeV Protons]')

plt.subplot(2, 2, 2)

plt.xscale('log')
plt.yscale('log')

electron_energy_init = electron_energy[electron_process==1] # if init_step
hist1 = plt.hist(electron_energy_init, np.logspace(np.log10(np.amin(electron_energy_init)),np.log10(np.amax(electron_energy_init)),num=50))

#plt.xlabel('Energy (eV)')
plt.ylabel('Count')
plt.title('[1000, 1MeV Protons]')
##
### 10 MeV
##

data = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_10mev_gold.csv",delimiter=",")

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

plt.subplot(2, 2, 3)
electron_energy_init = electron_energy[electron_process==1] # if init_step
hist2 = plt.hist(electron_energy_init[electron_energy_init<10000],20)

plt.xlabel('Energy (eV)')
plt.ylabel('Count')
plt.title('<10keV Zoom [1000, 10MeV Protons]')

plt.subplot(2, 2, 4)
plt.xscale('log')
plt.yscale('log')

electron_energy_init = electron_energy[electron_process==1] # if init_step
#electron_energy_init = np.log10(electron_energy_init)
hist2 = plt.hist(electron_energy_init, np.logspace(np.log10(np.amin(electron_energy_init)),np.log10(np.amax(electron_energy_init)),num=50))

plt.xlabel('Energy (eV)')
plt.ylabel('Count')
plt.title('[1000, 10MeV Protons]')

plt.suptitle('Energy Spectra of Secondary Electrons\n in Gold at point of creation')

plt.show()
