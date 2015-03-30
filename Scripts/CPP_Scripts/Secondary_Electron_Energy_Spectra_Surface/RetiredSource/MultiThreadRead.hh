#ifndef MultiThreadRead_h
#define MultiThreadRead_h 1

#include "AnalysisTool.hh"
#include "SurfaceEnergy.hh"
#include "StackingTool.hh"

using namespace std;

class MultiThreadRead {
  public:
  MultiThreadRead(const char* file, AnalysisTool* anal, StackingTool* stack);
    ~MultiThreadRead();

    void BeginThreads(int threads);
    int GetRunningThreads();

    static void * ThreadActionMain(void *threadid);
    static void doThreadAction(long long int lower, long long int upper, int id);

    static AnalysisTool * GetAnalysisTool();
  
  private:
};

#endif
