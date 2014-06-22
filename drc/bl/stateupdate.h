/*
 * this class is to test and update the state transition of a mediation process.
 * after everything is implemented all that should be required is create the class with the mediation
 * process as argument.
 */


#ifndef STATEUPDATE_H
#define STATEUPDATE_H

#include "mediationprocess.h"
#include "drctypes.h"

class StateUpdate
{
public:
    StateUpdate(MediationProcess *arg);
private:
    void StateCheck(MediationProcess *arg);
    void startState(MediationProcess *arg);
    void readyToSchedule(MediationProcess *arg);
    void scheduled(MediationProcess *arg);
    void closed(MediationProcess *arg);
};

#endif // STATEUPDATE_H
