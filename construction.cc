#include "construction.hh"
#include "G4UserLimits.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
std::cout << "Detector being intialized " << std::endl;
}

MyDetectorConstruction::~MyDetectorConstruction()
{
std::cout << "Detector being destructed " << std::endl;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
//Definition of the function Construct() that belongs to the class MyDetectorConstruction and that 
// returns an object from G4VPhysicalVolume
{
	G4NistManager *nist = G4NistManager::Instance();
//nist is an object of the G4NistManager class, whose value we set to be the return value of the
// function Instance() from the G4NistManager class.

	// define lAr material
    G4Material *lAr = new G4Material("lAr", 18, 39.948 * g / mole, 1.3982 * g / cm3);
	G4Material* detector_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_lAr");
	// Write down all the constants as a function of the energy
	G4double lArFastScintEnergy[17] = { 7.2*eV,  7.9*eV,  8.3*eV,  8.6*eV,  8.9*eV,  9.1*eV,  9.3*eV,  9.6*eV,  9.7*eV,  9.8*eV,  10*eV,  10.2*eV,  10.3*eV,  10.6*eV,  11*eV,  11.6*eV,  11.9*eV};

	G4double lArSlowScintEnergy[17] = { 7.2*eV,  7.9*eV,  8.3*eV,  8.6*eV,  8.9*eV,  9.1*eV,  9.3*eV,  9.6*eV,  9.7*eV,  9.8*eV,  10*eV,  10.2*eV,  10.3*eV,  10.6*eV,  11*eV,  11.6*eV,  11.9*eV}; 

	G4double lArFastScintSpectrum[17] = { 0.0,  0.04, 0.12, 0.27, 0.44, 0.62, 0.80, 0.91, 0.92, 0.85, 0.70, 0.50, 0.31, 0.13, 0.04,  0.01, 0.0 };

	G4double lArSlowScintSpectrum[17] = {0.0,  0.04, 0.12, 0.27, 0.44, 0.62, 0.80, 0.91, 0.92, 0.85, 0.70, 0.50, 0.31, 0.13, 0.04,  0.01, 0.0 };

	G4double RIndexEnergy[21] = {1.18626*eV, 1.68626*eV, 2.18626*eV, 2.68626*eV, 3.18626*eV, 3.68626*eV, 4.18626*eV, 4.68626*eV, 5.18626*eV, 5.68626*eV, 6.18626*eV, 6.68626*eV, 7.18626*eV, 7.68626*eV, 8.18626*eV, 8.68626*eV, 9.18626*eV, 9.68626*eV, 10.1863*eV, 10.6863*eV, 11.1863*eV};

	G4double RIndexSpectrum[21] ={1.24664, 1.2205, 1.22694, 1.22932, 1.23124, 1.23322, 1.23545, 1.23806, 1.24116, 1.24489, 1.24942, 1.25499, 1.26197, 1.2709, 1.28263, 1.29865, 1.32169, 1.35747, 1.42039, 1.56011, 2.16626};

	G4double lArAbsLenEnergy[8]= {4*eV,     5*eV,     6*eV,     7*eV,     8*eV,     9*eV,     10*eV,    11*eV};

//	G4double lArAbsLenSpectrum[8] = { 2000*km,2000*km, 2000*km, 2000*km, 2000*km, 2000*km, 2000*km, 2000*km};


	G4double lArAbsLenSpectrum[8] = { 2000*cm,2000*cm, 2000*cm, 2000*cm, 2000*cm, 2000*cm, 2000*cm, 2000*cm};

	G4double lArRayleighEnergy[21] = {1.18626*eV, 1.68626*eV, 2.18626*eV, 2.68626*eV, 3.18626*eV, 3.68626*eV, 4.18626*eV, 4.68626*eV, 5.18626*eV, 5.68626*eV, 6.18626*eV, 6.68626*eV, 7.18626*eV, 7.68626*eV, 8.18626*eV, 8.68626*eV, 9.18626*eV, 9.68626*eV, 10.1863*eV, 10.6863*eV, 11.1863*eV};
	

	//G4double lArRayleighSpectrum[21] = {10*km, 10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km,10*km};	

	G4double lArRayleighSpectrum[21] = {1200800*cm, 390747*cm, 128633*cm, 54969.1*cm, 27191.8*cm, 14853.7*cm, 8716.9*cm, 5397.42*cm, 3481.37*cm, 2316.51*cm, 1577.63*cm, 1092.02*cm, 763.045*cm, 534.232*cm, 371.335*cm, 252.942*cm, 165.38*cm, 99.9003*cm, 51.2653*cm, 17.495*cm, 0.964341*cm};	
	
	
	// define all the properties of lAr
	G4MaterialPropertiesTable* lAr_MPT = new G4MaterialPropertiesTable(); 

	lAr_MPT ->AddProperty("SCINTILLATIONCOMPONENT1", lArFastScintEnergy, lArFastScintSpectrum, 17 );
	lAr_MPT ->AddProperty("SCINTILLATIONCOMPONENT2", lArSlowScintEnergy, lArSlowScintSpectrum, 17 );
	lAr_MPT ->AddProperty("ABSLENGTH", lArAbsLenEnergy, lArAbsLenSpectrum, 8);
	lAr_MPT ->AddProperty("RAYLEIGH", lArRayleighEnergy, lArRayleighSpectrum, 21 );
	lAr_MPT ->AddProperty("RINDEX", RIndexEnergy, RIndexSpectrum, 21); 
	lAr_MPT ->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 6.*ns);
	lAr_MPT ->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 1300.*ns);
	lAr_MPT ->AddConstProperty("RESOLUTIONSCALE",1);
	lAr_MPT ->AddConstProperty("SCINTILLATIONYIELD2", 0.7692307);
	lAr_MPT ->AddConstProperty("SCINTILLATIONYIELD1", 0.2307692);
	lAr_MPT ->AddConstProperty("SCINTILLATIONYIELD", 24000./MeV);


	// Add lAr propeties to lAr
	lAr->SetMaterialPropertiesTable(lAr_MPT);

	lAr->GetIonisation()->SetBirksConstant(0.069*cm/MeV);

	// define STEEL_STAINLESS_FE7CR2NI. First I need to define some elements:


	G4Element *Chromium=new G4Element("Chromium","Cr", 24, 51.9961* g / mole);

	G4Element *Carbon=new G4Element("Carbon", "C", 6, 12.0107* g / mole);

	G4Element *Iron=new G4Element("Iron","Fe", 26, 55.845* g / mole);

	G4Element *Nickel=new G4Element("Nickel", "Ni", 28, 58.6934* g / mole);

	G4Material *STEEL_STAINLESS_Fe7Cr2Ni = new G4Material("STEEL_STAINLESS_Fe7Cr2Ni",7.85*g/cm3,4);

	STEEL_STAINLESS_Fe7Cr2Ni -> AddElement(Chromium, 0.1792);
	STEEL_STAINLESS_Fe7Cr2Ni -> AddElement(Iron, 0.7298);
	STEEL_STAINLESS_Fe7Cr2Ni -> AddElement(Nickel, 0.09);
	STEEL_STAINLESS_Fe7Cr2Ni -> AddElement(Carbon, 0.001);	
	

	// Reflection information for Stainless Steel 
	
	G4double STEEL_STAINLESS_Fe7Cr2Ni_ReflectivityEnergy[12]={1.77*eV, 2.0675*eV, 2.481*eV, 2.819*eV, 2.953*eV, 3.1807*eV, 3.54*eV, 4.135*eV, 4.962*eV, 5.39*eV, 7.*eV, 15*eV};
	
