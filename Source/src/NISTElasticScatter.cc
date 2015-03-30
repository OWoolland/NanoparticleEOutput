#include "NISTElasticScatter.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4DataSet.hh"
#include "G4DataVector.hh"

#include "G4CrossSectionDataSet.hh"
#include "G4LinInterpolation.hh"

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

G4GPILSelection particleSelection;
G4ParticleChange particleChange;

G4CrossSectionDataSet * angularDistributionDataSet;
G4CrossSectionDataSet * transportDataSet;

G4double particleEnergy;

//////////////////////////////////////////////////
// Constructor / Destructor 
//////////////////////////////////////////////////

NISTElasticScatter::NISTElasticScatter(const G4String& processName)
  : G4VDiscreteProcess(processName) {
  // Load cross section tables
  G4LinInterpolation* algo = new G4LinInterpolation;
  
  angularDistributionDataSet = new G4CrossSectionDataSet(algo->Clone(), eV, m2);
  angularDistributionDataSet->LoadData("CompiledTable");

  transportDataSet = new G4CrossSectionDataSet(algo->Clone(), eV, m);
  transportDataSet->LoadData("64_AU_EMFP");
}

NISTElasticScatter::~NISTElasticScatter()
{
}

//////////////////////////////////////////////////
// General methods
//////////////////////////////////////////////////

G4bool NISTElasticScatter::IsApplicable(const G4ParticleDefinition&)
{
  // Add applicability conditions
  return true;
}

G4double NISTElasticScatter::GetMeanFreePath (const G4Track &aTrack, G4double, G4ForceCondition *condition)
{
  particleEnergy = aTrack.GetKineticEnergy();
  G4double meanFreePath = transportDataSet->FindValue(particleEnergy,0);

  if (particleEnergy > 250*eV) {cout << "fail high" << endl; meanFreePath = DBL_MAX;}
  else if (particleEnergy < 50*eV) {cout << "fail low" << endl; meanFreePath = DBL_MAX;}
 
  return meanFreePath;
}

//////////////////////////////////////////////////
// Interaction length methods
//////////////////////////////////////////////////

G4double NISTElasticScatter::AtRestGetPhysicalInteractionLength (const G4Track &aTrack, G4ForceCondition *condition)
{
  // dummy
  G4double ProposedStep = DBL_MAX;
  return ProposedStep;
}

G4double NISTElasticScatter::AlongStepGetPhysicalInteractionLength (const G4Track &aTrack, G4double previousStepSize, G4double currentMinimumStep, G4double &currentSafety, G4GPILSelection *selection)
{
  // dummy
  G4double ProposedStep = DBL_MAX;
  return ProposedStep;
}

G4double NISTElasticScatter::PostStepGetPhysicalInteractionLength(const G4Track& aTrack, G4double previousStepSize, G4ForceCondition* condition )
{
  //particleEnergy = 50*eV;
  particleEnergy = aTrack.GetKineticEnergy();

  G4double ProposedStep = transportDataSet->FindValue(particleEnergy,0);

  if (particleEnergy > 250*eV) {cout << "fail high" << endl; ProposedStep = DBL_MAX;}
  else if (particleEnergy < 50*eV) {cout << "fail low" << endl; ProposedStep = DBL_MAX;}
 
  return ProposedStep;
}

//////////////////////////////////////////////////
// Do it methods
//////////////////////////////////////////////////

G4VParticleChange* NISTElasticScatter::AtRestDoIt(const G4Track& aTrack, const G4Step& step)
{
  // dummy
  particleChange.Initialize(aTrack);
  return &particleChange;
}

G4VParticleChange* NISTElasticScatter::AlongStepDoIt(const G4Track & aTrack, const G4Step& step)
{
  // dummy
  particleChange.Initialize(aTrack);
  return &particleChange;
}

G4VParticleChange* NISTElasticScatter::PostStepDoIt(const G4Track & aTrack, const G4Step& step)
{
  particleChange.Initialize(aTrack);

  // Choose scattering angles
  G4double thetaDegrees = RandomTheta();
  G4double phiDegrees = G4UniformRand()*360;

  G4double theta = (thetaDegrees/180)*pi;
  G4double phi = (phiDegrees/180)*pi;
  
  //cout << "THETAGREP," << theta << "," << particleEnergy << "," << endl;

  G4ThreeVector currentMomentumDirection = *particleChange.GetMomentumDirection();
  G4ThreeVector proposedMomentumDirection = currentMomentumDirection;
  proposedMomentumDirection.setTheta(theta);
  proposedMomentumDirection.setPhi(phi);
  particleChange.ProposeMomentumDirection(proposedMomentumDirection);
  
  return &particleChange;
}

G4double NISTElasticScatter::RandomTheta()
{
  //////////////////////////////////////////////////
  // Obtain pdf at particle energy
  //////////////////////////////////////////////////

  // Find total across angles
  G4double totalCrossSection = angularDistributionDataSet->FindValue(particleEnergy,0);

  // Find each value as a fraction of the total
  G4DataVector pdf;
  pdf.clear(); 
  for (G4int i = 0; i!=180; ++i) {
      G4double value = angularDistributionDataSet->GetComponent(i)
	                                         ->FindValue(particleEnergy,0);
      pdf.push_back(value/totalCrossSection);
    }

  //////////////////////////////////////////////////
  // Obtain random angle
  //////////////////////////////////////////////////

  G4double pdfMax = *max_element(pdf.begin(),pdf.end()); // find pdf maximum
  G4double randAngle = floor(G4UniformRand()*180); // randomly select angle
  G4double randY = G4UniformRand()*pdfMax; // Generate random number between 0 and pdfMax
  while(pdf[randAngle]<randY) {
    randAngle = floor(G4UniformRand()*180); 
    randY = G4UniformRand()*pdfMax;
    //cout << "Sample reject" << endl;
  }
  //cout << "Sample accept" << endl;
  G4double theta = randAngle;
  
  return theta;
}
