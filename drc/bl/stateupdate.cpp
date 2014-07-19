/*
 * this class is to test and update the state transition of a mediation process.
 * after everything is implemented all that should be required is create the class with the mediation
 * process as argument.
 */

#include "mediationsession.h"
#include "stateupdate.h"
#include "DRCModels.h"
#include <QDebug>
#include <set>

StateUpdate::StateUpdate()
{
    _errorMessage = "";
    _stateMessage = "";
}

//this function calls the method for the state transition the mediation process is in
bool StateUpdate::StateCheck(MediationProcess *arg, QString& errorMessage, QString& stateMessage)
{
    DisputeProcessInternalStates targetState = arg->GetInternalState();
    bool success = true;

    // we always reset the internal state and calculate the state
    arg->SetInternalState(PROCESS_INTERNAL_STATE_NONE);
    do
    {
        // get the current state, depending on that state, see if progress can be made.
        switch(arg->GetInternalState())
        {
        case PROCESS_INTERNAL_STATE_NONE:
            success = startState(arg);
            break;
        case PROCESS_INTERNAL_STATE_INITIATED:
            success = initiated(arg);
            break;
        case PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS:
            success = unique(arg);
            break;
        case PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE:
            success = readyToSchedule(arg);
              break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
            success = scheduled(arg);
            break;
        case PROCESS_INTERNAL_STATE_OUTCOME_SELECTED:
            success = outcome(arg);
            break;
        case PROCESS_INTERNAL_STATE_CLOSED:
            success = false;
            break;
        }
        // loop until a state doesn't pass or it reaches the final state
    } while (success && arg->GetInternalState() != PROCESS_INTERNAL_STATE_CLOSED);

    // call the _processState (external state) function here
    GetExternalState(arg);  // map internal state to external state

    // after internal state has been calculated, we'll compare it with the
    // previously calculated internal state (target state).
    auto finalState = arg->GetInternalState();
    if (finalState < targetState || finalState == PROCESS_INTERNAL_STATE_NONE)
    {
        errorMessage = _errorMessage;
        success = false;
    }
    else success = true;

    //return success;
    stateMessage = _stateMessage;

    // debug statements
    if(success)
    {
        qDebug() << "Decided status: " << success << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Decided status: " << success << " errorMessage(" << _errorMessage << ")";
    }

    return success;
}

