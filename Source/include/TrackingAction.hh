#ifndef TrackingAction_h
#define TrackingAction_h

#include "G4UserTrackingAction.hh"
#include <map>

class G4Region;
class G4ParticleDefinition;
class DetectorConstruction;

class TrackingAction : public G4UserTrackingAction
{
  public:
    TrackingAction(DetectorConstruction* detector = 0);
    ~TrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

    void SetDetector(DetectorConstruction* detector) {
      fDetector = detector;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInTarget() {
      return fNParticleInTarget;
    }

    std::map<const G4ParticleDefinition*, int>& GetNParticlesCreatedInWorld() {
      return fNParticleInWorld;
    }

  private:
    DetectorConstruction* fDetector;
    G4Region* fTargetRegion;
    std::map<const G4ParticleDefinition*, int> fNParticleInTarget;
    std::map<const G4ParticleDefinition*, int> fNParticleInWorld;
};
#endif 
