#include "AnalysisTool.hh"
#include "StackingTool.hh"

#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <sstream> // stringstream

using namespace std;

AnalysisTool::AnalysisTool(){
}

AnalysisTool::~AnalysisTool() {
}

void AnalysisTool::PrintTool() {
  cout << "No analysis tool currently selected" << endl;
}

bool AnalysisTool::getInterest() {
  return false;
}

bool AnalysisTool::getInterest(int particle, int surface) {
  return false;
}

bool AnalysisTool::getInterest(int particle,
			       int surface,
			       int creationProcess,
			       int flagPhotoElectron) {
  return false;
}

string AnalysisTool::processData() {
  stringstream outLine;
  outLine << "No analysis tool currently selected" << endl;
  return outLine.str();
}

string AnalysisTool::processData(int id, float energy) {
  stringstream outLine;
  outLine << "No analysis tool currently selected" << endl;
  return outLine.str();
}
