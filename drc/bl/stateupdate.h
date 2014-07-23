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
    bool _infoOnly;
    bool startState(MediationProcess *arg);
    bool info(MediationProcess *arg);
    bool initiated(MediationProcess* arg);
    bool unique(MediationProcess *arg);
    bool clientinfo(MediationProcess *arg);
    bool fees(MediationProcess *arg);
    bool mediators(MediationProcess *arg);
    bool scheduled(MediationProcess *arg);
    bool outcome(MediationProcess *arg);
    bool closed(MediationProcess *arg);
    bool ValidateName(QString name);
    QString StateToString(DisputeProcessInternalStates);
    void GetExternalState(MediationProcess* arg);
};

#endif // STATEUPDATE_H
