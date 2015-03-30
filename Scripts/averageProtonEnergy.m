# read in file
data = dlmread("../Data/CambridgeOutput_nt_state_space_merged_water.csv")(:,1:15);
# select relevant columns
id = data(:,1);
x = data(:,2);
E = data(:,6);
particle = data(:,8);

clear data

# remove uninteresting events
id = id(particle==2);
x = x(particle==2);
E = E(particle==2);

# lots of id = 1 ...

clear particle

# histogram id and energy by depth


  ParticleID = data[:,0]
  x = data[:,1]
  y = data[:,2]
  z = data[:,3]
  edep =data[:,4]
  Energy = data[:,5]
  Time = data[:,6]
  Particle = data[:,7]

  proton_x = x[Particle == 2]
  proton_energy = Energy[Particle == 2]

  proton_energy = proton_energy[proton_x>0]
  proton_x = proton_x[proton_x>0]

  ### Sum in bins
  hist_x, edges = np.histogram(proton_x, bins=75, weights=proton_energy)
    
  ### plotting
  plt.plot(edges[1:],hist_x, 'ko-')

  xlow,xhigh,ylow,yhigh = plt.axis()
  plt.axis((xlow,xhigh,ylow,yhigh))
  
  plt.xlabel('Depth (um)')
  plt.ylabel('Energy (eV)')
  plt.title(title)

  plt.show()

  print('3db point is: %.2e ' % (0.707*np.amax(hist_x)))

  odata = zip(hist_x,edges[1:])
  np.savetxt('Average_Energy_x.csv', odata, delimiter=',')
