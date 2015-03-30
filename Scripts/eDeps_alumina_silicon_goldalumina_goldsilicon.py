import numpy as np
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plt
from pylab import *

data_alumina = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_alumina.csv",delimiter=",")
data_silicon = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_silicon.csv",delimiter=",")
data_gold5alumina95 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_gold5alumina95.csv",delimiter=",")
data_gold5silicon95 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_gold5silicon95.csv",delimiter=",")

#water_particle = data_water_all[:,7]
#alumina_particle = data_alumina_all[:,7]
#silicon_particle = data_silicon_all[:,7]
#zincoxide_particle = data_zincoxide_all[:,7]
#indiumtinoxide_particle = data_indiumtinoxide_all[:,7]
#gold5alumina95_particle = data_gold5alumina95_all[:,7]

#data_water = data_water_all[water_particle == 2]
#data_alumina = data_alumina_all[alumina_particle == 2]
#data_silicon = data_silicon_all[silicon_particle == 2]

x_alumina = data_alumina[:,1]
edep_alumina = data_alumina[:,4]
x_alumina = x_alumina[edep_alumina>0.1]
edep_alumina = edep_alumina[edep_alumina>0.1]

x_silicon = data_silicon[:,1]
edep_silicon = data_silicon[:,4]
x_silicon = x_silicon[edep_silicon>0.1]
edep_silicon = edep_silicon[edep_silicon>0.1]

x_gold5alumina95 = data_gold5alumina95[:,1]
edep_gold5alumina95 = data_gold5alumina95[:,4]
x_gold5alumina95 = x_gold5alumina95[edep_gold5alumina95>0.1]
edep_gold5alumina95 = edep_gold5alumina95[edep_gold5alumina95>0.1]

x_gold5silicon95 = data_gold5silicon95[:,1]
edep_gold5silicon95 = data_gold5silicon95[:,4]
x_gold5silicon95 = x_gold5silicon95[edep_gold5silicon95>0.1]
edep_gold5silicon95 = edep_gold5silicon95[edep_gold5silicon95>0.1]

min_depth = np.amin(x_alumina)
max_depth = np.amax([np.amax(x_gold5silicon95),np.amax(x_alumina),np.amax(x_silicon),np.amax(x_gold5alumina95)])
dif_depth = max_depth - min_depth

### Binning data 
#x_bins = np.linspace(np.amin(x_water), np.amax(x_water), num=1000)
x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth))

### Sum in bins
hist_x_alumina, edges_alumina = np.histogram(x_alumina, bins=x_bins, weights=edep_alumina)
hist_x_silicon, edges_silicon = np.histogram(x_silicon, bins=x_bins, weights=edep_silicon)
hist_x_gold5alumina95, edges_gold5alumina95 = np.histogram(x_gold5alumina95, bins=x_bins, weights=edep_gold5alumina95)
hist_x_gold5silicon95, edges_gold5silicon95 = np.histogram(x_gold5silicon95, bins=x_bins, weights=edep_gold5silicon95)

### plotting
alumina = plt.plot(hist_x_alumina, 'ro-', label="Alumina")
silicon = plt.plot(hist_x_silicon, 'bo-', label="Silicon")
gold5alumina95 = plt.plot(hist_x_gold5alumina95, 'mo-', label="Gold 5% Alumina 95%")
gold5silicon95 = plt.plot(hist_x_gold5silicon95, 'ko-', label="Gold 5% Silicon 95%")

#locs, labels = xticks([150,200,250,300,350,400,450,500], ['50', '100', '150', '2#00','250','300','350','400','450'])
#xlow,xhigh,ylow,yhigh = plt.axis()
#plt.axis((110,525,ylow,yhigh))

plt.xlabel('Depth (um)')
plt.ylabel('Energy Deposition (eV)')
plt.title('Energy Deposition in Alumina, Silicon, Gold/Alumina Alloy\nand Gold/Silicon Alloy [1000, 1MeV Protons]')

plt.legend()

plt.show()
#plt.savefig('eDeps_water_alumina_silicon_goldalumina_indiumoxide_zincoxide.png')
