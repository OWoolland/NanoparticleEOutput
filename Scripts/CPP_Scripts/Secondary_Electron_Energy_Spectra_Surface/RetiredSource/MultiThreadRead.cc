#include "MultiThreadRead.hh"
#include "SurfaceEnergy.hh"
#include "StackingTool.hh"

#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <vector>    // stacking

using namespace std;

volatile int running_threads = 0;
pthread_mutex_t running_threads_mutex = PTHREAD_MUTEX_INITIALIZER;

long long int length = 0;
const char* inputFileName;

int nThreads = 0;
AnalysisTool* analyser = NULL;
StackingTool* stackingTool = NULL;

MultiThreadRead::MultiThreadRead(const char* fileName, AnalysisTool* anal, StackingTool* stack) {
  analyser = anal;
  stackingTool = stack;
  //anal->PrintTool();
  
  // setup file parameters
  inputFileName = fileName;
  ifstream file (inputFileName);

  /*  // find lingth of file
  file.seekg (0, ios::end);
  length = file.tellg();
  file.seekg (0, ios::beg);

  cout << "Length is: " << length << endl;*/
}

MultiThreadRead::~MultiThreadRead() {
  pthread_exit(NULL);
}

AnalysisTool* MultiThreadRead::GetAnalysisTool() {
  return analyser;
}

void MultiThreadRead::BeginThreads(int numThreads) {
  nThreads = numThreads;
  pthread_t threads[nThreads];

  // also create stacking tool
  
  for(int i=0 ; i<nThreads ; i++) {
    pthread_create(&threads[i], NULL, ThreadActionMain, (void *)i);
  }
}

int MultiThreadRead::GetRunningThreads() {
  //pthread_mutex_lock(&running_threads_mutex);
  return running_threads;
  //pthread_mutex_unlock(&running_threads_mutex);
}

void *MultiThreadRead::ThreadActionMain(void *threadid) { 
  long id = (long)threadid;

  long long int threadLocalLengthLower = 0; // if thread 0
  if (id!=0) threadLocalLengthLower = ((length/nThreads)*id)+1;
  long long int threadLocalLengthUpper = (length/nThreads)*(id+1);
  
  //------------------------------------------------
  // Thread Start
  //------------------------------------------------

  pthread_mutex_lock(&running_threads_mutex);
  running_threads++;
  pthread_mutex_unlock(&running_threads_mutex);
  
  //------------------------------------------------
  // Thread Body
  //------------------------------------------------
  
  doThreadAction(threadLocalLengthLower, threadLocalLengthUpper, id);
  
  //------------------------------------------------
  // Thread End
  //------------------------------------------------
  pthread_mutex_lock(&running_threads_mutex);
  running_threads--;
  pthread_mutex_unlock(&running_threads_mutex);    
   
  pthread_exit(NULL);
}

void MultiThreadRead::doThreadAction(long long int lower, long long int upper, int threadid) {
  long long int threadLocalLengthLower = lower;
  long long int threadLocalLengthUpper = upper;
  int id = threadid;
  
  ifstream file (inputFileName);
  string line;
  
  // begin read
  file.seekg (threadLocalLengthLower);
  while(file.good()&&(file.tellg()<threadLocalLengthUpper)) {
    getline(file,line);
    analyser->ProcessLine(line,stackingTool);
  }  
}
