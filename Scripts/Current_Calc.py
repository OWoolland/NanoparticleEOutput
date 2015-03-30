import numpy as np
#import scipy as sp
#import matplotlib as mpl
import matplotlib.pyplot as plt

data = np.genfromtxt("../Build/microelectronics_state_space_merged.csv",delimiter=",")

ParticleID = data[:,0]
x = data[:,1]
y = data[:,2]
z = data[:,3]
Edep =data[:,4]
Energy = data[:,5]
Time = data[:,6]
Particle = data[:,7]

electron_x = x[Particle == 1]
electron_time = Time[Particle == 1]

# i = q*(q/(2mv))*(d/s)

# constants
q = 1.602e-19
m = 9.109e-31

# variables
v = electron_x/electron_time
d = electron_x
s = 200e-6 # detector width

i = q*(q/(2*m*v))*(d/s)

# bin data
t_bins = np.linspace(np.amin(electron_time), np.amin(electron_time), num=100)

# sum in bins
hist_t, edges = np.histogram(electron_time, bins=t_bins, weights=i)

### plotting
plt.plot(hist_t)

xlow,xhigh,ylow,yhigh = plt.axis()
plt.axis((xlow,xhigh,ylow,yhigh))

plt.xlabel('Time')
plt.ylabel('Current (A)')
plt.title('Current against Time')

plt.show()