// -------------------------------------------------------------------------------------------------------
// this is the start state. all that is required is something in the name field
// -------------------------------------------------------------------------------------------------------
bool StateUpdate::startState(MediationProcess *arg)
{
    bool advance = false;
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
                arg->SetInternalState(PROCESS_INTERNAL_STATE_INITIATED);
                advance = true;
                break;
            }
        }
    }

    if (!advance)
    {
        _errorMessage = "Cannot create mediation process: Missing at least one party with a name.";
        _stateMessage = "To save, add at least one party with a name.";
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * initiated state
 * checks for at least two parties where the name of the
 * primary person is not the same as any other primary
 *      example:  party1.primary != party2.primary
 * AND ensure we have some contact info for both parties
 * success: state = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 * failure: state = PROCESS_INTERNAL_STATE_INITIATED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::initiated(MediationProcess* arg)
{
    qDebug() << "Validating Initiated State.";
    auto parties = arg->GetParties();
    std::set<QString> dups;
    bool advance = true;

    // first, check for duplicates... party1 primary == party2 primary
    if (parties->size() > 1)
    {
        for (unsigned int i = 0; i < parties->size(); i++)
        {
            auto name = parties->at(i)->GetPrimary()->FullName();
            if (dups.find(name) == dups.end()) dups.insert(name);
            else
            {
                _errorMessage = "Cannot initiate mediation process: two or more clients are the same person.";
                _stateMessage = "Not ready to schedule: Two or more clients are the same person.  Each client must be unique.";
                advance = false;
                break;
            }
        }
    }
    else
    {
        // need at least two clients to proceed.
        _errorMessage = "Intake should have at least two clients to be ready to schedule.";
        _stateMessage = "At least two clients are needed to schedule a mediation.";
        advance = false;
    }

    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * initiated state
 * checks for info only, then
 * checks to see if party1 primary == party2 primary
 * AND ensure we have some contact info for both parties
 * success: state = PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE
 * failure: state = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::unique(MediationProcess* arg)
{
    qDebug() << "Validating Unique State.";
    auto parties = arg->GetParties();
    bool advance = true;

    for (unsigned int i=0; i < parties->size(); i++)
    {
        auto primary = parties->at(i)->GetPrimary();
        advance &= ValidateName(primary->FullName());
        advance &=              // (phone not empty) AND ((address not empty) OR (email address not empty))
           ((!primary->getPrimaryPhone().isEmpty()) &&
           ((!primary->getStreet().isEmpty() && !primary->getCity().isEmpty() && !primary->getState().isEmpty() && (primary->getCounty() != COUNTY_NONE)) ||
             !primary->getEmail().isEmpty()));
    }

    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
    }
    else
    {
        _errorMessage = "Phone numbers and either email or mailing address is needed to schedule.";
        _stateMessage = "Not ready to schedule yet: A phone number and either email or mailing addresses is needed for each client.";
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * readyToSchedule state
 * checks to see if the most recent session is confirmed.
 *
 * success: state = PROCESS_INTERNAL_STATE_SCHEDULED
 * failure: state = PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::readyToSchedule(MediationProcess *arg)
{
    qDebug() << "Validating ReadyToSchedule state.";
    bool advance;

    // is there a session?
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
    }
    else
    {
        // is the latest session confirmed?
        MediationSession* session = arg->getMediationSessionVector()->at(arg->getMediationSessionVector()->size() - 1);
        if (session->GetState() == SESSION_STATE_CONFIRMED)
        {
            advance = true;
            arg->SetInternalState(PROCESS_INTERNAL_STATE_SCHEDULED);
        }
        else
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
            advance = false;
            _errorMessage = "Cannot schedule session: Mediation process must have latest session confirmed to be considered Scheduled.";
            _stateMessage = "Session must be confirmed to be considered scheduled.";
        }
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }

    return advance;
}


/* -------------------------------------------------------------------------------------------------------
 * scheduled state
 * checks to see the latest session has some outcome selected,
 * and all fees are paid in full.
 * success: state = PROCESS_INTERNAL_STATE_OUTCOME_SELECTED
 * failure: state = PROCESS_INTERNAL_STATE_SCHEDULED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::scheduled(MediationProcess *arg)
{
    qDebug() << "Validating Scheduled state.";
    bool advance = true;
    if(arg)
    {
        MediationSessionVector* sessions = arg->getMediationSessionVector();
        foreach(MediationSession* session, *sessions)
        {
            if(session->getOutcome() == SESSION_OUTCOME_NONE)
            {
                _errorMessage = "Cannot close: Session Outcome needs to be selected.";
                _stateMessage = "Select session outcome to close mediation process.";
                advance = false;
            }
        }
        if (advance)
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_OUTCOME_SELECTED);
        }
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * outcome state
 * checks to see if all fees have been paid
 * success: state = PROCESS_INTERNAL_STATE_CLOSED
 * failure: state = PROCESS_INTERNAL_STATE_OUTCOME_SELECTED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::outcome(MediationProcess *arg)
{
    qDebug() << "Validating Outcome state.";
    bool advance = true;
    if(arg)
    {
        MediationSessionVector* sessions = arg->getMediationSessionVector();
        foreach(MediationSession* session, *sessions)
        {
            if(!session->isFullyPaid())
            {
                advance = false;
                arg->SetInternalState(PROCESS_INTERNAL_STATE_OUTCOME_SELECTED);
                _errorMessage = "Mediation Process has unpaid session fees.";
                _stateMessage = "To close mediation process all fees must be paid.";
            }
        }
    }
    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_CLOSED);
    }

    if(advance)
    {
        qDebug() << "Validation status: " << advance << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Validation status: " << advance << " errorMessage(" << _errorMessage << ")";
    }
    return advance;
}

/*  GetExternalState - map internal state to external state
 *  NONE -> NONE
 *  INITIATED & UNIQUE_CLIENTS & READY_TO_SCHEDULE go to CLOSED_NO_SESSION if it is info only,
 *          and PENDING if it is not info only.
 *  SCHEDULED & OUTCOME_SELECTED -> SCHEDULED
 *  CLOSED goes to CLOSED_WITH_SESSION if it is closed and an outcome has been reached
 *      goes to STATE_CLOSED_NO_SESSION otherwise
 */
void StateUpdate::GetExternalState(MediationProcess* arg)
{
    auto internalState = arg->GetInternalState();
    DisputeProcessStates externalState = PROCESS_STATE_NONE;
    switch (internalState)
    {
        case PROCESS_INTERNAL_STATE_NONE:
            break;
        // Initiated state and readyToSchedule are currently mapped to
        // external states the exact same way, so just falling through.
        // Any state that is part of a straight path (no branches) on the
        // state diagram should be able to be implemented as a fall through
        // like this.
        case PROCESS_INTERNAL_STATE_INITIATED:
        case PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS:
        case PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE:
            if (arg->GetInfoOnly()) externalState = PROCESS_STATE_CLOSED_NO_SESSION;
            else externalState = PROCESS_STATE_PENDING;
            break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
        case PROCESS_INTERNAL_STATE_OUTCOME_SELECTED:
            externalState = PROCESS_STATE_SCHEDULED;
            break;
        case PROCESS_INTERNAL_STATE_CLOSED:
            MediationSessionVector* sessions = arg->getMediationSessionVector();
            if (sessions->size() > 0)   // Has there been at least 1 session?
            {
                auto lastSession = sessions->at(sessions->size()-1);
                if (lastSession->getOutcome() == SESSION_OUTCOME_AGREEMENT ||
                    lastSession->getOutcome() == SESSION_OUTCOME_NO_AGREEMENT) // Was an outcome reached/not reached?
                    externalState = PROCESS_STATE_CLOSED_WITH_SESSION;
                else externalState = PROCESS_STATE_CLOSED_NO_SESSION;   // No outcome has been reahed yet.
            }
            else externalState = PROCESS_STATE_CLOSED_NO_SESSION;
            break;
    }
    arg->SetState(externalState);
}

bool StateUpdate::ValidateName(QString name)
{
    if (name.isEmpty() || name == " ") return false;
    return true;
}
