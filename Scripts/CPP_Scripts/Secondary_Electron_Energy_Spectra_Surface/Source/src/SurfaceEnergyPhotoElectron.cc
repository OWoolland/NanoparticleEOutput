#include "SurfaceEnergyPhotoElectron.hh"
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

SurfaceEnergyPhotoElectron::SurfaceEnergyPhotoElectron() : AnalysisTool() {
}

SurfaceEnergyPhotoElectron::~SurfaceEnergyPhotoElectron() {
}

void SurfaceEnergyPhotoElectron::PrintTool() {
  cout << "The analysis tool in use is SurfaceEnergyPhotoElectron" << endl;
}

bool SurfaceEnergyPhotoElectron::getInterest() {}

bool SurfaceEnergyPhotoElectron::getInterest(int particle, int surface) {}

bool SurfaceEnergyPhotoElectron::getInterest(int particle,
					     int surface,
					     int creationProcess,
					     int flagPhotoElectron) {
  if (particle == 1 && surface == 1 &&
      creationProcess == 8 && flagPhotoElectron == 1) return true;
  else return false;				       
}

string SurfaceEnergyPhotoElectron::processData() {}

string SurfaceEnergyPhotoElectron::processData(int id, float energy) {
  stringstream outLine;
  outLine << id << "," << energy;
  return outLine.str();
}
