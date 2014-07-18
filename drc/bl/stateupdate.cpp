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
}

//this function calls the method for the state transition the mediation process is in
bool StateUpdate::StateCheck(MediationProcess *arg, QString& errorMessage)
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
        case PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE:
            success = readyToSchedule(arg);
              break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
            success = scheduled(arg);
            break;
//        case PROCESS_INTERNAL_STATE_MEDIATION_COMPLETED:
//            success = closed(arg);
//            break;
        case PROCESS_INTERNAL_STATE_CLOSED:
            break;
        }
        qDebug() << "at end of while - success = " << success;
        qDebug() << "at end of while - state = " << arg->GetInternalState();
        // loop until a state doesn't pass or it reaches the final state
    } while (success && arg->GetInternalState() != PROCESS_INTERNAL_STATE_CLOSED);


    // call the _processState (external state) function here
#warning Finalize internal states and add new states to GetExternalState();
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
                arg->SetState(PROCESS_STATE_PENDING);
                advance = true;
                break;
            }
        }
    }
    qDebug() << "Validation status: " << advance << " " << _errorMessage;
    if (!advance) _errorMessage = "Cannot create mediation process: Missing at least one party with a name.";
    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * initiated state
 * checks for info only, then
 * checks to see if party1 primary == party2 primary
 * AND ensure we have some contact info for both parties
 * success: state = PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE
 * failure: state = PROCESS_INTERNAL_STATE_INITIATED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::initiated(MediationProcess* arg)
{
    qDebug() << "Validating Initiated State.";
    auto parties = arg->GetParties();
    std::set<QString> dups;
    bool advance = true;

    // info only?
    if (arg->GetInfoOnly())
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_CLOSED);
        arg->SetState(PROCESS_STATE_CLOSED_NO_SESSION);
    }
    else
    {

        // first, check for duplicates... party1 primary == party2 primary
        if (parties->size() > 1)
        {
            for (unsigned int i = 0; i < parties->size(); i++)
            {
                auto name = parties->at(i)->GetPrimary()->FullName();
                if (dups.find(name) == dups.end()) dups.insert(name);
                else
                {
                    _errorMessage = "Cannot initiate mediation process: two or more parties contain the same person.";
                    advance = false;
                    break;
                }
            }
        }

        // if that succeeded, check for sufficient contact information
        if(advance)
        {
            if (parties->size() < 2)
            {
                advance = false;
                _errorMessage = "Mediation process is not ready to schedule because it does not have at least two clients with sufficient contact information.";
            }
            else
            {
                for (unsigned int i=0; i < parties->size(); i++)
                {
                    auto primary = parties->at(i)->GetPrimary();
                    advance &= ValidateName(primary->FullName());
                    advance &=              // (phone not empty) AND ((address not empty) OR (email address not empty))
                       ((!primary->getPrimaryPhone().isEmpty()) &&
                       ((!primary->getStreet().isEmpty() && !primary->getCity().isEmpty() && !primary->getState().isEmpty() && (primary->getCounty() != COUNTY_NONE)) ||
                         !primary->getEmail().isEmpty()));
                }
                if(!advance)
                {
                    _errorMessage = "Phone numbers and either email or mailing address is needed to schedule.";
                }
            }
        }

        // set internal and visible state appropriately
        if      (advance)
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
            arg->SetState(PROCESS_STATE_PENDING);
        }
        else
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_INITIATED);
            arg->SetState(PROCESS_STATE_PENDING);
        }
    }

    qDebug() << "Validation status: " << advance << " " << _errorMessage;
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
    bool advance = false;

    // check if the most recent session is confirmed
  //  MediationSessionVector *sessions = arg->getMediationSessionVector();
    if(arg->getMediationSessionVector()->size() == 0)
        return advance;
    MediationSession* session = arg->getMediationSessionVector()->at(arg->getMediationSessionVector()->size() - 1);
//    foreach(MediationSession* session, *arg->getMediationSessionVector())
//    {
        if (session->GetState() == SESSION_STATE_CONFIRMED)
        {

            advance = true;

        }
//    }

    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_SCHEDULED);
        arg->SetState(PROCESS_STATE_SCHEDULED);
    }
    else
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE);
        arg->SetState(PROCESS_STATE_PENDING);
        advance = false;
        _errorMessage = "Mediation process must have latest session confirmed to be considered Scheduled.";
    }

    qDebug() << "Validation status: " << advance << " " << _errorMessage;
    return advance;
}


/* -------------------------------------------------------------------------------------------------------
 * scheduled state
 * checks to see the latest session has some outcome selected,
 * and all fees are paid in full.
 * success: state = PROCESS_INTERNAL_STATE_CLOSED
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
            // first we will check to see if the fees have been paid.
            if(!session->isFullyPaid())
            {
                _errorMessage = "Session Fees must be collected.";
                advance = false;
            }
            // then if an outcome has been selected.
            else if(session->getOutcome() == SESSION_OUTCOME_NONE)
            {
                _errorMessage = "Session Outcome needs to be selected.";
                advance = false;
            }
            else if (session->getOutcome() == SESSION_OUTCOME_AGREEMENT || session->getOutcome() == SESSION_OUTCOME_NO_AGREEMENT)
            {
                arg->SetState(PROCESS_STATE_CLOSED_WITH_SESSION);
            }
            else
            {
                arg->SetState(PROCESS_STATE_CLOSED_NO_SESSION);
            }
        }
    }
    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_CLOSED);
    }
    else
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_SCHEDULED);
        arg->SetState(PROCESS_STATE_SCHEDULED);
    }
    qDebug() << "Validation status: " << advance << " " << _errorMessage;
    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * closed state
 * checks to see if mediators have been selected, an outcome as been reached/not reached, and
 * if a fee has been added
 * success: state = PROCESS_STATE_SCHEDULED
 * failure: state = PROCESS_STATE_OUTCOME_REACHED
 * TODO
 * -------------------------------------------------------------------------------------------------------
 */
//bool StateUpdate::closed(MediationProcess *arg)
//{
//    qDebug() << "Validating Closed state.";
//    bool success = true;
//    if(arg)
//    {
//        MediationSessionVector* sessions = arg->getMediationSessionVector();
//        for (unsigned int i = 0; i < sessions->size(); i++)
//        {
//            auto session = sessions->at(i);
////            success &= (!session->getFee1().isEmpty());
////            success &= (!session->getFee2().isEmpty());
//            success &= (!session->getMediator1().isEmpty());
//            success &= (!session->getMediator2().isEmpty());
//        }
//    }
//    if (success)
//    {
//        arg->SetInternalState(PROCESS_INTERNAL_STATE_CLOSED);
//    }
//    else
//    {
//        arg->SetInternalState(PROCESS_INTERNAL_STATE_SCHEDULED);
//        _errorMessage = "Mediation session form not completed.";
//    }
//    qDebug() << "Validation status: " << success << " " << _errorMessage;
//    return success;
//}

/*  GetExternalState - map internal state to external state
 *  NONE -> NONE
 *  INITIATED & READY_TO_SCHEDULE go to CLOSED_NO_SESSION if it is info only,
 *          and PENDING if it is not info only.
 *  SCHEDULED -> SCHEDULED
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
        case PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE:
            if (arg->GetInfoOnly()) externalState = PROCESS_STATE_CLOSED_NO_SESSION;
            else externalState = PROCESS_STATE_PENDING;
            break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
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
