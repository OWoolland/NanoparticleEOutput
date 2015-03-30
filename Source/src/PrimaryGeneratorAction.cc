// --------------------------------------------------
// Header Files
// --------------------------------------------------

#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

// --------------------------------------------------
// Global Variables
// --------------------------------------------------

// --------------------------------------------------
// Local Variables
// --------------------------------------------------

G4GeneralParticleSource* ParticleGun;

static G4int countRuns = 0;
unsigned long long int firstTime = 0;
unsigned long long int currentTime = 0;

// --------------------------------------------------
// Class begin
// --------------------------------------------------

PrimaryGeneratorAction::PrimaryGeneratorAction():
  G4VUserPrimaryGeneratorAction()
{
  firstTime = time(NULL);
  ParticleGun = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Progress bar
  countRuns++;
  currentTime = time(NULL);
   if(countRuns%1000000==0) {
    printf("%.0e primary particles generated ",(G4double)countRuns);
    printf("with %.0f minutes elapsed\n",(double)(currentTime-firstTime)/60);
  }

  // Generate event
  ParticleGun->GeneratePrimaryVertex(anEvent);
}
