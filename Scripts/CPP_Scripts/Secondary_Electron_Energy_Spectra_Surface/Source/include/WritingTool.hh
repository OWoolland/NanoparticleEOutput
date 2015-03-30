#ifndef WritingTool_h
#define WritingTool_h 1

#include "StackingTool.hh"
#include "MemMapRead.hh"

#include <sstream>   // stringstream

using namespace std;

class WritingTool {
  public:
    WritingTool(const char* outFileName, StackingTool* stack, MemMapRead* reader);
    virtual ~WritingTool();

    void beginWriter();
    int getWriteStackSize();
    static void *writeStack(void* threadid);
    void stackLine(string line);
      
  private:
};

#endif
