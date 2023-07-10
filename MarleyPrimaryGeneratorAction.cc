/// @file
/// @copyright Copyright (C) 2016-2021 Steven Gardiner
/// @license GNU General Public License, version 3
//
// This file is part of MARLEY (Model of Argon Reaction Low Energy Yields)
//
// MARLEY is free software: you can redistribute it and/or modify it under the
// terms of version 3 of the GNU General Public License as published by the
// Free Software Foundation.
//
// For the full text of the license please see COPYING or
// visit http://opensource.org/licenses/GPL-3.0
//
// Please respect the MCnet academic usage guidelines. See GUIDELINES
// or visit https://www.montecarlonet.org/GUIDELINES for details.

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
#include "MarleyPrimaryGeneratorAction.hh"

MarleyPrimaryGeneratorAction::MarleyPrimaryGeneratorAction(
  const std::string& config_file_name) : G4VUserPrimaryGeneratorAction()
{
  // Create a new marley::Generator object using the settings from the
  // configuration file. If the USE_ROOT preprocessor macro is defined, then
  // parse the configuration file using a RootJSONConfig object to make
  // ROOT-dependent configuration options available (e.g., the use of a "th1"
  // or "tgraph" neutrino source)
  #ifdef USE_ROOT
  marley::RootJSONConfig config( config_file_name );
  #else
  marley::JSONConfig config( config_file_name );
  #endif
  marley_generator_= config.create_generator();

}



MarleyPrimaryGeneratorAction::~MarleyPrimaryGeneratorAction()
{
delete fMessenger;	
}

void MarleyPrimaryGeneratorAction::MarleyGeneratePrimaries(G4Event* anEvent)
{ 

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

  // Create a new primary vertex at the spacetime origin.
  vertex = new G4PrimaryVertex(vertexPosition[0], vertexPosition[1], vertexPosition[2], 0.); // x,y,z,t0

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  // Generate a new MARLEY event using the owned marley::Generator object
  marley::Event ev = marley_generator_.create_event();

  // This line, if uncommented, will print the event in ASCII format
  // to standard output
  //std::cout << ev << '\n';

  // Loop over each of the final particles in the MARLEY event
  for ( const auto& fp : ev.get_final_particles() ) {

    // Convert each one from a marley::Particle into a G4PrimaryParticle.
    // Do this by first setting the PDG code and the 4-momentum components.
    G4PrimaryParticle* particle = new G4PrimaryParticle( fp->pdg_code(),
      fp->px(), fp->py(), fp->pz(), fp->total_energy() );

    // Also set the charge of the G4PrimaryParticle appropriately


    particle->SetCharge( fp->charge() );


    // Add the fully-initialized G4PrimaryParticle to the primary vertex

    vertex->SetPrimary( particle );

    G4int PrimaryPDG = particle->GetPDGcode();
    G4double PrimaryEnergy = particle->GetTotalEnergy();
    G4double PrimaryPx = particle->GetPx();
    G4double PrimaryPy = particle->GetPy();
    G4double PrimaryPz = particle->GetPz();

    man->FillNtupleIColumn(4,0,PrimaryPDG);
    man->FillNtupleDColumn(4,1,PrimaryEnergy);
    man->FillNtupleDColumn(4,2,PrimaryPx);
    man->FillNtupleDColumn(4,3,PrimaryPy);
    man->FillNtupleDColumn(4,4,PrimaryPz);
    man->AddNtupleRow(4);
  }

  // The primary vertex has been fully populated with all final-state particles
  // from the MARLEY event. Add it to the G4Event object so that Geant4 can
  // begin tracking the particles through the simulated geometry.

  anEvent->AddPrimaryVertex( vertex );
}

G4ThreeVector MarleyPrimaryGeneratorAction::RandomVertex(G4double GenVolX_, G4double GenVolY_, G4double GenVolZ_)
{
  G4double vertexX = GenVolX_ * (G4UniformRand()-0.5);
  G4double vertexY = GenVolY_ * (G4UniformRand()-0.5);
  G4double vertexZ = GenVolZ_ * (G4UniformRand()-0.5);
  G4ThreeVector vertexPosition = G4ThreeVector(vertexX,vertexY,vertexZ);

  return vertexPosition;
}
