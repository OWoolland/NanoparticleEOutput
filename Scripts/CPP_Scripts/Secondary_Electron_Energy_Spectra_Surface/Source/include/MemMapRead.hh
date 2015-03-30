#ifndef MemMapRead_h
#define MemMapRead_h 1

#include "AnalysisTool.hh"
#include "StackingTool.hh"

#include <sys/mman.h>

using namespace std;

class MemMapRead {
  public:
    MemMapRead(const char* fName, AnalysisTool* anal, StackingTool* stack);
    virtual ~MemMapRead();
  
    void beginReader();
    
    static const char* mapFile(const char* fname, size_t& length);
    static void * readFile(void *threadid);

    void printCurrentProgress();
    bool getFinished();
  
  private:
};

#endif
