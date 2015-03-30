import numpy as np
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plt
from pylab import *

data_silicon_1 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_1mev_silicon.csv",delimiter=",")
data_silicon_5 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_silicon.csv",delimiter=",")
data_silicon_10 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_10mev_silicon.csv",delimiter=",")
data_silicon_50 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_50mev_silicon.csv",delimiter=",")
data_silicon_100 = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_100mev_silicon.csv",delimiter=",")

x_silicon_1 = data_silicon_1[:,1]
edep_silicon_1 = data_silicon_1[:,4]
x_silicon_1 = x_silicon_1[edep_silicon_1>0.1]
edep_silicon_1 = edep_silicon_1[edep_silicon_1>0.1]

x_silicon_5 = data_silicon_5[:,1]
edep_silicon_5 = data_silicon_5[:,4]
x_silicon_5 = x_silicon_5[edep_silicon_5>500]
edep_silicon_5 = edep_silicon_5[edep_silicon_5>500]

x_silicon_10 = data_silicon_10[:,1]
edep_silicon_10 = data_silicon_10[:,4]
x_silicon_10 = x_silicon_10[edep_silicon_10>0.10]
edep_silicon_10 = edep_silicon_10[edep_silicon_10>0.10]

x_silicon_50 = data_silicon_50[:,1]
edep_silicon_50 = data_silicon_50[:,4]
x_silicon_50 = x_silicon_50[edep_silicon_50>5000]
edep_silicon_50 = edep_silicon_50[edep_silicon_50>5000]

x_silicon_100 = data_silicon_100[:,1]
edep_silicon_100 = data_silicon_100[:,4]
x_silicon_100 = x_silicon_100[edep_silicon_100>0.100]
edep_silicon_100 = edep_silicon_100[edep_silicon_100>0.100]

min_depth = np.amin([np.amin(x_silicon_1),np.amin(x_silicon_5),np.amin(x_silicon_10),np.amin(x_silicon_50),np.amin(x_silicon_100)])
max_depth = np.amax([np.amax(x_silicon_1),np.amax(x_silicon_5),np.amax(x_silicon_10),np.amax(x_silicon_50),np.amax(x_silicon_100)])
dif_depth = max_depth - min_depth

### Binning data 
x_bins = np.linspace(min_depth, max_depth, num=ceil(dif_depth))

### Sum in bins
hist_x_silicon_1, edges_silicon_1 = np.histogram(x_silicon_1, bins=x_bins, weights=edep_silicon_1)
hist_x_silicon_5, edges_silicon_5 = np.histogram(x_silicon_5, bins=x_bins, weights=edep_silicon_5)
hist_x_silicon_10, edges_silicon_10 = np.histogram(x_silicon_10, bins=x_bins, weights=edep_silicon_10)
hist_x_silicon_50, edges_silicon_50 = np.histogram(x_silicon_50, bins=x_bins, weights=edep_silicon_50)
hist_x_silicon_100, edges_silicon_100 = np.histogram(x_silicon_100, bins=x_bins, weights=edep_silicon_100)

### plotting
silicon_1 = plt.semilogx(hist_x_silicon_1, 'go-', label="1 MeV")
silicon_5 = plt.semilogx(hist_x_silicon_5, 'ro-', label="5 MeV")
silicon_10 = plt.semilogx(hist_x_silicon_10, 'co-', label="10 MeV")
silicon_50 = plt.semilogx(hist_x_silicon_50, 'mo-', label="50 MeV")
silicon_100 = plt.semilogx(hist_x_silicon_100, 'ko-', label="100 MeV")

plt.xlabel('Depth (um)')
plt.ylabel('Energy Deposition (eV)')
plt.title('Energy Deposition in Silicon [1000 Protons]')

plt.legend()

plt.show()
