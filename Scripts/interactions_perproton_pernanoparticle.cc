#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <string.h>

#include <stdio.h>
#include <stdlib.h> 

#include <cmath> 

#include <list>
#include <time.h> 

using namespace std;

int i = 0;
string line;
string value;

stringstream line_ss;
stringstream value_ss;

unsigned long long int currentTime;
unsigned long long int lastTime;

unsigned long long int current_loc;
unsigned long long int length;

int id = 0;
float x = 0.;
float y = 0.;
float z = 0.;
float edep = 0.;
float energy = 0.;
float particle_time = 0.;
int particle = 0;
int process = 0;
int creation_process = 0;
float momentum_x = 0.;
float momentum_y = 0.;
float momentum_z = 0.;
int volume = 0.;

int proton_count;
int electron_count;

int main(int argc, char* argv[])
{
  if (argc < 2) 
    {
      cerr << "Usage: " << argv[0] << " <options> DATAFILE\n"
	   << "Options:\n"
	   << "\t-h,--help\t\tShow this help message\n"
	   << "\t-c,--csv\t\tExport a csv file\n"
	   << "\t-o,--output\t\tName the otput csv file"
	   << endl;
    }

  // setup file parameters
  ifstream file (argv[1]);
  ofstream ofile;
  ofile.open("nanoparticle_only_dataset.csv");

  // find lingth of file
  file.seekg (0, ios::end);
  length =file.tellg();
  file.seekg (0, ios::beg);

  // begin timing
  lastTime = time(NULL);
  
  while(file.good())
    {
      // get a single line of the file
      getline(file,line);

      // every interval seconds print a status update
      int interval = 30;
      currentTime = time(NULL);
      if ((currentTime - lastTime >= interval))
	{
	  current_loc = file.tellg();
	  printf("Completed: %.1f%% ", ((double)current_loc/(double)length)*100);
	  printf("processing line number %llu of %llu ",current_loc,length);
	  printf("with %.0f minutes elapsed\n",(double)currentTime/60);
	  lastTime = currentTime;
	}

      stringstream line_ss(line); // create stringsteam pseudofile of line
      int i = 1;

      bool line_fail = false;
      while (line_ss.good() && !line_fail)
	{
	  // get comma delimited element of file line
	  getline(line_ss, value, ',');
	  
	  // use stringstream to hold values temporarily
	  stringstream value_ss(value);
	  switch(i)
	    {
            case 1: value_ss >> id; break;
            case 2: value_ss >> x; break;
	    case 3: value_ss >> y; break;
	    case 4: value_ss >> z; break;	    
	    case 5: value_ss >> edep; break;
	    case 6: value_ss >> energy; break;
	    case 7: value_ss >> particle_time; break;
	    case 8: value_ss >> particle; break;	   
	    case 9: value_ss >> process; break;
	    case 10: value_ss >> creation_process; break;
            case 11: value_ss >> momentum_x; break;
	    case 12: value_ss >> momentum_y; break;
	    case 13: value_ss >> momentum_z; break;
	    case 14: value_ss >> volume; break;
	    default: 
	      current_loc = file.tellg();
	      printf("Error on line %llu\n",current_loc); 
	      id = x = y = z = edep = energy = particle_time = particle = process = creation_process = 0;
	      line_fail = true;
	    }
	  i++;
	}
      
      // Analysise individual event here
      //float np_r = 10E-3; // nanoparticle radius (width)
      //if (abs(x-0.1)<np_r) // if event is inside nanoparticle
      if (volume == 1 && id != 0) // some weird thing where particle 0 is totally fictional or wrong
	{
	  // count the particle
          if(particle == 2) proton_count++;
	  else if(particle == 1) electron_count++;  

	  // write to output file
	  ofile << id << "," 
		<< x << "," 
		<< y << "," 
		<< z << "," 
		<< edep << "," 
		<< energy << "," 
		<< particle_time << "," 
		<< particle << "," 
		<< process << "," 
		<< creation_process << ","
		<< momentum_x << "," 
		<< momentum_y << "," 
		<< momentum_z << "," 
		<< volume << endl;
 	}
      
    }
  // Analyise all events here
  cout<<"Electron count is "<< electron_count << " proton count is " << proton_count << endl;
  ofile.close();
}
