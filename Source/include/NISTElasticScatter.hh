#ifndef NISTElasticScatter_h
#define NISTElasticScatter_h 1

// Headers
#include "globals.hh"
#include "G4VDiscreteProcess.hh"

// Class
class NISTElasticScatter : public G4VDiscreteProcess {

public:
  NISTElasticScatter(const G4String& processName = "NISTElastic");
  ~NISTElasticScatter();

  virtual G4bool IsApplicable(const G4ParticleDefinition&);

  virtual G4double AtRestGetPhysicalInteractionLength(const G4Track&, G4ForceCondition*);
  virtual G4double AlongStepGetPhysicalInteractionLength(const G4Track &, G4double, G4double, G4double &, G4GPILSelection *);
  virtual G4double PostStepGetPhysicalInteractionLength(const G4Track&, G4double, G4ForceCondition*);
  
  virtual G4VParticleChange* AtRestDoIt(const G4Track&, const G4Step&);
  virtual G4VParticleChange* AlongStepDoIt(const G4Track&, const G4Step&);
  virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

  virtual G4double GetMeanFreePath (const G4Track&, G4double, G4ForceCondition*);

  G4double RandomTheta();

private:
    
};

#endif
