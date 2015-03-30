import numpy as np
import matplotlib.pyplot as plt
from pylab import *

data_water = np.genfromtxt("../Data/microelectronics_state_space_merged_5mev_water.csv",delimiter=",")
data_alumina = np.genfromtxt("../Data/microelectronics_state_space_merged_5mev_alumina.csv",delimiter=",")

x_water = data_water[:,1]
edep_water =data_water[:,4]

x_alumina = data_alumina[:,1]
edep_alumina =data_alumina[:,4]

### Binning data 
x_bins = np.linspace(np.amin(x_water), np.amax(x_water), num=2200)

### Sum in bins
hist_x_water, edges_water = np.histogram(x_water, bins=x_bins, weights=edep_water)
hist_x_alumina, edges_alumina = np.histogram(x_alumina, bins=x_bins, weights=edep_alumina)

### plotting
water = plt.plot(hist_x_water, 'ko', label="Water")
alumina = plt.plot(hist_x_alumina, 'ro', label="Alumina")

locs, labels = xticks([150,200,250,300,350,400,450,500], ['50', '100', '150', '200','250','300','350','400','450'])
xlow,xhigh,ylow,yhigh = plt.axis()
plt.axis((110,525,ylow,yhigh))

plt.xlabel('Depth (um)')
plt.ylabel('Energy Deposition (eV)')
plt.title('Energy Deposition in Water and Alumina [500, 5MeV Protons]')

plt.legend()

plt.show()