//	G4double STEEL_STAINLESS_Fe7Cr2Ni_ReflectivitySpectrum[12]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	
//	G4double STEEL_STAINLESS_Fe7Cr2Ni_ReflectivitySpectrum[12]={1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

    G4double STEEL_STAINLESS_Fe7Cr2Ni_ReflectivitySpectrum[12]={ 0.66, 0.64, 0.62, 0.60, 0.59, 0.57, 0.53, 0.47, 0.39, 0.36, 0.27, 0.25};

	// create the MPT for Stainless Steel:

	G4MaterialPropertiesTable *STEEL_STAINLESS_Fe7Cr2Ni_MPT = new G4MaterialPropertiesTable();

	STEEL_STAINLESS_Fe7Cr2Ni_MPT -> AddProperty("REFLECTIVITY", STEEL_STAINLESS_Fe7Cr2Ni_ReflectivityEnergy, STEEL_STAINLESS_Fe7Cr2Ni_ReflectivitySpectrum,12 );

	STEEL_STAINLESS_Fe7Cr2Ni -> SetMaterialPropertiesTable(STEEL_STAINLESS_Fe7Cr2Ni_MPT);


	// Define surface properties of stainless steel 

	G4MaterialPropertiesTable* PMTSurfaceMPT = new G4MaterialPropertiesTable();

	PMTSurfaceMPT -> AddProperty("REFLECTIVITY", STEEL_STAINLESS_Fe7Cr2Ni_ReflectivityEnergy, STEEL_STAINLESS_Fe7Cr2Ni_ReflectivitySpectrum,12 );

	G4float halfLenX = 675;
	
	G4float halfLenY = 325.;
	
 	G4float halfLenZ = 1000;


	// Define world material

 //       G4double energy[2] = {1.37*eV, 6.19*eV };
