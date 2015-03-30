#include "AllPass.hh"
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

AllPass::AllPass() : AnalysisTool() {
}

AllPass::~AllPass() {
}

void AllPass::PrintTool() {
  cout << "The analysis tool in use is AllPass" << endl;
}

bool AllPass::getInterest() {
  return true;
}

bool AllPass::getInterest(int particle, int surface) {}

bool AllPass::getInterest(int particle,
				int surface,
				int creationProcess,
				int flagPhotoElectron) {}

string AllPass::processData() {}

string AllPass::processData(int id, float energy) {
  stringstream outLine;
  outLine << id << "," << energy;
  return outLine.str();
}
