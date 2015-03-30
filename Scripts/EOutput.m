data = dlmread("../Scripts/surface_only_dataset.csv");

data_electron = data(data(:,8)==1,:); % select electrons

clear data;

id = data_electron(:,1);
x = data_electron(:,2);
y = data_electron(:,3);
z = data_electron(:,4);
edep = data_electron(:,5);
energy = data_electron(:,6);
time = data_electron(:,7);
particle = data_electron(:,8);
process = data_electron(:,9);
creation_process = data_electron(:,10);
momentum_x = data_electron(:,11);
momentum_y = data_electron(:,12);
momentum_z = data_electron(:,13);
volume = data_electron(:,14);
surface = data_electron(:,15);
auger = data_electron(:,16);

energy_surface_PEE = energy(surface==1&creation_process==8);
%energy_surface_PEE_auger = energy(surface==1&creation_process==8&auger==1);
%energy_surface_PEE_photo = energy(surface==1&creation_process==8&auger==0);

clf
hold all
axis ([0 15000]);
hist(energy_surface_PEE,15000,'FaceColor','g','EdgeColor','g');
%hist(energy_surface_PEE_auger,10000,'FaceColor','r','EdgeColor','r');
%hist(energy_surface_PEE_photo,10000,'FaceColor','g','EdgeColor','g');
%legend("Auger","PhotoElectrons")

xlabel ('Energy (ev)')
ylabel ('Number of Electrons')
title ('Energy spectra of asdf electrons crossing the nanoparticle surface - 10^6, 10 keV photons input')
