#include "SurfaceEnergy.hh"
#include "AnalysisTool.hh"

#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <sstream>   // stringsream
#include <vector>    // stacking
#include <sstream>   // stringstream

using namespace std;

/**************************************************
Flow of class:
  - Receive relevant variables from worker thread
  - Check for interest
  - Process data and format for outputting
**************************************************/

SurfaceEnergy::SurfaceEnergy() : AnalysisTool() {
}

SurfaceEnergy::~SurfaceEnergy() {
}

void SurfaceEnergy::PrintTool() {
  cout << "The analysis tool in use is SurfaceEnergy" << endl;
}

bool SurfaceEnergy::getInterest() {}

bool SurfaceEnergy::getInterest(int particle, int surface) {
  if (particle == 1 && surface == 1) return true;
  else return false;				       
}

bool SurfaceEnergy::getInterest(int particle,
				int surface,
				int creationProcess,
				int flagPhotoElectron) {}

string SurfaceEnergy::processData() {}

string SurfaceEnergy::processData(int id, float energy) {
  stringstream outLine;
  outLine << id << "," << energy;
  return outLine.str();
}
