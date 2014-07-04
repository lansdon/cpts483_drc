/*
 * this class is to test and update the state transition of a mediation process.
 * after everything is implemented all that should be required is create the class with the mediation
 * process as argument.
 */


#include "stateupdate.h"
#include "DRCModels.h"
#include <QDebug>
#include <set>

StateUpdate::StateUpdate()
{
    _errorMessage = "";
}

//this function calls the method for the state transition the mediation process is in
bool StateUpdate::StateCheck(MediationProcess *arg, QString& errorMessage)
{
    unsigned int targetState = arg->getStateTransition();
    bool success = true;
    arg->setStateTransition(PROCESS_STATE_NONE);
    do
    {
        switch(arg->getStateTransition())
        {
        case PROCESS_INTERNAL_STATE_NONE:
            success = startState(arg);
            break;
        case PROCESS_INTERNAL_STATE_INITIATED:
            success = initiated(arg);
            break;
        case PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE:
            success = readyToSchedule(arg);
              break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
            success = scheduled(arg);
            break;
        case PROCESS_INTERNAL_STATE_MEDIATION_COMPLETED:
            success = closed(arg);
            break;
        case PROCESS_INTERNAL_STATE_OUTCOME_REACHED:
            success = false;
            break;
        }
    } while (success && arg->getStateTransition() != PROCESS_INTERNAL_STATE_OUTCOME_REACHED);

    auto finalState = arg->getStateTransition();
    if (finalState < targetState || finalState == PROCESS_STATE_NONE)
    {
        errorMessage = _errorMessage;
        return success;
    }
    else return true;
}

//this is the start state. all that is required is something in the name field
bool StateUpdate::startState(MediationProcess *arg)
{
    bool success = false;
    qDebug() << "Validating Start State.";
    auto parties = arg->GetParties();
    if(parties->size() > 0)
    {
        auto parties = arg->GetParties();
        for (unsigned int i = 0; i < parties->size(); i++)
        {
            auto primaryName = parties->at(i)->GetPrimary()->FullName();

            if (ValidateName(primaryName))
            {
                arg->setStateTransition(PROCESS_INTERNAL_STATE_INITIATED);
                success = true;
                break;
            }
        }
    }
    qDebug() << "Validation status: " << success << " " << _errorMessage;
    if (!success) _errorMessage = "Cannot create mediation process: Missing at least one party with a name.";
    return success;
}

/* initiated state
 * checks to see if party1 primary == party2 primary
 * success: state = PROCESS_STATE_READY_TO_SCHEDULE
 * failure: state = PROCESS_STATE_NONE
 */
bool StateUpdate::initiated(MediationProcess* arg)
{
    qDebug() << "Validating Initiated State.";
    auto parties = arg->GetParties();
    std::set<QString> dups;
    bool success = true;
    if (parties->size() > 1)
    {
        for (unsigned int i = 0; i < parties->size(); i++)
        {
            auto name = parties->at(i)->GetPrimary()->FullName();
            if (dups.find(name) == dups.end()) dups.insert(name);
            else
            {
                _errorMessage = "Cannot initiate mediation process: two or more parties contain the same person.";
                success = false;
                break;
            }
        }
    }
    if      (success) arg->setStateTransition(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
    else    arg->setStateTransition(PROCESS_STATE_NONE);
    qDebug() << "Validation status: " << success << " " << _errorMessage;
    return success;
}

/* readyToSchedule state
 * checks to see if there is sufficient contact information for
 * the primary person of each party.
 * success: state = PROCESS_STATE_READY_SCHEDULED
 * failure: state = PROCESS_STATE_INITIATED
 */
bool StateUpdate::readyToSchedule(MediationProcess *arg)
{
    qDebug() << "Validating ReadyToSchedule state.";
    bool success = true;
    if (arg)
    {
        auto parties = arg->GetParties();
        if (parties->size() < 2)     success = false;
        for (unsigned int i=0; i < parties->size(); i++)
        {
            auto primary = parties->at(i)->GetPrimary();
            success &= ValidateName(primary->FullName());
            success &=              // (phone not empty) AND ((address not empty) OR (email address not empty))
               ((!primary->getPrimaryPhone().isEmpty()) &&
               ((!primary->getStreet().isEmpty() && !primary->getCity().isEmpty() && !primary->getState().isEmpty() && !primary->getCounty().isEmpty()) ||
                 !primary->getEmail().isEmpty()));
        }
    }
    else success = false;

    if (!success)
    {
        _errorMessage = "Mediation process is not ready to schedule because it does not have at least two clients with sufficient contact information.";
        arg->setStateTransition(PROCESS_INTERNAL_STATE_INITIATED);
    }
    else arg->setStateTransition(PROCESS_STATE_SCHEDULED);
    qDebug() << "Validation status: " << success << " " << _errorMessage;
    return success;
}


/* scheduled state
 * checks to see if a mediation date has been set
 * success: state = PROCESS_STATE_CLOSED
 * failure: state = PROCESS_STATE_READY_TO_SCHEDULE
 * TODO
 */
bool StateUpdate::scheduled(MediationProcess *arg)
{
    qDebug() << "Validating Scheduled state.";
    bool success = true;
    if(arg)
    {
        auto sessions = arg->getMediationSessionVector();
        if (sessions->size() < 1) success = false;
    }
    if (success)
    {
        arg->setStateTransition(PROCESS_INTERNAL_STATE_MEDIATION_COMPLETED);
    }
    else
    {
        arg->setStateTransition(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
        _errorMessage = "No mediation date scheduled.";
    }
    qDebug() << "Validation status: " << success << " " << _errorMessage;
    return success;
}

/*
 * closed state
 * checks to see if mediators have been selected, an outcome as been reached/not reached, and
 * if a fee has been added
 * success: state = PROCESS_STATE_SCHEDULED
 * failure: state = PROCESS_STATE_OUTCOME_REACHED
 * TODO
 */
bool StateUpdate::closed(MediationProcess *arg)
{
    qDebug() << "Validating Closed state.";
    bool success = true;
    if(arg)
    {
        MediationSessionVector* sessions = arg->getMediationSessionVector();
        for (unsigned int i = 0; i < sessions->size(); i++)
        {
            auto session = sessions->at(i);
            success &= (!session->getFee1().isEmpty());
            success &= (!session->getFee2().isEmpty());
            success &= (!session->getMediator1().isEmpty());
            success &= (!session->getMediator2().isEmpty());
        }
    }
    if (success)
    {
        arg->setStateTransition(PROCESS_INTERNAL_STATE_OUTCOME_REACHED);
    }
    else
    {
        arg->setStateTransition(PROCESS_INTERNAL_STATE_SCHEDULED);
        _errorMessage = "Mediation session form not completed.";
    }
    qDebug() << "Validation status: " << success << " " << _errorMessage;
    return success;
}

bool StateUpdate::ValidateName(QString name)
{
    if (name.isEmpty() || name == " ") return false;
    return true;
}
