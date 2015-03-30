#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"

class G4Run;
class TrackingAction;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:
  // Histogram management
    void CreateHistogram();
    void WriteHistogram();

  // Worker management
    void InitializeWorker(const G4Run*);

  // Variables
    TrackingAction* fpTrackingAction;
    bool fInitialized;
};

#endif
