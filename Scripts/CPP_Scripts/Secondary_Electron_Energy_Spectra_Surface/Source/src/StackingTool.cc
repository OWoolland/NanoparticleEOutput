#include "StackingTool.hh"

#include <iostream>  // printing
#include <vector>    // stacking

using namespace std;

static vector<char* > stack;
pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER;

/**************************************************
Flow of class:
  - Create stack
  - Return true from isCreated() when constructed
  - Accept data from reader and maintain a semephore of the stack size
  - Pass lines to awaiting worker threads
**************************************************/

StackingTool::StackingTool(){
}

StackingTool::~StackingTool() {
}

void StackingTool::stackLine(char* line) {
  pthread_mutex_lock(&stack_mutex);
    stack.push_back(line);
  pthread_mutex_unlock(&stack_mutex);
}

int StackingTool::getStackSize() {
  //cout << stack.size() << endl;
  return stack.size();
}

char* StackingTool::giveLine() {
  // potential bottleneck
  char* line = 0;
  pthread_mutex_lock(&stack_mutex);
  if (stack.size()>0) {
    line = stack.back();
    stack.pop_back();
  }
  pthread_mutex_unlock(&stack_mutex);
  return line;  
}