//        G4double rindexWorld[2]={1.0,1.0};
        
	// G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
   //     mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
//	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
//	worldMat->SetMaterialPropertiesTable(mptWorld);
	// worldMat is our world material, an object from G4material, whose value we set to be the return 
	// value from the FindOrBuildMaterial("G4_AIR") function applied to nist
	G4Box *solidWorld = new G4Box("solidWorld", 685.*cm, 340.*cm, 1030.*cm);
	// we have to give some values
	logicWorld = new G4LogicalVolume(solidWorld, lAr, "logicWorld");
	// logicWorld is the logical volume that combines the size and the material
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0 , G4ThreeVector(0,0,0), logicWorld, "physWorld",0 , false, 0, true);

	// Hollow box to reflect photons that hit the boundaries

	G4double maxStep = 100000/CLHEP::cm;
  	fStepLimit = new G4UserLimits();
	fStepLimit->SetMaxAllowedStep(maxStep);
  	logicWorld->SetUserLimits(fStepLimit);      

	G4Box *outerBox = new G4Box("outerBox", (halfLenX+2.)*cm , (halfLenY+2.)*cm, (halfLenZ+2.)*cm );
	
	G4Box *innerBox = new G4Box("innerBox", halfLenX*cm, halfLenY*cm, halfLenZ*cm);

	G4SubtractionSolid *solidReflectiveBox = new G4SubtractionSolid("solidReflectiveBox", outerBox, innerBox);

	G4LogicalVolume *logicReflectiveBox = new G4LogicalVolume(solidReflectiveBox, STEEL_STAINLESS_Fe7Cr2Ni, "logicReflectiveBox");
	

	G4VPhysicalVolume *physReflectiveBox = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicReflectiveBox, "physReflectiveBox", logicWorld, false, 0 ,true );


	G4OpticalSurface *reflectiveBoxSurface = new G4OpticalSurface("reflectiveBoxSurface");

        reflectiveBoxSurface ->SetMaterialPropertiesTable(PMTSurfaceMPT);

        reflectiveBoxSurface ->SetType(dielectric_metal);

	G4LogicalSkinSurface *reflectiveBoxSurfaceBorder = new G4LogicalSkinSurface("reflectiveBoxSurfaceBorder", logicReflectiveBox, reflectiveBoxSurface);	
       

//....oooOO0OOooo.......oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

	
	G4int nRows = 90;
	G4int nCols = 125; 

	std::cout << "-----> The number of detectors is :" << nRows*nCols << std::endl;

	G4float halfPixX = (2*halfLenX/nRows)/2;
	
	G4float halfPixY = 0.0000001;

        G4float halfPixZ = (2*halfLenZ/nCols)/2;

        G4Box *solidDetector = new G4Box("solidDetector", halfPixX*cm , halfPixY*cm, halfPixZ*cm);

        logicDetector = new G4LogicalVolume(solidDetector, lAr, "logicDetector");

        for (G4int i= 0; i<nRows; i++)
        {

                for (G4int j=0; j<nCols; j++)

                {
//WARNING Overlap check is set to false because it is time consuming. Each time we change the geometry it should be checked at least once.
                        G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( -halfLenX*cm + halfPixX*cm+(2*halfPixX*i)*cm, halfLenY*cm - halfPixY*cm  , -halfLenZ*cm + halfPixZ*cm+(2*halfPixZ*j)*cm), logicDetector ,"physDetector", logicWorld, false, j+i*(nCols), false);

	//	std::cout << "Pixel X: " << -halfLenX + halfPixX+(2*halfPixX*i) << "Pixel Y: "<< halfLenY - halfPixY << "Pixel Z: " << -halfLenZ + halfPixZ+(2*halfPixZ*j) << std::endl;
		
                }

        }


/*


        G4Box *solidDetector = new G4Box("solidDetector", 0.05*cm , 0.0000001*cm, 0.05*cm);

        logicDetector = new G4LogicalVolume(solidDetector, lAr, "logicDetector");


	G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( 0*cm, 324*cm, 0*cm), logicDetector ,"physDetector", logicWorld, false, 0, false);
*/
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
// here I create the sensitive detectors, which are going to be the ones that will have the ProcessHit method. Hence, each time a photon hits a SensitiveDetector volume, the hit will be processed and <<cout(ed)	
	logicDetector->SetSensitiveDetector(sensDet1);

	MySensitiveDetector *lArTracker = new MySensitiveDetector("lArTracker");
	logicWorld->SetSensitiveDetector(lArTracker);

}

