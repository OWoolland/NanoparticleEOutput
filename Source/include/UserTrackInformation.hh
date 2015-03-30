#ifndef UserTrackInformation_h
#define UserTrackInformation_h 1

#include "G4Track.hh"
#include "G4VUserTrackInformation.hh"

class UserTrackInformation : public G4VUserTrackInformation 
{
 public:
  UserTrackInformation();
  virtual ~UserTrackInformation();
   
  void SetUserTrackID();
  G4int GetUserTrackID();

  void SetAugerElectronFlag(G4bool flg);
  G4bool GetAugerElectronFlag();
};

#endif
