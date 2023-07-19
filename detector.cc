#include "detector.hh"
#include "run.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) :
G4VSensitiveDetector(name)
{
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory *R0hist)
{
	
 G4int pdg = aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();
 const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
 G4int copyNo = touchable->GetCopyNumber();
 G4VPhysicalVolume *currentVolume = touchable->GetVolume();
 G4String volumeName = currentVolume->GetName();

 G4String particleName = aStep->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();

//if( (pdg==0) && (volumeName=="physDetector"))

 if( (particleName == "opticalphoton" ) && (volumeName=="physDetector") )
{
// Here we want to get info about the position of our photon. 
// We have to access the track of the particle
	G4Track *track = aStep->GetTrack();
// with this line we kill the trajectory of the photon as soon as it enters the detector
	G4ThreeVector vertexPosition =track->GetVertexPosition();

	G4String CreatorProcess = aStep->GetTrack() ->GetCreatorProcess() -> GetProcessName();
	G4double time_track;
	track->SetTrackStatus(fStopAndKill);
	time_track = track->GetGlobalTime();
    G4double local_time = track->GetLocalTime();	

// For each step, we also can define two steps points, preStepPoint (when the photon enters the sensitive detector)
// and poststepPoint (when the photon leaves the sensitive detector))
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	G4double time_step = preStepPoint->GetGlobalTime();

	G4double edep = aStep->GetTotalEnergyDeposit();

	G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
 	
	G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03; //wlen in nm
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->FillNtupleIColumn(0,0, copyNo);
	man->FillNtupleIColumn(0,1,runID);
	man->FillNtupleDColumn(0,2,wlen);
    man->FillNtupleDColumn(0,3,vertexPosition[0]/10);
	man->FillNtupleDColumn(0,4,vertexPosition[1]/10);
	man->FillNtupleDColumn(0,5,vertexPosition[2]/10);
	man->FillNtupleDColumn(0,7,time_step);
	man->FillNtupleDColumn(0,8,local_time);
	man->AddNtupleRow(0);
}

else if (particleName != "opticalphoton")
{
	G4Track *track = aStep->GetTrack();
	G4double time_track;
	time_track = track->GetGlobalTime();
	G4int parentID = track->GetParentID();
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector position_start = aStep->GetPreStepPoint()->GetPosition();

	G4double time_start = preStepPoint->GetGlobalTime()/CLHEP::ns;

	G4double time_end = preStepPoint->GetGlobalTime()/CLHEP::ns;

	G4double edep = aStep->GetTotalEnergyDeposit()/CLHEP::MeV;

	if(edep!=0)
	{
		G4int pdg = aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();

		G4ThreeVector position_end = aStep->GetPostStepPoint()->GetPosition();

		G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
		G4int runID = G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID();

		G4double length = aStep->GetStepLength()/CLHEP::cm;

		G4AnalysisManager *man = G4AnalysisManager::Instance();
		man->FillNtupleDColumn(3,0,edep);
		man->FillNtupleDColumn(3,1,position_start[0]/10);
		man->FillNtupleDColumn(3,2,position_start[1]/10);
		man->FillNtupleDColumn(3,3,position_start[2]/10);
		man->FillNtupleDColumn(3,4,position_end[0]/10);
		man->FillNtupleDColumn(3,5,position_end[1]/10);
		man->FillNtupleDColumn(3,6,position_end[2]/10);
		man->FillNtupleDColumn(3,7,time_start);
		man->FillNtupleDColumn(3,8,time_end);
		man->FillNtupleIColumn(3,9,pdg);
		man->FillNtupleIColumn(3,10,eventID);
		man->FillNtupleDColumn(3,11,length);
		man->FillNtupleIColumn(3,12,parentID);
		man->FillNtupleIColumn(3,13,runID);
		man->AddNtupleRow(3);
	}
}

return true;

}
