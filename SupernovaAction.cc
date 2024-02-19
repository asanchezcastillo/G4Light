#include "SupernovaAction.hh"

SupernovaActionInitialization::SupernovaActionInitialization()
{}

SupernovaActionInitialization::~SupernovaActionInitialization()
{}

void SupernovaActionInitialization::BuildForMaster() const
{
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}

void SupernovaActionInitialization::Build() const
{

    SupernovaGenerator *sngen = new SupernovaGenerator();
	SetUserAction(sngen);
    MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
	MySteppingAction *steppingAction = new MySteppingAction(eventAction);
	SetUserAction(steppingAction);
	TrackingAction* trackingAction = new TrackingAction(eventAction);
  	SetUserAction(trackingAction);
	

}
