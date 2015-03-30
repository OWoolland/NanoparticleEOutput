// --------------------------------------------------
// Header files
// --------------------------------------------------

#include "DetectorConstruction.hh"

// Material headers
#include "G4Material.hh"
#include "G4NistManager.hh"

// Dimensional headers
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

// Volume headers
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// Solids
#include "G4Box.hh"
#include "G4Orb.hh"

// Debugging
#include "G4Threading.hh"
#include <iostream>
using namespace std;

// Math
#include <stdlib.h>  
#include <math.h>   

// Physics
#include "G4ProductionCuts.hh"

// --------------------------------------------------
// Global Variables
// --------------------------------------------------
  
extern G4double world_x;
extern G4double world_y;
extern G4double world_z;
extern G4double target_x;
extern G4double target_y;
extern G4double target_z;

// --------------------------------------------------
// Local Variables
// --------------------------------------------------

G4NistManager* MaterialManager = G4NistManager::Instance();

G4Material* alumina;
G4Material* gold;
G4Material* silicon;
G4Material* water;
G4Material* graphite;
G4Material* vacuum;

DetectorConstruction::DetectorConstruction()
{ 
  DefineMaterials();
}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();
  alumina = man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  gold = man->FindOrBuildMaterial("G4_Au");
  silicon = man->FindOrBuildMaterial("G4_Si");
  water = man->FindOrBuildMaterial("G4_WATER");
  graphite = man->FindOrBuildMaterial("G4_GRAPHITE");
  vacuum = man->FindOrBuildMaterial("G4_Galactic");
}

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Define World
  G4Box* world_box = new G4Box("wld_box", world_x, world_y, world_z);
  world_log = new G4LogicalVolume(world_box,     // G4VSolid
				  vacuum,        // material
				  "wld_box_log", // name
				  0,             // field manager
				  0,             // sensitive detector
				  0,             // user limits
				  true);         // optimise
  world_phys = new G4PVPlacement(0,                    // rotation
				 G4ThreeVector(0,0,0), // position 
				 world_log,            // logical volume
				 "wld_box",            // name
				 0,                    // mother logical volume
				 false,                // pMany??
				 0,                    // copy number
				 true);                // surface check

  // Define target
  G4Orb* target_box = new G4Orb("wld_box", target_x);
  //G4Box* target_box = new G4Box("target_box", target_x, target_y, target_z);
  target_log = new G4LogicalVolume(target_box,   // G4VSolid
				  gold,          // material
				  "tgt_box_log", // name
				  0,             // field manager
				  0,             // sensitive detector
				  0,             // user limits
				  true);         // optimise
  target_phys = new G4PVPlacement(0,                    // rotation
				  G4ThreeVector(0,0,0), // position 
				  target_log,           // logical volume
				  "tgt_box",            // name
				  world_log,            // mother logical volume
				  false,                // pMany??
				  0,                    // copy number
				  true);                // surface check


  // Create Target G4Region and add logical volume
  G4ProductionCuts* cuts = new G4ProductionCuts();
  
  G4double defCut = 1*nm;
  cuts->SetProductionCut(defCut,"gamma");
  cuts->SetProductionCut(defCut,"e-");
  cuts->SetProductionCut(defCut,"e+");
  cuts->SetProductionCut(defCut,"proton");
  
  fRegion = new G4Region("wld_box");
  fRegion->SetProductionCuts(cuts);

  return world_phys;
}
