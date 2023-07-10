

// Standard library includes
#include <iostream>

// Geant4 includes
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "BackgroundGenerator.hh"

//#include "globals.hh"

BackgroundGenerator::BackgroundGenerator()
{

}

BackgroundGenerator::~BackgroundGenerator()
{
delete fMessenger;	
}

void BackgroundGenerator::BackgroundGeneratePrimaries(G4Event* anEvent)
{ 
    
  if(background_) GenerateSNBackground(anEvent); 

}

void BackgroundGenerator::GenerateSNBackground(G4Event* anEvent)
{

  for(int i =0 ; i< nAr39 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 18, 39, decay_time);
  }

  for(int i =0 ; i< nAr42 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 18, 42, decay_time);
  }

  for(int i =0 ; i< nKr85 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 36, 85, decay_time);
  }

  for(int i =0 ; i< nK42 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 19, 42, decay_time);
  }

  for(int i =0 ; i< nBi214 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 83, 214, decay_time);
  }

  for(int i =0 ; i< nPb214 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 82, 214, decay_time);
  }

  for(int i =0 ; i< nRn222 ; i++)
  {
  double decay_time = G4UniformRand()-0.5 * time_window;
  Generate_Radioisotope(anEvent, 86, 222, decay_time);
  }

}

G4ThreeVector BackgroundGenerator::RandomVertex(G4double GenVolX_, G4double GenVolY_, G4double GenVolZ_)
{
  G4double vertexX = GenVolX_ * (G4UniformRand()-0.5);
  G4double vertexY = GenVolY_ * (G4UniformRand()-0.5);
  G4double vertexZ = GenVolZ_ * (G4UniformRand()-0.5);
  G4ThreeVector vertexPosition = G4ThreeVector(vertexX,vertexY,vertexZ);

  return vertexPosition;
}

void BackgroundGenerator::Generate_Radioisotope(G4Event* anEvent, int Atomic_Number, int Atomic_Mass, double decay_time)
{
G4ParticleDefinition* pdef = G4IonTable::GetIonTable()->GetIon(Atomic_Number, Atomic_Mass, 0.); 
if (!pdef)G4Exception("SetParticleDefinition()", "[IonGun]",FatalException, " can not create ion ");
pdef->SetPDGLifeTime(1.*ps);
G4PrimaryParticle* particle = new G4PrimaryParticle(pdef);
const G4ThreeVector momentum_direction = G4ThreeVector(0,0,1);
particle->SetMomentumDirection(momentum_direction);
particle->SetKineticEnergy(1.*eV);

G4ThreeVector vertexPosition = RandomVertex(GenVolX,GenVolY,GenVolZ);
G4PrimaryVertex* bg_vertex = new G4PrimaryVertex(vertexPosition, decay_time);
bg_vertex->SetPrimary(particle);
anEvent->AddPrimaryVertex(bg_vertex);
}
