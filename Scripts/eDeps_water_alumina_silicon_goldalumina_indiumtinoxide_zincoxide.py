import numpy as np
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plt
from pylab import *

data_water = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_water.csv",delimiter=",")
data_alumina = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_alumina.csv",delimiter=",")
data_silicon = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_silicon.csv",delimiter=",")
data_zincoxide = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_zincoxide.csv",delimiter=",")
data_indiumtinoxide = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_indiumtinoxide.csv",delimiter=",")
data_gold5alumina95 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_gold5alumina95.csv",delimiter=",")

#water_particle = data_water_all[:,7]
#alumina_particle = data_alumina_all[:,7]
#silicon_particle = data_silicon_all[:,7]
#zincoxide_particle = data_zincoxide_all[:,7]
#indiumtinoxide_particle = data_indiumtinoxide_all[:,7]
#gold5alumina95_particle = data_gold5alumina95_all[:,7]

#data_water = data_water_all[water_particle == 2]
#data_alumina = data_alumina_all[alumina_particle == 2]
#data_silicon = data_silicon_all[silicon_particle == 2]

x_water = data_water[:,1]
edep_water = data_water[:,4]
x_water = x_water[edep_water>0.1]
edep_water = edep_water[edep_water>0.1]

x_alumina = data_alumina[:,1]
edep_alumina = data_alumina[:,4]
x_alumina = x_alumina[edep_alumina>0.1]
edep_alumina = edep_alumina[edep_alumina>0.1]

x_silicon = data_silicon[:,1]
edep_silicon = data_silicon[:,4]
x_silicon = x_silicon[edep_silicon>0.1]
edep_silicon = edep_silicon[edep_silicon>0.1]

x_zincoxide = data_zincoxide[:,1]
edep_zincoxide = data_zincoxide[:,4]
x_zincoxide = x_zincoxide[edep_zincoxide>0.1]
edep_zincoxide = edep_zincoxide[edep_zincoxide>0.1]

x_indiumtinoxide = data_indiumtinoxide[:,1]
edep_indiumtinoxide = data_indiumtinoxide[:,4]
x_indiumtinoxide = x_indiumtinoxide[edep_indiumtinoxide>0.1]
edep_indiumtinoxide = edep_indiumtinoxide[edep_indiumtinoxide>0.1]

x_gold5alumina95 = data_gold5alumina95[:,1]
edep_gold5alumina95 = data_gold5alumina95[:,4]
x_gold5alumina95 = x_gold5alumina95[edep_gold5alumina95>0.1]
edep_gold5alumina95 = edep_gold5alumina95[edep_gold5alumina95>0.1]

min_depth = np.amin(x_water)
max_depth = np.amax([np.amax(x_water),np.amax(x_alumina),np.amax(x_silicon),np.amax(x_zincoxide),np.amax(x_indiumtinoxide),np.amax(x_gold5alumina95)])
dif_depth = max_depth - min_depth

### Binning data 
#x_bins = np.linspace(np.amin(x_water), np.amax(x_water), num=1000)
x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth))

### Sum in bins
hist_x_water, edges_water = np.histogram(x_water, bins=x_bins, weights=edep_water)
hist_x_alumina, edges_alumina = np.histogram(x_alumina, bins=x_bins, weights=edep_alumina)
hist_x_silicon, edges_silicon = np.histogram(x_silicon, bins=x_bins, weights=edep_silicon)
hist_x_zincoxide, edges_zincoxide = np.histogram(x_zincoxide, bins=x_bins, weights=edep_zincoxide)
hist_x_indiumtinoxide, edges_indiumtinoxide = np.histogram(x_indiumtinoxide, bins=x_bins, weights=edep_indiumtinoxide)
hist_x_gold5alumina95, edges_gold5alumina95 = np.histogram(x_gold5alumina95, bins=x_bins, weights=edep_gold5alumina95)

### plotting
water = plt.plot(hist_x_water, 'ko-', label="Water")
alumina = plt.plot(hist_x_alumina, 'ro-', label="Alumina")
silicon = plt.plot(hist_x_silicon, 'bo-', label="Silicon")
zincoxide = plt.plot(hist_x_zincoxide, 'go-', label="Zinc Oxide")
indiumtinoxide = plt.plot(hist_x_indiumtinoxide, 'co-', label="Indium Tin Oxide")
gold5alumina95 = plt.plot(hist_x_gold5alumina95, 'mo-', label="Gold 5% Alumina 95%")

#locs, labels = xticks([150,200,250,300,350,400,450,500], ['50', '100', '150', '2#00','250','300','350','400','450'])
#xlow,xhigh,ylow,yhigh = plt.axis()
#plt.axis((110,525,ylow,yhigh))

plt.xlabel('Depth (um)')
plt.ylabel('Energy Deposition (eV)')
plt.title('Energy Deposition in Water, Alumina, Silicon, Zinc Oxide, \nIndium Tin Oxide and a Gold/Alumina Alloy [1000, 5MeV Protons]')

plt.legend()

plt.show()
plt.savefig('eDeps_water_alumina_silicon_goldalumina_indiumoxide_zincoxide.png')
