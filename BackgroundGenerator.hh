#ifndef BACKGROUNDGENERATOR_HH
#define BACKGROUNDGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GenericMessenger.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"



class BackgroundGenerator : public G4VUserPrimaryGeneratorAction
{
public:
        BackgroundGenerator();
        ~BackgroundGenerator();

        virtual void BackgroundGeneratePrimaries(G4Event*);
// This si creating the primary particles that are going to be propagated by the Build() function in the 
// MyActionInitialization class
private:

  G4GenericMessenger *fMessenger;

  G4int nAr39; // Number of Ar39 isotopes to simulate over the time window.
  G4int nAr42; // Number of Ar42 isotopes to simulate over the time window.
  G4int nKr85; // Number of Kr85 isotopes to simulate over the time window.
  G4int nK42; // Number of Kr85 isotopes to simulate over the time window.
  G4int nBi214; // Number of Bi214 isotopes to simulate over the time window.
  G4int nPb214; // Number of Pb214 isotopes to simulate over the time window.
  G4int nRn222; // Number of Rn222 isotopes to simulate over the time window

  bool background_;

  G4double GenVolX; // X lenght of the volume in which we simulate interactions
  G4double GenVolY; // Y lenght of the volume in which we simulate interactions
  G4double GenVolZ; // Z lenght of the volume in which we simulate interactions
 
  G4double time_window;

  void GenerateSNBackground(G4Event* anEvent);
  void Generate_Radioisotope(G4Event* anEvent, int Atomic_number, int Atomic_mass, double decay_time);
  G4ThreeVector RandomVertex(G4double , G4double , G4double );
 
};

#endif
