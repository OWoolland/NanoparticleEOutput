#include "SurfaceEnergyAugerElectron.hh"
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

SurfaceEnergyAugerElectron::SurfaceEnergyAugerElectron() : AnalysisTool() {
}

SurfaceEnergyAugerElectron::~SurfaceEnergyAugerElectron() {
}

void SurfaceEnergyAugerElectron::PrintTool() {
  cout << "The analysis tool in use is SurfaceEnergyAugerElectron" << endl;
}

bool SurfaceEnergyAugerElectron::getInterest() {}

bool SurfaceEnergyAugerElectron::getInterest(int particle, int surface) {}

bool SurfaceEnergyAugerElectron::getInterest(int particle,
					     int surface,
					     int creationProcess,
					     int flagPhotoElectron) {
  if (particle == 1 && surface == 1 &&
      creationProcess == 8 && flagPhotoElectron == 0) return true;
  else return false;				       
}

string SurfaceEnergyAugerElectron::processData() {}

string SurfaceEnergyAugerElectron::processData(int id, float energy) {
  stringstream outLine;
  outLine << id << "," << energy;
  return outLine.str();
}
