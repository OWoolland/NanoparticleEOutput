fid = fopen('../Data/StandardEM_Opt_4_state_space_merged_45mev_water_goldslice.csv');

tline = fgetl(fid);
while ischar(tline))
  disp(tline)
  id = data(:,1);
  x = data(:,2);
  y = data(:,3);
  z = data(:,4);
  edep = data(:,5);
  energy = data(:,6);
  time = data(:,7);
  particle = data(:,8);
  process = data(:,9);
  creation_process = data(:,10);   

  tline = fgetl(fid);
end

fclose(fid);







#data=1;
#no_protons = 0;
#no_interactions = 0;

##  data = data{:,:,:};
#  size(data)
  # remove data from outside nanoparticle
#  np_width = 10E-3;
#  x = data{2};
#  data = data{x>-np_width,:};
#  x = data{2};
#  data = data(x<np_width,:);
  
  # In nanoparticle data only

#  no_interactions = no_interactios + size(id,1)
#  no_protons = no_protons + size(unique(id(particle==2)),1)

#  disp(loop)
#  total_edep_protons = total_edep_protons + edep(particle==2); 
#  total_edep_electrons = total_edep_electrons edep(particle==1));
end  

#fclose(fileID);

#disp(sprintf('Number of interactions with the nanoparticle: %i',size(no_interactions)))
#disp(sprintf('Number of protons interacting with nanoparticle: %i',size(no_protons)))
#disp(sprintf('Average energy deposit by protons: %i eV by electrons: %i eV', average_edep_protons,average_edep_electrons))
#disp(sprintf('Total number of particles interacting in the nanoparticle: %i',size(unique(id),1)))
