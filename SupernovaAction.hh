#ifndef SUPERNOVAACTION_HH
#define SUPERNOVAACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"
#include "trackingaction.hh"	
#include "G4GenericMessenger.hh"
#include "SupernovaGenerator.hh"

class SupernovaActionInitialization : public G4VUserActionInitialization
{
public:
	SupernovaActionInitialization();
	~SupernovaActionInitialization();
	
	virtual void Build() const;
	virtual void BuildForMaster() const;
    
// The Build function is the main function that will run the particle gun and compute the stepping etc

};

#endif
