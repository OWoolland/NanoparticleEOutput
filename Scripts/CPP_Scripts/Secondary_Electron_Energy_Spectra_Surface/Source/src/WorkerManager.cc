#include "WorkerManager.hh"
#include "StackingTool.hh"
#include "WritingTool.hh"

#include "AnalysisTool.hh"


#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <vector>    // stacking
#include <sstream>   // stringstream

using namespace std;

int nThreads = 0;
AnalysisTool* analyser = NULL;
StackingTool* stackingTool = NULL;
WritingTool* writingTool = NULL;

/**************************************************
Flow of class:
  - Check stack semaphore
  - If > 0 then fetch a line
  - Process the line and retreive the variables
  - Check if the analyser is interested in the line 
  - Write the relevant information to the output file if so
**************************************************/

WorkerManager::WorkerManager(AnalysisTool* anal, StackingTool* stack, WritingTool* write) {
  analyser = anal;
  stackingTool = stack;
  writingTool = write;
  
  analyser->PrintTool();
}

WorkerManager::~WorkerManager() {
}

void WorkerManager::beginThreads(int numThreads) {
  nThreads = numThreads;
  pthread_t threads[nThreads];
  
  for(int i=0; i<nThreads; i++) {
    pthread_create(&threads[i], NULL, threadAction, (void *)i);
  }
}

void *WorkerManager::threadAction(void *threadid) {
  long threadId = (long)threadid;
  char* line;

  int id = 0;
  float x,y,z,edep,energy,particle_time = 0.;
  int particle,process,creation_process = 0;
  float momentum_x,momentum_y,momentum_z = 0.;
  int volume,surface,photoElectron = 0;

  while (true) {
    if (stackingTool->getStackSize()==0) continue;
    else line = stackingTool->giveLine();

    stringstream line_ss; // create stringsteam pseudofile of line
    line_ss << line;

    int i = 1; bool line_fail = false; string value;
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
	  case 16: value_ss >> photoElectron; break;
	  case 17: break;
	  default: 
	    cout << "Error on line " << line <<endl;
	    line_fail = true;
	  }
	i++;
      }
    if(analyser->getInterest(particle, surface, creation_process, photoElectron)) {
      string toWrite = analyser->processData(id,energy); // make one line
      if(writingTool->getWriteStackSize()>50000)
	while(writingTool->getWriteStackSize()>2500)
	  {usleep(10000);};      
      writingTool->stackLine(toWrite);
    }     
  }
}
