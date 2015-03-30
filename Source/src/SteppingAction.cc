// needs editing

// --------------------------------------------------
// Header Files
// --------------------------------------------------

#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackVector.hh"
#include "G4MTRunManager.hh"
#include "Analysis.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include "UserTrackInformation.hh"

#include "G4Threading.hh"
#include "G4ShellData.hh"
#include "G4AtomicShellEnumerator.hh"
#include "G4NucleiProperties.hh"

#include "G4AutoLock.hh"

// --------------------------------------------------
// Global Variables
// --------------------------------------------------

extern G4double water_x;
extern G4double water_y;
extern G4double water_z;
  
extern G4double world_x;
extern G4double world_y;
extern G4double world_z;
  
extern G4double alumina_x;
extern G4double alumina_y;
extern G4double alumina_z;

extern G4double pore_d;

// --------------------------------------------------
// Local Variables
// --------------------------------------------------

//static G4Element* goldElement = new G4Element("Gold","Au",79,196.9666*g/mole) ;

// --------------------------------------------------
// Class begin
// --------------------------------------------------

SteppingAction::SteppingAction():G4UserSteppingAction() 
{
}

SteppingAction::~SteppingAction() 
{ 
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4double edep = step->GetTotalEnergyDeposit();
  G4double energy = step->GetTrack()->GetKineticEnergy();

  G4String particle_type = step->GetTrack()->GetDefinition()->GetParticleName();
  G4int particle_id = step->GetTrack()->GetTrackID();

  UserTrackInformation* trackInfo = (UserTrackInformation*)(step->GetTrack()->GetUserInformation());
  G4int user_track_id = trackInfo->GetUserTrackID();

  G4double stepLength = step->GetStepLength();

  G4StepPoint* prePoint  = step->GetPreStepPoint();
  G4StepPoint* postPoint = step->GetPostStepPoint();

  G4double x1 = prePoint->GetPosition().x();
  G4double x2 = postPoint->GetPosition().x(); 
  
  G4double y = postPoint->GetPosition().y(); 
  G4double z = postPoint->GetPosition().z(); 

  G4ThreeVector momentum = step->GetTrack()->GetMomentumDirection();
  G4double momentum_x = momentum.x();
  G4double momentum_y = momentum.y();
  G4double momentum_z = momentum.z();

  G4String CurrentVolumeName = step->GetTrack()->GetVolume()->GetName();
 
  G4double step_time = step->GetTrack()->GetGlobalTime();
  G4int step_no = step->GetTrack()->GetCurrentStepNumber();

  G4double step_mid = (x1+x2)/2; 

  G4String ParticleName = step->GetTrack()->GetDynamicParticle()->GetDefinition() ->GetParticleName();
  G4String ProcessName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4String CreationProcessName = "initStep";
  if(step->GetTrack()->GetCreatorProcess()!=0) CreationProcessName = step->GetTrack()->GetCreatorProcess()->GetProcessName();

  
  //////////////////////////////////////////////////
  // Other flags
  //////////////////////////////////////////////////

  
  G4int flagAtSurface = step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary;
  G4bool flagAugerElectron = trackInfo->GetAugerElectronFlag();
  G4int flagParticle=23;
  G4int flagProcess=33;
  G4int flagCreationProcess=43;
  G4int flagCurrentVolume=53;
  
  if (ParticleName == "e-")              flagParticle = 1;    
  else if (ParticleName == "proton")     flagParticle = 2;
  else if (ParticleName == "GenericIon") flagParticle = 3;
  else if (ParticleName == "gamma")      flagParticle = 4;
  else if (ParticleName == "e+")         flagParticle = 5;
  //  else {flagParticle = 23; G4cout << "LOOK PARTICLE " << ParticleName << G4endl;}

  if (ProcessName == "initStep")            flagProcess = 1;
  else if (ProcessName == "msc")            flagProcess = 2;
  else if (ProcessName == "hIoni")          flagProcess = 3;
  else if (ProcessName == "eIoni")          flagProcess = 4;
  else if (ProcessName == "Transportation") flagProcess = 5;
  else if (ProcessName == "eBrem")          flagProcess = 6; 
  else if (ProcessName == "compt")          flagProcess = 7; 
  else if (ProcessName == "phot")           flagProcess = 8;
  else if (ProcessName == "Rayl")           flagProcess = 9;
  else if (ProcessName == "conv")           flagProcess = 10;
  else if (ProcessName == "annihil")        flagProcess = 11;
  //else {flagProcess = 33; G4cout << "LOOK PROCESS " << ProcessName << G4endl;}
  //G4cout << "Process called: " << ProcessName << G4endl;
  //G4cout << "Process called: " << ProcessName << " Step length: " << stepLength/m << " Particle energy: " << energy/eV << endl;

  if (CreationProcessName == "initStep")            flagCreationProcess = 1;
  else if (CreationProcessName == "msc")            flagCreationProcess = 2;
  else if (CreationProcessName == "hIoni")          flagCreationProcess = 3;
  else if (CreationProcessName == "eIoni")          flagCreationProcess = 4;
  else if (CreationProcessName == "Transportation") flagCreationProcess = 5;
  else if (CreationProcessName == "eBrem")          flagCreationProcess = 6; 
  else if (CreationProcessName == "compt")          flagCreationProcess = 7; 
  else if (CreationProcessName == "phot")           flagCreationProcess = 8;
  else if (CreationProcessName == "Rayl")           flagCreationProcess = 9;
  else if (CreationProcessName == "conv")           flagCreationProcess = 10;
  else if (CreationProcessName == "annihil")        flagCreationProcess = 11;
  //else {flagCreationProcess = 43; G4cout << "LOOK PROCESS CREATION" << CreationProcessName << G4endl;}

  if (CurrentVolumeName == "wld_box") flagCurrentVolume = 1;
  else if (CurrentVolumeName == "tgt_box") flagCurrentVolume = 2;
  //else {flagCreationProcess = 53; G4cout << "LOOK VOLUME" << CurrentVolumeName << G4endl;}

  //////////////////////////////////////////////////
  // Add step to histogram
  //////////////////////////////////////////////////
  
  // TO REDUCE FILE SIZE FOR CAMBRIDGE BUILD - ELECTRONS NOT RECOREDED
  //if (flagParticle!=1) {       
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(0, user_track_id);
  analysisManager->FillNtupleDColumn(1, x2/um);
  analysisManager->FillNtupleDColumn(2, y/um);
  analysisManager->FillNtupleDColumn(3, z/um);
  analysisManager->FillNtupleDColumn(4, edep/eV);
  analysisManager->FillNtupleDColumn(5, energy/eV); 
  analysisManager->FillNtupleDColumn(6, step_time/s);
  analysisManager->FillNtupleDColumn(7, flagParticle);
  analysisManager->FillNtupleDColumn(8, flagProcess);
  analysisManager->FillNtupleDColumn(9, flagCreationProcess);
  analysisManager->FillNtupleDColumn(10, momentum_x/um);
  analysisManager->FillNtupleDColumn(11, momentum_y/um);
  analysisManager->FillNtupleDColumn(12, momentum_z/um);
  analysisManager->FillNtupleDColumn(13, flagCurrentVolume);
  analysisManager->FillNtupleDColumn(14, flagAtSurface);
  analysisManager->FillNtupleDColumn(15, flagAugerElectron);
 
  analysisManager->AddNtupleRow(); 
  //}     
}
