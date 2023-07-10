#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{   
    
    G4double edep = step->GetTotalEnergyDeposit();

    int pdg = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
    
    if(pdg!=0 && pdg!=22 && pdg!=-22)
    {
    fEventAction->AddEdep(edep);
    fEventAction->SaveEdep(step);
    }

}
