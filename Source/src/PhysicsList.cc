#include "PhysicsList.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmDNAPhysics.hh"
#include "G4DecayPhysics.hh"

#include "G4LossTableManager.hh"
#include "G4EmConfigurator.hh"
#include "G4UnitsTable.hh"

#include "G4ProcessManager.hh"
#include "G4Decay.hh"

#include "StepMax.hh"
#include "NISTElasticScatter.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4VAtomDeexcitation.hh"
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4ProductionCutsTable.hh"

#include "G4DummyModel.hh"
#include "G4UniversalFluctuation.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList(),
			     fEmPhysicsList(0),
			     fDecPhysicsList(0),
			     fHadronPhys(),    
			     fStepMaxProcess(0)//,
			     //fOliProcess(0)
{
  //G4LossTableManager::Instance();

  //fStepMaxProcess = 0;
  //fOliProcess = 0;

  //SetVerboseLevel(0);

  // EM physics
  //fEmPhysicsList = new G4EmStandardPhysics_option3();      
  fEmPhysicsList = new G4EmLivermorePhysics();
  //fEmPhysicsList = new G4EmDNAPhysics();

  // Deacy physics
  fDecPhysicsList = new G4DecayPhysics();
}

PhysicsList::~PhysicsList()
{
  delete fEmPhysicsList;
  delete fDecPhysicsList;
  for(size_t i=0; i<fHadronPhys.size(); i++) {delete fHadronPhys[i];}
}

void PhysicsList::ConstructParticle()
{
  fEmPhysicsList->ConstructParticle();
  //fDecPhysicsList->ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  
  fEmPhysicsList->ConstructProcess();
  fDecPhysicsList->ConstructProcess();
  for(size_t i=0; i<fHadronPhys.size(); i++) {
    fHadronPhys[i]->ConstructProcess();
  }
  SetCuts();

  //AddStepMax();
}

//////////////////////////////////////////////////
// Set Cuts and step limits
//////////////////////////////////////////////////

/*void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  //fStepMaxProcess = new StepMax();
  fOliProcess = new NISTElasticScatter();

  theParticleIterator->reset();
  while ((*theParticleIterator)()) {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (fOliProcess->IsApplicable(*particle) && pmanager){
      //pmanager->AddDiscreteProcess(fOliProcess);
    }
  }
  }*/

void PhysicsList::SetCuts()
{
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(50*eV, 400*MeV);
  SetCutValue(1*nm, "gamma");
  SetCutValue(1*nm, "e-");
  SetCutValue(1*nm, "e+");
  SetCutValue(1*nm, "proton");
}
