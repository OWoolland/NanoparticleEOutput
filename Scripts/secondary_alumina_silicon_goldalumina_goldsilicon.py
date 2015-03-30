import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from pylab import *

### Import data

data_alumina = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_alumina.csv",delimiter=",")
data_silicon = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_silicon.csv",delimiter=",")
data_gold5alumina95 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_gold5alumina95.csv",delimiter=",")
data_gold5silicon95 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_gold5silicon95.csv",delimiter=",")

### Extract particle types

alumina_particle = data_alumina[:,7]
silicon_particle = data_silicon[:,7]
gold5alumina95_particle = data_gold5alumina95[:,7]
gold5silicon95_particle = data_gold5silicon95[:,7]

### Select electrons

data_alumina = data_alumina[alumina_particle == 1]
data_silicon = data_silicon[silicon_particle == 1]
data_gold5alumina95 = data_gold5alumina95[gold5alumina95_particle == 1]
data_gold5silicon95 = data_gold5silicon95[gold5silicon95_particle == 1]

### Extract initial positions

x_alumina = data_alumina[:,1]
alumina_process = data_alumina[:,8]
x_alumina_init = x_alumina[alumina_process==1]

x_silicon = data_silicon[:,1]
silicon_process = data_silicon[:,8]
x_silicon_init = x_silicon[silicon_process==1]

x_gold5alumina95 = data_gold5alumina95[:,1]
gold5alumina95_process = data_gold5alumina95[:,8]
x_gold5alumina95_init = x_gold5alumina95[gold5alumina95_process==1]

x_gold5silicon95 = data_gold5silicon95[:,1]
gold5silicon95_process = data_gold5silicon95[:,8]
x_gold5silicon95_init = x_gold5silicon95[gold5silicon95_process==1]

### Find plot scaling

min_depth = np.amin([np.amin(x_gold5silicon95_init),np.amin(x_alumina_init),np.amin(x_silicon_init),np.amin(x_gold5alumina95_init)])
max_depth = np.amax([np.amax(x_gold5silicon95_init),np.amax(x_alumina_init),np.amax(x_silicon_init),np.amax(x_gold5alumina95_init)])
dif_depth = max_depth - min_depth

### Binning data 

x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth))

### Sum in bins
hist_x_alumina, edges_alumina = np.histogram(x_alumina_init, bins=x_bins)
hist_x_silicon, edges_silicon = np.histogram(x_silicon_init, bins=x_bins)
hist_x_gold5alumina95, edges_gold5alumina95 = np.histogram(x_gold5alumina95_init, bins=x_bins)
hist_x_gold5silicon95, edges_gold5silicon95 = np.histogram(x_gold5silicon95_init, bins=x_bins)

#hist_x_alumina, edges_alumina = np.histogram(x_alumina_init)
#hist_x_silicon, edges_silicon = np.histogram(x_silicon_init)
#hist_x_gold5alumina95, edges_gold5alumina95 = np.histogram(x_gold5alumina95_init)
#hist_x_gold5silicon95, edges_gold5silicon95 = np.histogram(x_gold5silicon95_init)

### plotting

alumina = plt.plot(hist_x_alumina, 'ro-', label="Alumina")
silicon = plt.plot(hist_x_silicon, 'bo-', label="Silicon")
gold5alumina95 = plt.plot(hist_x_gold5alumina95, 'mo-', label="Gold 5% Alumina 95%")
gold5silicon95 = plt.plot(hist_x_gold5silicon95, 'ko-', label="Gold 5% Silicon 95%")

plt.xlabel('Depth (um)')
plt.ylabel('Count')
plt.title('Scondary Electron Generation in Alumina, Silicon, Gold/Alumina Alloy\nand Gold/Silicon Alloy [1000, 1MeV Protons]')

plt.legend()

plt.show()
