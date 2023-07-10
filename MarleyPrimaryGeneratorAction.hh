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

#pragma once

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

class G4Event;

class MarleyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MarleyPrimaryGeneratorAction(const std::string& config_file_name);
    ~MarleyPrimaryGeneratorAction();

    virtual void MarleyGeneratePrimaries(G4Event*) ;

  private:

	G4GenericMessenger *fMessenger;
  G4PrimaryVertex* vertex;

  G4double vertex_x_;
  G4double vertex_y_;
  G4double vertex_z_;

  G4double GenVolX; // X lenght of the volume in which we simulate interactions
  G4double GenVolY; // Y lenght of the volume in which we simulate interactions
  G4double GenVolZ; // Z lenght of the volume in which we simulate interactions

  G4double time_window; // Time window to simulate background

  bool randomVertex_;

  G4ThreeVector RandomVertex(G4double , G4double , G4double );

  protected:
  
    // MARLEY event generator object
  marley::Generator marley_generator_;


};