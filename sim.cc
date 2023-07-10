#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"

#include <FTFP_BERT_HP.hh>
#include <G4EmStandardPhysics_option4.hh>

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "SupernovaGenerator.hh"
#include "SupernovaAction.hh"

int main(int argc, char** argv)
{
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager();
		runManager->SetNumberOfThreads(2*(G4Threading::G4GetNumberOfCores()));
	#else

		G4RunManager * runManager = new G4RunManager();
	#endif

	runManager->SetUserInitialization(new MyDetectorConstruction());
//	runManager->SetUserInitialization(new MyPhysicsList());
 	G4VModularPhysicsList* physics_list = new FTFP_BERT_HP();
	physics_list->ReplacePhysics(new G4EmStandardPhysics_option4());
  	G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
	G4OpticalParameters *opParams = G4OpticalParameters::Instance();
	opParams -> SetScintTrackSecondariesFirst(true);
	opParams -> SetScintByParticleType(false);
	opParams->SetCerenkovTrackSecondariesFirst(false);
	physics_list->RegisterPhysics (opticalPhysics);
	runManager->SetUserInitialization(physics_list);

	char* marleyFile=0;
	char* generatorFile=0;
	int nRuns=0;

	for (int i=1; i<argc; i++)
	{
		if(i + 1 != argc)
		{
			if(strcmp(argv[i], "--marley") == 0 || strcmp(argv[i], "-m") == 0 )
			{
			marleyFile = argv[i+1];
			i++;	
			}
                        if(strcmp(argv[i], "--gen") == 0 || strcmp(argv[i], "-g") == 0 )
                        {
                        generatorFile = argv[i+1];
                        i++;
                        }
			if ( strcmp(argv[i], "-n") == 0 )
			{
			nRuns = atoi(argv[i+1]);	
			i++;	
			}
		}
	}	

	if(marleyFile==0 && generatorFile==0)
	{              
		runManager->SetUserInitialization(new MyActionInitialization());
		runManager->Initialize();
        G4UImanager *UImanager = G4UImanager::GetUIpointer();
        UImanager->ApplyCommand("/process/inactivate Cerenkov");
        UImanager->ApplyCommand("/process/inactivate Scintillation");
        G4UIExecutive * ui = 0;
		ui = new G4UIExecutive(argc, argv);
        G4VisManager *visManager = new G4VisExecutive();
        visManager->Initialize();
        if (ui)
        {
                UImanager->ApplyCommand("/control/execute vis.mac");
                ui->SessionStart();
                delete ui;
        }
	delete visManager;
	}

	if(marleyFile != 0 )
	{
		runManager->SetNumberOfThreads(1);
		G4String marFile = marleyFile;
		runManager->SetUserInitialization(new SupernovaActionInitialization());
		runManager->Initialize();
		for(int i = 0; i<nRuns; i ++ )
		{
			G4UImanager *UImanager = G4UImanager::GetUIpointer();
			UImanager->ApplyCommand("/process/inactivate Cerenkov");
			UImanager->ApplyCommand("/process/inactivate Scintillation");
			UImanager->ApplyCommand("/control/execute " + marFile);
			runManager->BeamOn(1);
		}

	}

	if(generatorFile!=0)
	{
		G4String genFile=generatorFile;
		G4VisManager *visManager = new G4VisExecutive();
		visManager->Initialize();
		G4UImanager *UImanager = G4UImanager::GetUIpointer();
		MyPrimaryGenerator * myGenerator = new MyPrimaryGenerator();
		runManager->SetUserInitialization(new MyActionInitialization());
		runManager->Initialize();
		for(int i = 0; i<nRuns; i ++ )
		{
			UImanager->ApplyCommand("/process/inactivate Cerenkov");
			UImanager->ApplyCommand("/process/inactivate Scintillation");
			UImanager->ApplyCommand("/control/execute " + genFile);
			runManager->BeamOn(1);
		}
	}	

	delete runManager;
}
