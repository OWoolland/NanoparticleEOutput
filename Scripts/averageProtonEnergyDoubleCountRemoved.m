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
[dummy, index] = histc(x,linspace(min(x),max(x))); # index = histogram bin of input vector

for i=1:size(unique(index))
  binindex = unique(index)(i);
  binids = id.*(index==j); # array of ids in each bin
  for j=1:size(binids) # for each id in each bin
    binid = binids(j);
    
  end
end
