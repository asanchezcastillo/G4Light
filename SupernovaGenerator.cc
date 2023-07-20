/// Class in chargge of controlling the generation of SN neutrinos and background

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
//#include "globals.hh"

// MARLEY includes
#include "marley/Event.hh"
#include "marley/Particle.hh"
#ifdef USE_ROOT
  #include "marley/RootJSONConfig.hh"
#else
  #include "marley/JSONConfig.hh"
#endif
// marg4 includes
#include "SupernovaGenerator.hh"

SupernovaGenerator::SupernovaGenerator() : G4VUserPrimaryGeneratorAction()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  // std::default_random_engine generator(seed);
  fMessenger = new G4GenericMessenger(this, "/SNGenerator/", "Marley input");
  fMessenger->DeclareProperty("MarleyConfig", marleyConfig, "Name of the Marley configuration file.");
  fMessenger->DeclareProperty("NSNNeutrino", NSNNeutrino, "Number of SN neutrino");
  fMessenger->DeclareProperty("RandomVertex", randomVertex_, "Random Vertex");
  fMessenger->DeclarePropertyWithUnit("TimeWindow", "s", time_window, "Time window to simulate background");
  fMessenger->DeclarePropertyWithUnit("VertexX", "cm" , vertex_x_,"X coordinate of the interaction vertex");
  fMessenger->DeclarePropertyWithUnit("VertexY", "cm", vertex_y_,"Y coordinate of the interaction vertex");
  fMessenger->DeclarePropertyWithUnit("VertexZ", "cm",  vertex_z_, "Z coordinate of the interaction vertex");
  fMessenger->DeclarePropertyWithUnit("GenVolX", "cm", GenVolX ,"Length in the X dimension of the volume in which we will generate events");
  fMessenger->DeclarePropertyWithUnit("GenVolY", "cm", GenVolY ,"Length in the Y dimension of the volume in which we will generate events");
  fMessenger->DeclarePropertyWithUnit("GenVolZ", "cm", GenVolZ ,"Length in the Z dimension of the volume in which we will generate events");
  fMessenger->DeclareProperty("Background", background_, "Whether to simulate background");
  fMessenger->DeclareProperty("nAr39", nAr39, "Number of Ar39 isotopes to simulate over the time window.");
  fMessenger->DeclareProperty("nAr42", nAr42, "Number of Ar42 isotopes to simulate over the time window.");
  fMessenger->DeclareProperty("nKr85", nKr85, "Number of Kr85 isotopes to simulate over the time window.");
  fMessenger->DeclareProperty("nK42", nK42, "Number of K42 isotopes to simulate over the time window.");
  //fMessenger->DeclareProperty("nCo60", nCo60, "Number of Co60 isotopes to simulate over the time window."); From CPA. Not sure there will be a CPA.
  fMessenger->DeclareProperty("nBi214", nBi214, "Number of Bi214 isotopes to simulate over the time window.");
  fMessenger->DeclareProperty("nPb214", nPb214, "Number of Pb214 isotopes to simulate over the time window.");
  fMessenger->DeclareProperty("nRn222", nRn222, "Number of Rn222 isotopes to simulate over the time window.");
  //fMessenger->DeclareProperty("Po210", Po210, "Number of Po210 isotopes to simulate over the time window."); From APA. Not sure there will be an APA.
}


SupernovaGenerator::~SupernovaGenerator()
{
  delete fMessenger;	
}

void SupernovaGenerator::GeneratePrimaries(G4Event* anEvent)
{
 this->MarleyInitialize(marleyConfig); // Initialize marley generator
 for(size_t i = 0; i<NSNNeutrino; i++) this->MarleyGeneratePrimaries(anEvent); // Generate marley primary particles
 if(background_) this->BackgroundGeneratePrimaries(anEvent); // Generate radiological background
}

