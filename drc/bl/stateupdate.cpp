/*
 * this class is to test and update the state transition of a mediation process.
 * after everything is implemented all that should be required is create the class with the mediation
 * process as argument.
 */


#include "stateupdate.h"

StateUpdate::StateUpdate(MediationProcess *arg)
{
    StateCheck(arg);
}
//this function calls the method for the state transition the mediation process is in
void StateUpdate::StateCheck(MediationProcess *arg)
{
    switch(arg->getStateTransition())
    {
    case PROCESS_STATE_NONE:
        startState(arg);
        break;
    case PROCESS_STATE_INITIATED:
        readyToSchedule(arg);
        break;
    case PROCESS_STATE_SCHEDULED:
        scheduled(arg);
        break;
    case PROCESS_STATE_OUTCOME_REACHED:
        closed(arg);
        break;
    }
}

//this is the start state. all that is required is something in the name field
void StateUpdate::startState(MediationProcess *arg)
{
    if(arg->GetPartyAtIndex(0)->GetPrimary()->isName())
    {
        arg->setStateTransition(PROCESS_STATE_INITIATED);
        StateCheck(arg);
    }
}

//this function checks if a schedule is added to the mediation process
void StateUpdate::scheduled(MediationProcess *arg)
{
    if(arg)//just so that the argument not used warning doesn't show up
    {}
}

//this function checks if there is sufficent contact information to schedule
void StateUpdate::readyToSchedule(MediationProcess *arg)
{
    if(arg)//just so that the argument not used warning doesn't show up
    {}
}

//this function is to check if it meets the requirements to move to the move state or back to ready to schedule
void StateUpdate::closed(MediationProcess *arg)
{
    if(arg)//just so that the argument not used warning doesn't show up
    {}
}
