#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();

// here we are creating an object that belongs to MyPrimaryGenerator class, which is created in the generator.cc/hh files

	SetUserAction(generator);

// this line initializes the action

	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);

// we dont use any default run action, we use our own one.

	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction *steppingAction = new MySteppingAction(eventAction);
	SetUserAction(steppingAction);

	TrackingAction* trackingAction = new TrackingAction(eventAction);
  	SetUserAction(trackingAction);

}
