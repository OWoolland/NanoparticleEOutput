#include "MemMapRead.hh"
#include "AnalysisTool.hh"
#include "StackingTool.hh"

#include <algorithm>
#include <pthread.h> // multithreading
#include <iostream>  // printing
#include <unistd.h>  // delay (usleep)
#include <stdio.h>   // printf
#include <time.h>    // for progress monitoring
#include <stdlib.h>  // atoi 
#include <string.h>  // to_string

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

const char* map_file(const char* fname, size_t& length);
const char* fileMap;
const char* fileEnd;
const char* firstAddr;

AnalysisTool* analyserTool = NULL;
StackingTool* stackTool = NULL;

size_t length;

unsigned long long int firstTime = 0;
unsigned long long int currentTime = 0;

bool finished = false;

/**************************************************
Flow of class:
  - Copy file to memory
  - Copy line from memory
  - Pass to stack
  - When EOF - close
**************************************************/

MemMapRead::MemMapRead(const char* fName, AnalysisTool* anal, StackingTool* stack) {
  analyserTool = anal;
  stackTool = stack;
  
  finished = false;
  fileMap = mapFile(fName, length);
  fileEnd = fileMap + length;
  firstAddr = fileMap;
}

MemMapRead::~MemMapRead()
{}

const char* MemMapRead::mapFile(const char* fname, size_t& length) {
  int fileDescriptor = open(fname, O_RDONLY);
  if (fileDescriptor == -1)
    {
      cerr << "Failed to open" << endl;
      exit(255);
    }
  posix_fadvise(fileDescriptor, 0, 0, POSIX_FADV_SEQUENTIAL);
  posix_fadvise(fileDescriptor, 0, 0, POSIX_FADV_WILLNEED); 
  
  // obtain file size
  struct stat sb;
  if (fstat(fileDescriptor, &sb) == -1)
    {
      cerr << "Failed to fstat" << endl;
      exit(255);
    }
  
  length = sb.st_size;
  
  const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE || MAP_POPULATE, fileDescriptor, 0u));
  if (addr == MAP_FAILED) cerr << "Failed to map" << endl;
  
  return addr;
}

void MemMapRead::beginReader() {
  pthread_t thread[1];
  int id = 101;
  pthread_create(&thread[0], NULL, readFile, (void *)id);
}

void *MemMapRead::readFile(void *threadid) {
  firstTime = time(NULL);
  long threadId = (long)threadid;
  finished = false;
  while (fileMap && fileMap!=fileEnd) {
    const char* nextEnd = (const char *)(memchr(fileMap, '\n', fileEnd-fileMap));

    long long int gapNextEnd = nextEnd-fileMap;

    char* line = new char[gapNextEnd+2];

    strncpy(line, fileMap, gapNextEnd);
    line[gapNextEnd+1]='\0';

    //cout << line << endl;
    if(stackTool->getStackSize()>50000)
      while(stackTool->getStackSize()>25000)
	{usleep(10000);};
    stackTool->stackLine(line);

    ++nextEnd;
    fileMap=nextEnd; 
  }
  finished = true;
}

void MemMapRead::printCurrentProgress() { 
  currentTime = time(NULL);
  float progress = ((long int)fileMap-(long int)firstAddr)/(float)length;
  
  printf("Completed: %.1f%% ", progress*100);
  printf("processing line number %llu of %llu ",fileMap,fileEnd);
  printf("with %.0f minutes elapsed\n",(double)(currentTime-firstTime)/60);
}

bool MemMapRead::getFinished() {
  return finished;
}
