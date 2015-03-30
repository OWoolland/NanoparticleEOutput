#ifndef PlottingTool_h
#define PlottingTool_h 1

#include <string>

using namespace std;

class PlottingTool {
  public:
    PlottingTool();
    virtual ~PlottingTool();

    virtual void setTitle(string title);
    virtual void setXLabel(string xLabel);
    virtual void setYLabel(string yLabel);

    virtual void setFile(string file);

    virtual void setPlotParameters(string params);
  
    virtual void plotXY(int xCol, int yCol);
    virtual void plotHist(int nBins, double minValue, double maxValue, int col);

  private:
};

#endif
