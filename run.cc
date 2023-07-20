#include "run.hh"
MyRunAction::MyRunAction()
{
 	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->SetNtupleMerging(true);
	man->CreateNtuple("Photons","Photons");
    man->CreateNtupleIColumn("detectorCopy");
	man->CreateNtupleIColumn("runID");
	man->CreateNtupleDColumn("fWlen");
	man->CreateNtupleDColumn("fVertexX");
	man->CreateNtupleDColumn("fVertexY");
	man->CreateNtupleDColumn("fVertexZ");
	man->CreateNtupleIColumn("entries");
	man->CreateNtupleDColumn("Time_step");
	man->CreateNtupleDColumn("Time_local");
	man->FinishNtuple(0);

	man->CreateNtuple("Scoring", "Scoring");
 	man->CreateNtupleDColumn("TotalEdep");
	man->FinishNtuple(1);
	
	man->CreateNtuple("EnergyDeposition", "EnergyDeposition");
    man->CreateNtupleDColumn("edep");
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->CreateNtupleDColumn("time");
	man->CreateNtupleIColumn("pdg");
	man->CreateNtupleDColumn("step_length");
    man->FinishNtuple(2);

 	man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleDColumn("hit_energy_deposit");
	man->CreateNtupleDColumn("hit_start_x");
	man->CreateNtupleDColumn("hit_start_y");
	man->CreateNtupleDColumn("hit_start_z");
	man->CreateNtupleDColumn("hit_end_x");
	man->CreateNtupleDColumn("hit_end_y");
	man->CreateNtupleDColumn("hit_end_z");
	man->CreateNtupleDColumn("hit_start_t");
	man->CreateNtupleDColumn("hit_end_t");
	man->CreateNtupleIColumn("pdg");
	man->CreateNtupleIColumn("eventID");
	man->CreateNtupleDColumn("hit_length");
	man->CreateNtupleIColumn("run");
    man->FinishNtuple(3);

	man->CreateNtuple("InitialParticle", "InitialParticle");
    man->CreateNtupleIColumn("InitialParticlePDG");
	man->CreateNtupleDColumn("InitialParticleEnergy");
	man->CreateNtupleDColumn("InitialParticlePx");
	man->CreateNtupleDColumn("InitialParticlePy");
	man->CreateNtupleDColumn("InitialParticlePz");
	man->CreateNtupleDColumn("InteractionTime");
	man->FinishNtuple(4);
	
	man->CreateNtuple("PrimaryParticle", "Primary");
    man->CreateNtupleIColumn("PrimaryParticlePDG");
	man->CreateNtupleDColumn("PrimaryParticleEnergy");
	man->CreateNtupleDColumn("PrimaryParticlePx");
	man->CreateNtupleDColumn("PrimaryParticlePy");
	man->CreateNtupleDColumn("PrimaryParticlePz");
	man->FinishNtuple(5);

	man->CreateNtuple("Background", "Background");
	man->CreateNtupleDColumn("DecayTime");
	man->FinishNtuple(6);
}


MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	// First of all is to know where the output file has to be created
	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;
	man->OpenFile("analysis/output"+strRunID.str()+ ".root");
	//Random seed to obtain different events
	std::cout << " ----------------------------------------> Setting a new seed " << std::endl; 
	G4Random::setTheEngine(new CLHEP::RanecuEngine());
	G4long seed = time(NULL);
	G4Random::setTheSeed(seed);

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
    man->CloseFile();
}


