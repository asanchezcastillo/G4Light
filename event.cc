#include "event.hh"
#include "G4AnalysisManager.hh"


MyEventAction::MyEventAction(MyRunAction*)
{
	fEdep = 0.;

}
MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;

}
void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleDColumn(1,0,fEdep);
	man->AddNtupleRow(1);
}

void MyEventAction::SaveEdep(const G4Step* step)
{
	G4double edep = step->GetTotalEnergyDeposit();

	G4double step_length = step->GetStepLength();

	G4ThreeVector stepPosition = step->GetPreStepPoint()->GetPosition();

	G4double xPos = stepPosition[0];
	G4double yPos = stepPosition[1];
	G4double zPos = stepPosition[2];

	G4double time = step->GetPreStepPoint()->GetGlobalTime();	

	G4int pdg = step->GetTrack()->GetDynamicParticle()->GetPDGcode();

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleDColumn(2,0,edep);
	man->FillNtupleDColumn(2,1,xPos);
	man->FillNtupleDColumn(2,2,yPos);
	man->FillNtupleDColumn(2,3,zPos);
	man->FillNtupleDColumn(2,4,time);
	man->FillNtupleIColumn(2,5, pdg);
	man->FillNtupleDColumn(2,6, step_length);
	man->AddNtupleRow(2);
}

