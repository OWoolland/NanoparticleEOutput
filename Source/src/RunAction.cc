// needs editing

#include "RunAction.hh"
#include "TrackingAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4ParticleDefinition.hh"
#include "G4MTRunManager.hh"
#include "G4Threading.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

extern G4int id_store;

RunAction::RunAction()
{
  fpTrackingAction = 0;
  fInitialized = 0;
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  if(!fInitialized) InitializeWorker(run);
  CreateHistogram();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  WriteHistogram();
  delete G4AnalysisManager::Instance();
}

void RunAction::InitializeWorker(const G4Run*)
{
  //  if (fpTrackingAction == 0)
    fpTrackingAction =
      (TrackingAction*) G4RunManager::GetRunManager()->GetUserTrackingAction();
  
  fInitialized = true;
}

void RunAction::CreateHistogram()
{
  //G4cout << "##### Create analysis manager " << "  " << this << G4endl;
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->SetVerboseLevel(0);
  
  //G4String fileName = "NanoparticleEOutput";
  G4String fileName = "EscapeDepthOutput";
  analysisManager->OpenFile(fileName);
  
  analysisManager->CreateNtuple("state_space", "states");
  analysisManager->CreateNtupleDColumn("particleID");
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleDColumn("Time");
  analysisManager->CreateNtupleDColumn("Particle");
  analysisManager->CreateNtupleDColumn("ProcessID");  
  analysisManager->CreateNtupleDColumn("CreationProcess");  
  analysisManager->CreateNtupleDColumn("momentum_x");
  analysisManager->CreateNtupleDColumn("momentum_y");
  analysisManager->CreateNtupleDColumn("momentum_z");
  analysisManager->CreateNtupleDColumn("current_volume");
  analysisManager->CreateNtupleDColumn("surface");
  analysisManager->CreateNtupleDColumn("Auger");
  analysisManager->FinishNtuple();
}

void RunAction::WriteHistogram()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
