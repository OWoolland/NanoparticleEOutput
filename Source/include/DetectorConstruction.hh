#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4Region.hh"
#include "G4SystemOfUnits.hh"

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
  
    G4Region* GetTargetRegion()  {return fRegion;}
    void DefineMaterials();

    G4VPhysicalVolume* ConstructVolumes();

  private:
 
  G4LogicalVolume* world_log;
  G4VPhysicalVolume* world_phys;
  
  G4LogicalVolume* target_log;
  G4VPhysicalVolume* target_phys;

  G4LogicalVolume* ablator_log;
  G4VPhysicalVolume* ablator_phys;

  G4Region* fRegion;

};
#endif
