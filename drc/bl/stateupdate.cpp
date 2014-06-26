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
    unsigned int targetState = arg->getStateTransition();
    bool success = true;
    arg->setStateTransition(PROCESS_STATE_NONE);
    do
    {
        switch(arg->getStateTransition())
        {
        case PROCESS_STATE_NONE:
            success = startState(arg);
            break;
        case PROCESS_STATE_INITIATED:
            success = initiated(arg);
            break;
        case PROCESS_STATE_READY_TO_SCHEDULE:
            success = readyToSchedule(arg);
            break;
        case PROCESS_STATE_SCHEDULED:
            success = scheduled(arg);
            break;
        case PROCESS_STATE_OUTCOME_REACHED:
            success = closed(arg);
            break;
        }
    } while (success);

    if (arg->getStateTransition() < targetState)
    {

    }
}

//this is the start state. all that is required is something in the name field
bool StateUpdate::startState(MediationProcess *arg)
{
    if(arg->GetPartyAtIndex(0)->GetPrimary()->isName())
    {
        arg->setStateTransition(PROCESS_STATE_INITIATED);
        return true;
    }
    return false;
}

/* initiated state
 * checks to see if party1 primary == party2 primary
 * success: state = PROCESS_STATE_READY_TO_SCHEDULE
 * failure: state = PROCESS_STATE_NONE
 */
bool StateUpdate::initiated(MediationProcess* arg)
{
    auto parties = arg->GetParties();
    auto name = arg->GetPartyAtIndex(0)->GetPrimary()->FullName();
    bool success = true;
    if (parties.size() > 1)
    {
        for (unsigned int i = 0; i < parties.size(); i++)
        {
            if (parties[0]->GetPrimary()->FullName() == name)
            {
                success = false;
                break;
            }
        }
    }
    if      (success) arg->setStateTransition(PROCESS_STATE_READY_TO_SCHEDULE);
    else    arg->setStateTransition(PROCESS_STATE_NONE);
    return success;
}

/* readyToSchedule state
 * checks to see if there is sufficient contact information for
 * the primary person of each party.
 * success: state = PROCESS_STATE_SCHEDULED
 * failure: state = PROCESS_STATE_INITIATED
 */
bool StateUpdate::readyToSchedule(MediationProcess *arg)
{
    bool success = true;
    auto parties = arg->GetParties();
    if (parties.size() < 2)     success = false;
    for (unsigned int i=0; i < parties.size(); i++)
    {
        auto primary = parties[i]->GetPrimary();
        // check to see if primary person has either an address or email
    }
    return false;
}


/* scheduled state
 * checks to see if a mediation date has been set
 */
bool StateUpdate::scheduled(MediationProcess *arg)
{
    if(arg)//just so that the argument not used warning doesn't show up
    {
        return true;
    }
    return false;
}

/*
 * closed state
 */
bool StateUpdate::closed(MediationProcess *arg)
{
    if(arg)//just so that the argument not used warning doesn't show up
    {
        return true;
    }
    return false;
}
