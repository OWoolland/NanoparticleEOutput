#include "UserTrackInformation.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

extern G4int id_store;
G4int user_track_id_store;
G4bool augerElectronFlag;

UserTrackInformation::UserTrackInformation()
  : G4VUserTrackInformation()
{
  augerElectronFlag = false;
}

UserTrackInformation::~UserTrackInformation()
{}

void UserTrackInformation::SetUserTrackID(){
  user_track_id_store = id_store;
  id_store++;
}

G4int UserTrackInformation::GetUserTrackID(){
  return user_track_id_store;
}

void UserTrackInformation::SetAugerElectronFlag(G4bool flg){
  augerElectronFlag = flg;
}

G4bool UserTrackInformation::GetAugerElectronFlag(){
  return augerElectronFlag;
}
