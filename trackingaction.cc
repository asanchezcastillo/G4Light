
#include "trackingaction.hh"

#include "run.hh"
#include "event.hh"

#include "G4Track.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(MyEventAction* event)
:fEvent(event)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::~TrackingAction()
{
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{    
  G4int PDG = track->GetDynamicParticle()->GetPDGcode();
  G4double Energy = track->GetKineticEnergy();
  G4int trackID = track->GetTrackID();
  G4int parentID;
  if(track->GetParentID()) parentID = track->GetParentID();
  else parentID = -1;
  G4String creatorProcess;
  if(track->GetCreatorProcess()) creatorProcess = track->GetCreatorProcess()->GetProcessName();
  else creatorProcess = "Primary";
  G4double creationTime = track->GetGlobalTime();
  
/* For now leave this commented out and save all particles
  bool nuclearExcitedState=false;
    if (PDG >= 1000000000 && PDG <= 1999999999) {
        if (PDG % 10 != 0) {
            nuclearExcitedState = true;
        }
    }
  if(nuclearExcitedState)
  {
    std::cout << " So i am killing the particle " << std::endl;
    const_cast<G4Track*>(track)->SetTrackStatus(fStopAndKill); // I did a fishy transformation here... const_cast should not be allowed
    return; // We are not interested in particles coming from nuclear excited states
  } 
*/ 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(5,0,PDG);
  man->FillNtupleDColumn(5,1,Energy);
  man->FillNtupleIColumn(5,2,trackID);
  man->FillNtupleIColumn(5,3,parentID);
  man->FillNtupleSColumn(5,4,creatorProcess);
  man->FillNtupleDColumn(5,5,creationTime);
  man->AddNtupleRow(5);            // MeV
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

