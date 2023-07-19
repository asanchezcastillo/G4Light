#ifndef SUPERNOVAGENERATOR_HH
#define SUPERNOVAGENERATOR_HH


#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"
// Standard library includes
#include <string>

// Geant4 includes
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericMessenger.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"

// MARLEY includes
#include "marley/Generator.hh"

// ROOT includes 
#include "TROOT.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

class SupernovaGenerator : public G4VUserPrimaryGeneratorAction

{
public:
        SupernovaGenerator();
        ~SupernovaGenerator();

        virtual void GeneratePrimaries(G4Event*);
// This si creating the primary particles that are going to be propagated by the Build() function in the 
// MyActionInitialization class
private:
 	
  G4GenericMessenger *fMessenger; // Messenger for configuration
  
  bool randomVertex_; 
  size_t NSNNeutrino;
  G4PrimaryVertex* vertex; //Neutrino interaction vertex 
  G4double vertex_x_;
  G4double vertex_y_;
  G4double vertex_z_;

  G4double GenVolX; // X lenght of the volume in which we simulate interactions
  G4double GenVolY; // Y lenght of the volume in which we simulate interactions
  G4double GenVolZ; // Z lenght of the volume in which we simulate interactions

  G4double time_window; // Time window to simulate background

  std::string marleyConfig;

  bool background_; //Whether to include background
  G4int nAr39; // Number of Ar39 isotopes to simulate over the time window.
  G4int nAr42; // Number of Ar42 isotopes to simulate over the time window.
  G4int nKr85; // Number of Kr85 isotopes to simulate over the time window.
  G4int nK42; // Number of Kr85 isotopes to simulate over the time window.
  G4int nBi214; // Number of Bi214 isotopes to simulate over the time window.
  G4int nPb214; // Number of Pb214 isotopes to simulate over the time window.
  G4int nRn222; // Number of Rn222 isotopes to simulate over the time window

  marley::Generator marley_generator_;

  TH1D  * th1_;
  TH2D  * th2_;
  TFile * tfile_;

  G4ThreeVector RandomVertex(G4double , G4double , G4double );
  G4double SampleTime(G4double);

  void MarleyInitialize(std::string); // Initialize the marley::generator object
  void MarleyGeneratePrimaries(G4Event*); // Generate Marley neutrinos
  void BackgroundGeneratePrimaries(G4Event*); // Generate the background for all radioisotopes

  void Generate_Radioisotope(G4Event* anEvent, int Atomic_number, int Atomic_mass, double decay_time); // Function to generate radioisotopes

};

#endif
