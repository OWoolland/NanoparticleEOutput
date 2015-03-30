#ifndef WorkerManager_h
#define WorkerManager_h 1

#include "AnalysisTool.hh"
#include "StackingTool.hh"
#include "WritingTool.hh"

using namespace std;
  
class WorkerManager { 
  public:

  WorkerManager(AnalysisTool* anal, StackingTool* stack, WritingTool* write);
    ~WorkerManager();

    static void beginThreads(int numThreads);
    static void * threadAction(void *threadid);

  private:
};

#endif
