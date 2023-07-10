#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction

{
public:
        MyPrimaryGenerator();
        ~MyPrimaryGenerator();

        virtual void GeneratePrimaries(G4Event*);
// This si creating the primary particles that are going to be propagated by the Build() function in the 
// MyActionInitialization class
private:
// here we define the particle gun
	G4GeneralParticleSource *fParticleGun;

};

#endif
