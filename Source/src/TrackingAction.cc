#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4VSolid.hh"
#include "G4Region.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "DetectorConstruction.hh"
#include "UserTrackInformation.hh"
#include "Analysis.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"

#include "G4Threading.hh"
#include "G4AutoLock.hh"

using namespace std;

extern G4double alumina_x;
extern G4double alumina_y;
extern G4double alumina_z;

TrackingAction::TrackingAction(DetectorConstruction* detector)
{
    fDetector = detector;
    fTargetRegion = 0;
}

TrackingAction::~TrackingAction()
{
    fDetector = 0;
    fTargetRegion = 0;
}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  //G4cout << "\033[1;31m" << "Begin Tracking" << "\033[0m\n";
  
  // create user info
  UserTrackInformation* trackInfo = new UserTrackInformation();
  trackInfo->SetUserTrackID();
  //trackInfo->SetAugerFlag(true);

  G4int user_track_id = trackInfo->GetUserTrackID();
  G4ThreeVector position = track->GetPosition();
  G4double x = position.getX();
  G4double y = position.getY();
  G4double z = position.getZ();
  G4double edep = 0;
  G4double energy = track->GetKineticEnergy();
  G4double step_time = track->GetGlobalTime();

  G4ThreeVector momentum = track->GetMomentumDirection();
  G4double momentum_x = momentum.x();
  G4double momentum_y = momentum.y();
  G4double momentum_z = momentum.z();

  G4String CurrentVolumeName = track->GetVolume()->GetName();

  G4String ParticleName = track->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4String CreationProcessName = "initStep";
  if(track->GetCreatorProcess()!=0) CreationProcessName = track->GetCreatorProcess()->GetProcessName();

  // set auger electron flag
  trackInfo->SetAugerElectronFlag(track->GetCreatorModelID()==
				  G4PhysicsModelCatalog::GetIndex("phot_auger"));

  G4int flagParticle = 23;
  G4int flagProcess = 1; // Will be inital step
  G4int flagCreationProcess = 43;
  G4int flagCurrentVolume = 53;
  G4int flagAtSurface = 0;
  G4int flagAugerElectron = trackInfo->GetAugerElectronFlag();

  //if (CreationProcessName=="phot"&&ParticleName=="e-") cout << "photo/auger electron trackign begins" << endl;
  //if (ParticleName=="e-") cout << "energy of electron at track start = " << energy/eV << endl;
  
  if (ParticleName == "e-")              flagParticle = 1;    
  else if (ParticleName == "proton")     flagParticle = 2;
  else if (ParticleName == "GenericIon") flagParticle = 3;
  else if (ParticleName == "gamma")      flagParticle = 4;
  else if (ParticleName == "e+")         flagParticle = 5;
  else {flagParticle = 23;} 

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
  //  else {flagCreationProcess = 43; G4cout << "LOOK PROCESS " << CreationProcessName << G4endl;}

  if (CurrentVolumeName == "slc_box") flagCurrentVolume = 1;
  else if (CurrentVolumeName == "wtr_box") flagCurrentVolume = 2;
  else if (CurrentVolumeName == "wld_box") flagCurrentVolume = 3;
  //  else {flagCreationProcess = 53; G4cout << "LOOK VOLUME" << CurrentVolumeName << G4endl;}

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(0, user_track_id);
  analysisManager->FillNtupleDColumn(1, x/um);
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
}

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  UserTrackInformation* trackInfo = (UserTrackInformation*)(track->GetUserInformation());
  G4int user_track_id = trackInfo->GetUserTrackID();
  G4ThreeVector position = track->GetPosition();
  G4double x = position.getX();
  G4double y = position.getY();
  G4double z = position.getZ();
  G4double edep = 0;
  G4double energy = track->GetKineticEnergy();
  G4double step_time = track->GetGlobalTime();

  G4ThreeVector momentum = track->GetMomentumDirection();
  G4double momentum_x = momentum.x();
  G4double momentum_y = momentum.y();
  G4double momentum_z = momentum.z();

  G4String CurrentVolumeName = track->GetVolume()->GetName();

  G4String ParticleName = track->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4String CreationProcessName = "initStep";
   if(track->GetCreatorProcess()!=0) CreationProcessName = track->GetCreatorProcess()->GetProcessName();

  G4int flagParticle = 23;
  G4int flagProcess = 12; // Will be last step
  G4int flagCreationProcess = 43;
  G4int flagCurrentVolume = 53;
  G4int flagAtSurface = 0;
  G4int flagAugerElectron = trackInfo->GetAugerElectronFlag();

  if (ParticleName == "e-")              flagParticle = 1;    
  else if (ParticleName == "proton")     flagParticle = 2;
  else if (ParticleName == "GenericIon") flagParticle = 3;
  else if (ParticleName == "gamma")      flagParticle = 4;
  else if (ParticleName == "e+")         flagParticle = 5;
  else {flagParticle = 23;}

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
  //  else {flagCreationProcess = 43; G4cout << "LOOK PROCESS CREATION" << CreationProcessName << G4endl;}

  if (CurrentVolumeName == "wld_box") flagCurrentVolume = 1;
  else if (CurrentVolumeName == "tgt_box") flagCurrentVolume = 2;
  //  else {flagCreationProcess = 53; G4cout << "LOOK VOLUME" << CurrentVolumeName << G4endl;}
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(0, user_track_id);
  analysisManager->FillNtupleDColumn(1, x/um);
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
}
