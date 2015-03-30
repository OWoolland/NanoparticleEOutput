#include "WritingTool.hh"
#include "MemMapRead.hh"
#include "StackingTool.hh"

#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <fstream>   // reading file
#include <vector>    // stacking
#include <unistd.h>  // delay (usleep) , getopt

using namespace std;

static ofstream ofile;
//pthread_mutex_t ofile_mutex = PTHREAD_MUTEX_INITIALIZER;

static vector<string > writerStack;
pthread_mutex_t writerStack_mutex = PTHREAD_MUTEX_INITIALIZER;

MemMapRead* readToolWriter = NULL;
StackingTool* stackToolWriter = NULL;

/**************************************************
Flow of class:
  - Accept lines from other classes to write to output file

 SHOULD BECOME A STACK
**************************************************/

WritingTool::WritingTool(const char * outFileName,
			 StackingTool* stack,
			 MemMapRead* reader) {
  ofile.open(outFileName);
  stackToolWriter = stack;
  readToolWriter = reader;
}

WritingTool::~WritingTool() {
}

void WritingTool::beginWriter() {
  pthread_t thread[1];
  int id = 201;
  pthread_create(&thread[0], NULL, writeStack, (void *)id);
}

void *WritingTool::writeStack(void *threadid) {
  string writeLine;
  long threadId = (long)threadid;
  while((writerStack.size()>0)||
	(stackToolWriter->getStackSize()>0)||
	(readToolWriter->getFinished()==0)
	) {
    if (writerStack.size()>0) {
      pthread_mutex_lock(&writerStack_mutex);
        writeLine = writerStack.back();
        writerStack.pop_back();
      pthread_mutex_unlock(&writerStack_mutex);
      ofile << writeLine << endl;
    } else {
      usleep(1000);
    }
  }
}

void WritingTool::stackLine(string writeStackLine) {
  pthread_mutex_lock(&writerStack_mutex);
    writerStack.push_back(writeStackLine);
  pthread_mutex_unlock(&writerStack_mutex);  
}

int WritingTool::getWriteStackSize() {
  return writerStack.size();
}
