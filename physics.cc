#include "physics.hh"
#include "G4StepLimiterPhysics.hh"

MyPhysicsList::MyPhysicsList()
{
// in this constructor we have to register the physics list that we want to define 
// in principle one could register all the physics list, but it will take longer 
// to run the simulations

	G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();

	G4OpticalParameters *opParams = G4OpticalParameters::Instance();
	
	opParams -> SetScintTrackSecondariesFirst(false);

	opParams -> SetScintByParticleType(false);

	//opParams->SetCerenkovTrackSecondariesFirst(false);
	
	RegisterPhysics (opticalPhysics);
	
	RegisterPhysics (new G4EmStandardPhysics());
		
	G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
	
	RegisterPhysics(stepLimitPhys);
	
}

MyPhysicsList::~MyPhysicsList()
{}


