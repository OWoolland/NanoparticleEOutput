// --------------------------------------------------
// Header Files
// --------------------------------------------------

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

// Geant4 core
#include "G4MTRunManager.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

// Text interface 
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

// Visual interface
#include "G4VisExecutive.hh"

// User overriden classes
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

// Allow random spawning
#include "Randomize.hh"
#include "time.h"

// Allow use of units and constants
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// Allow printing to terminal
#include <iostream>
using namespace std;

// --------------------------------------------------
// Global Variables
// --------------------------------------------------

// REMEMBER HALF LENGTHS
G4double target_x = 100*nm;
G4double target_y = 1*um;
G4double target_z = 1*um;

G4double world_x = target_x*1.1;
G4double world_y = target_y*1.1;
G4double world_z = target_z*1.1;

//time_t rawtime;
//struct tm * timeinfo;

G4int id_store = 0;
vector<vector<G4double> > photoElectronStack;
G4Mutex photoElectronStackMutex = G4MUTEX_INITIALIZER;

G4int n_threads = 24;

G4DataVector bindingEnergies;

// --------------------------------------------------
// Begin Main
// --------------------------------------------------

int main(int argc,char** argv)
{
  // Record time at which simulation began
  //time (&rawtime);
  //timeinfo = localtime (&rawtime);

  // --------------------------------------------------
  // Construct the Geant4 framework
  // --------------------------------------------------
  
  // Choose the Random engine and set seed with system time
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time(NULL);
  G4Random::setTheSeed(seed);

  // Construct the run manager
  /*#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(n_threads);
#else
  G4RunManager* runManager = new G4RunManager;
#endif
runManager->SetVerboseLevel(0);*/
  
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetVerboseLevel(0);
  runManager->SetNumberOfThreads(n_threads);

  // Construct the geometry
  DetectorConstruction* massWorld = new DetectorConstruction;
  runManager->SetUserInitialization(massWorld);

  // Apply the physics list
  runManager->SetUserInitialization(new PhysicsList);

  // Initialise the user overriden actions (passing the detector)
  runManager->SetUserInitialization(new ActionInitialization(massWorld));

  // Initialise Geant4 kernel
  runManager->Initialize();

  // --------------------------------------------------
  // Construct the UIs
  // --------------------------------------------------

  // Get UI pointer
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Select batch or graphical mode  
  if (argc!=1) // run scripts
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  else // run interactively
    {  
      G4VisManager* visManager = new G4VisExecutive;
      visManager->SetVerboseLevel(0);
      visManager->Initialize();
      
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
      UImanager->ApplyCommand("/control/execute vis.mac"); 
      ui->SessionStart();
      
      delete ui;
      delete visManager;
    }
  delete runManager;

  return 0;
}
