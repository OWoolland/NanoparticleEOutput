#ifndef AnalysisTool_h
#define AnalysisTool_h 1

#include "StackingTool.hh"

#include <sstream>   // stringstream

using namespace std;

class AnalysisTool {
  public:
    AnalysisTool();
    virtual ~AnalysisTool();

    virtual void PrintTool();

    virtual bool getInterest();
    virtual bool getInterest(int particle, int sturface);
    virtual bool getInterest(int particle,
			     int sturface,
			     int creationProcess,
			     int flagPhotoElectron);
  
    virtual string processData();
    virtual string processData(int id, float energy);

  private:
};

#endif