void SupernovaGenerator::MarleyGeneratePrimaries(G4Event* anEvent)
{ 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  // Create a new primary vertex 
  vertex = new G4PrimaryVertex(0, 0, 0, 0); // x,y,z,t0

  // Generate a new MARLEY event using the owned marley::Generator object
  marley::Event ev = marley_generator_.create_event();

  // This line, if uncommented, will print the event in ASCII format
  // to standard output
  //std::cout << ev << '\n';
    G4double neutrino_energy;
    G4double interaction_time;
    for ( const auto& fp : ev.get_initial_particles() ) {
    // Get the initial particles of the event. This is just to store this information into the tree.
    G4PrimaryParticle* particle = new G4PrimaryParticle( fp->pdg_code(), fp->px(), fp->py(), fp->pz(), fp->total_energy() );
    // Also set the charge of the G4PrimaryParticle appropriately
    particle->SetCharge( fp->charge() );
    G4int InitialPDG = particle->GetPDGcode();
    G4double InitialEnergy = particle->GetTotalEnergy();
    G4double InitialPx = particle->GetPx();
    G4double InitialPy = particle->GetPy();
    G4double InitialPz = particle->GetPz();
/*    if (std::abs(particle->GetPDGcode()) == 12 or
    std::abs(particle->GetPDGcode()) == 14 or
    std::abs(particle->GetPDGcode()) == 16 or
    std::abs(particle->GetPDGcode()) == 18)
    */
    {
      neutrino_energy=InitialEnergy;
      interaction_time=SampleTime(neutrino_energy);
      man->FillNtupleIColumn(4,0,InitialPDG);
      man->FillNtupleDColumn(4,1,InitialEnergy);
      man->FillNtupleDColumn(4,2,InitialPx);
      man->FillNtupleDColumn(4,3,InitialPx);
      man->FillNtupleDColumn(4,4,InitialPx);
      man->FillNtupleDColumn(4,5,interaction_time);
      man->AddNtupleRow(4);            // MeV  
    }
  
  }
  G4ThreeVector vertexPosition;
  if(randomVertex_)  // Random vertex position generation
  {
    vertexPosition = RandomVertex(GenVolX,GenVolY,GenVolZ);
  }
  else // Fixed vertex position generation
  {
    vertexPosition[0] = vertex_x_;
    vertexPosition[1] = vertex_y_;
    vertexPosition[2] = vertex_z_;
  }
  vertex->SetPosition(vertexPosition[0], vertexPosition[1], vertexPosition[2]); // x,y,z,t0
  vertex->SetT0(interaction_time);

  // Loop over each of the final particles in the MARLEY event. These are the particles to be tracked and the only ones relevant for G4. 
  for ( const auto& fp : ev.get_final_particles() ) {
    // Convert each one from a marley::Particle into a G4PrimaryParticle.
    // Do this by first setting the PDG code and the 4-momentum components.
    G4PrimaryParticle* particle = new G4PrimaryParticle( fp->pdg_code(), fp->px(), fp->py(), fp->pz(), fp->total_energy() );
    // Also set the charge of the G4PrimaryParticle appropriately
    particle->SetCharge( fp->charge() );
    // Add the fully-initialized G4PrimaryParticle to the primary vertex
    vertex->SetPrimary( particle );
    G4int PrimaryPDG = particle->GetPDGcode();
    G4double PrimaryEnergy = particle->GetTotalEnergy();
    G4double PrimaryPx = particle->GetPx();
    G4double PrimaryPy = particle->GetPy();
    G4double PrimaryPz = particle->GetPz();
    man->FillNtupleIColumn(5,0,PrimaryPDG);
    man->FillNtupleDColumn(5,1,PrimaryEnergy);
    man->FillNtupleDColumn(5,2,PrimaryPx);
    man->FillNtupleDColumn(5,3,PrimaryPy);
    man->FillNtupleDColumn(5,4,PrimaryPz);
    man->AddNtupleRow(5);            // MeV
  }
  // The primary vertex has been fully populated with all final-state particles
  // from the MARLEY event. Add it to the G4Event object so that Geant4 can
  // begin tracking the particles through the simulated geometry.
  anEvent->AddPrimaryVertex( vertex );
}

// ............. SampleTime ............. //
// Function to sample the neutrino interaction time

G4double SupernovaGenerator::SampleTime(G4double neutrino_energy_)
{ 
  std::string th2_name_;
  th2_name_="nusperbin2d_nue"; 
  tfile_ = new TFile("nusperbin2d.root", "read");
  tfile_->GetObject(th2_name_.data(), th2_);
  th1_ = (TH1D*) th2_->ProjectionY();
  int const bin_idx = th1_->FindBin(neutrino_energy_);  // energy in MeV
  TH1D * th1_time = th2_->ProjectionX("time", bin_idx, bin_idx+1);
  double const time = th1_time->GetRandom();

  delete th1_;
  delete th2_;
  delete tfile_;

  return time;
}

// ............. RandomVertex ............. //
// Function to creaate a random position for the interaction vertex

G4ThreeVector SupernovaGenerator::RandomVertex(G4double GenVolX_, G4double GenVolY_, G4double GenVolZ_)
{
  G4double vertexX = GenVolX_ * (G4UniformRand()-0.5);
  G4double vertexY = GenVolY_ * (G4UniformRand()-0.5);
  G4double vertexZ = GenVolZ_ * (G4UniformRand()-0.5);
  G4ThreeVector vertexPosition = G4ThreeVector(vertexX,vertexY,vertexZ);

  return vertexPosition;
}

// ............. MarleyInitialize ............. //
// Function to intialize the marley_generator object that is required to create the primary vertices

void SupernovaGenerator::MarleyInitialize(std::string marleyConfig_ )
{
  #ifdef USE_ROOT
  marley::RootJSONConfig config( marleyConfig_ );
  #else
  marley::JSONConfig config( marleyConfig_ );
  #endif
  marley_generator_= config.create_generator();
}

// ............. BackgroundGeneratePrimaries ............. //
// Function to generate all the background interactions in our event 

void SupernovaGenerator::BackgroundGeneratePrimaries(G4Event* anEvent)
{
  for(int i =0 ; i< nAr39 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 18, 39, decay_time);
  }

  for(int i =0 ; i< nAr42 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 18, 42, decay_time);
  }

  for(int i =0 ; i< nKr85 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 36, 85, decay_time);
  }

  for(int i =0 ; i< nK42 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 19, 42, decay_time);
  }

  for(int i =0 ; i< nBi214 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 83, 214, decay_time);
  }

  for(int i =0 ; i< nPb214 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 82, 214, decay_time);
  }

  for(int i =0 ; i< nRn222 ; i++)
  {
  G4double decay_time = (G4UniformRand()) * time_window*ns;
  Generate_Radioisotope(anEvent, 86, 222, decay_time);
  }
}

// ............. Generate_Radioisotope ............. //
// Function to generate radioisotopes based on their atomic and mass number

void SupernovaGenerator::Generate_Radioisotope(G4Event* anEvent, int Atomic_Number, int Atomic_Mass, double decay_time)
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
G4AnalysisManager *man = G4AnalysisManager::Instance();
man->FillNtupleDColumn(6,0,decay_time);
man->AddNtupleRow(6);           
bg_vertex->SetPrimary(particle);
anEvent->AddPrimaryVertex(bg_vertex);
}
