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

vector<float > Energy(1000000,0);
vector<int > Count(1000000,0);
vector<float > Hist(1000000,0); 

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
int surface = 0;
int auger = 0;

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
  ofstream ofile (argv[2]);

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

      //cout << line_ss.str() << endl;
      
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
	    case 15: value_ss >> surface; break;
	    case 16: value_ss >> auger; break;
	    default: 
	      current_loc = file.tellg();
	      printf("Error on line %llu\n",current_loc); 
	      //id = x = y = z = edep = energy = particle_time = particle = process = creation_process = 0;
	      line_fail = true;
	    }
	  i++;
	}

      // Analysise individual event here
      x=(x+1000000); // zero ref mm  
      if (id != 0 && particle==2 && process!=1)
	{
	  Energy[floor(x)]=Energy[floor(x)]+energy;
	  Count[floor(x)]++;
 	}
    }
  // Analyise all events here
  for (int i = 0 ; i < Energy.size() ; i++) {
    if(Count[i]>0) Hist[i]=Energy[i]/Count[i];
    else Hist[i] = 0;
    ofile << Hist[i] << endl;
  }
  //cout << Hist << endl;
  ofile.close();
}
