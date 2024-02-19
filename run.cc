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
	man->CreateNtupleIColumn("hit_track_id");
    man->FinishNtuple(1);

	man->CreateNtuple("InitialParticle", "InitialParticle");
    man->CreateNtupleIColumn("InitialParticlePDG");
	man->CreateNtupleDColumn("InitialParticleEnergy");
	man->CreateNtupleDColumn("InitialParticlePx");
	man->CreateNtupleDColumn("InitialParticlePy");
	man->CreateNtupleDColumn("InitialParticlePz");
	man->CreateNtupleDColumn("InteractionVertexX");
	man->CreateNtupleDColumn("InteractionVertexY");
	man->CreateNtupleDColumn("InteractionVertexZ");
	man->CreateNtupleDColumn("InteractionTime");
	man->FinishNtuple(2);
	
	man->CreateNtuple("PrimaryParticle", "Primary");
    man->CreateNtupleIColumn("PrimaryParticlePDG");
	man->CreateNtupleDColumn("PrimaryParticleEnergy");
	man->CreateNtupleDColumn("PrimaryParticlePx");
	man->CreateNtupleDColumn("PrimaryParticlePy");
	man->CreateNtupleDColumn("PrimaryParticlePz");
	man->CreateNtupleDColumn("PrimaryParticleTime");
	man->FinishNtuple(3);

	man->CreateNtuple("Background", "Background");
	man->CreateNtupleDColumn("DecayTime");
	man->CreateNtupleIColumn("AtomicNumber");
	man->CreateNtupleIColumn("AtomicMass");
	man->CreateNtupleDColumn("BackgroundVertexX");
	man->CreateNtupleDColumn("BackgroundVertexY");
	man->CreateNtupleDColumn("BackgroundVertexZ");
	man->FinishNtuple(4);

	man->CreateNtuple("ParticleTracking", "ParticleTracking");
	man->CreateNtupleIColumn("PDG");
	man->CreateNtupleDColumn("Energy");
	man->CreateNtupleIColumn("TrackID");
	man->CreateNtupleIColumn("ParentID");
	man->CreateNtupleSColumn("CreatorProcess");
	man->CreateNtupleDColumn("CreationTime");
	man->FinishNtuple(5);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	// First of all is to know where the output file has to be created
	std::cout << " Starting action " << std::endl;
	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;
	man->OpenFile("analysis/output"+strRunID.str()+ ".root");
	//Random seed to obtain different events
	G4Random::setTheEngine(new CLHEP::RanecuEngine());
	long seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
	G4Random::setTheSeed(seed);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	std::cout << " Closing action " << std::endl;
    G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
    man->CloseFile();
}


