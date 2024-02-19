#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4AnalysisManager.hh"


class MyEventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackingAction : public G4UserTrackingAction {
  public:  
    TrackingAction(MyEventAction*);
   ~TrackingAction() override;
   
    void  PreUserTrackingAction(const G4Track*) override;
    void PostUserTrackingAction(const G4Track*) override;
        
  private:
    MyEventAction* fEvent = nullptr;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
