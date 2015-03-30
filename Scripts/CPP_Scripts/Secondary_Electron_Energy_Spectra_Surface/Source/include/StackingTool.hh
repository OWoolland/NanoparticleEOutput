#ifndef StackingTool_h
#define StackingTool_h 1
#include <string>

using namespace std;

class StackingTool {
  public:
    StackingTool();
    virtual ~StackingTool();

    virtual void stackLine(char* line);

    virtual int getStackSize();
    virtual char* giveLine();

  private:
};

#endif
