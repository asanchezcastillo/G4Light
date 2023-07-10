#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "detector.hh"
#include "G4Tubs.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalParameters.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4GenericMessenger.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
// We have to create a classi that defines our volume and is inherited from another class in Geant4
{
public:
	
	MyDetectorConstruction();
	~MyDetectorConstruction();

	virtual G4VPhysicalVolume* Construct() override;

	
//Construct is the function that returns an object from G4PhysicalVolume. This function constructs the whole description of the detector.

private:
// In this case we need to define logicDetector outside the construct function because it is going to
// be called by the ConstructSDandField function as well
	G4LogicalVolume *logicDetector;
	G4UserLimits* fStepLimit = nullptr;
	G4LogicalVolume *logicWorld;
//	G4LogicalVolume *logicSphere2;
	virtual void ConstructSDandField();
};

#endif
