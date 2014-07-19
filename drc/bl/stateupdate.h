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
    StateUpdate();
    bool StateCheck(MediationProcess *arg, QString &errorMessage, QString &stateMessage);
private:
    QString _errorMessage;
    QString _stateMessage;
    bool startState(MediationProcess *arg);
    bool initiated(MediationProcess* arg);
    bool readyToSchedule(MediationProcess *arg);
    bool scheduled(MediationProcess *arg);
    bool closed(MediationProcess *arg);
    bool unique(MediationProcess *arg);
    bool outcome(MediationProcess *arg);
    bool ValidateName(QString name);
    void GetExternalState(MediationProcess* arg);
};

#endif // STATEUPDATE_H
