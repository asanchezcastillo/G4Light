#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"
#include "G4GenericMessenger.hh"

class MyActionInitialization : public G4VUserActionInitialization

{
public:
	MyActionInitialization();
	~MyActionInitialization();
	
	virtual void Build() const;
	virtual void BuildForMaster() const;
// The Build function is the main function that will run the particle gun and compute the stepping etc

};

#endif
