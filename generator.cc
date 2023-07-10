#include "generator.hh"
#include "Randomize.hh"
#include <G4INCLRandom.hh>
#include "G4RandomDirection.hh"
#include "G4GeneralParticleSource.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4GeneralParticleSource(); 
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
