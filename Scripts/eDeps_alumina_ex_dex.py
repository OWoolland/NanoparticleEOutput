import numpy as np
import matplotlib.pyplot as plt
from pylab import *

data_disabled = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_alumina.csv",delimiter=",")
data_enabled = np.genfromtxt("../Data/StandardEM_Opt_4_state_space_merged_5mev_alumina_deex.csv",delimiter=",")

x_disabled = data_disabled[:,1]
edep_disabled =data_disabled[:,4]

x_enabled = data_enabled[:,1]
edep_enabled =data_enabled[:,4]

### Binning data 
#x_bins = np.linspace(np.amin(x_disabled), np.amax(x_disabled), num=2200)

### Sum in bins
hist_x_disabled, edges_disabled = np.histogram(x_disabled, bins=1000, weights=edep_disabled)
hist_x_enabled, edges_enabled = np.histogram(x_enabled, bins=1000, weights=edep_enabled)

### plotting
#disabled = plt.plot(hist_x_disabled, 'ko', label="Disabled")
enabled = plt.plot(hist_x_enabled, 'ro', label="Enabled")

plt.xlabel('Depth (um)')
plt.ylabel('Energy Deposition (eV)')
plt.title('Energy deposition comparision with atomic deexcitation enabled and disabled [50, 5MeV Protons]')

plt.legend()

plt.show()
