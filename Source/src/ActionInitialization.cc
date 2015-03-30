#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "TrackingAction.hh"

#include "G4MTRunManager.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detConstruction)
  : G4VUserActionInitialization(),
    fDetectorConstruction(detConstruction)
{

}

ActionInitialization::~ActionInitialization()
{

}

void ActionInitialization::BuildForMaster() const
{
  // For ease of reading when using MT mode the master thread for
  // this code is different to the workers
}

void ActionInitialization::Build() const
{	
  SetUserAction(new PrimaryGeneratorAction);

  TrackingAction* trackingAction = new TrackingAction(fDetectorConstruction);
  SetUserAction(trackingAction);

  RunAction* runAction= new RunAction();
  SetUserAction(runAction);

  SetUserAction(new SteppingAction());
}  
