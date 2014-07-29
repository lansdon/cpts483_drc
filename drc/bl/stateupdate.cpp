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
    _infoOnly = false;
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
        case PROCESS_INTERNAL_STATE_INFO_ONLY:
            success = info(arg);
            break;
        case PROCESS_INTERNAL_STATE_INITIATED:
            success = initiated(arg);
            break;
        case PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS:
            success = unique(arg);
            break;
        case PROCESS_INTERNAL_STATE_ATTORNEY_INFO:
            success = attorney(arg);
            break;
        case PROCESS_INTERNAL_STATE_CLIENT_INFO:
            success = clientinfo(arg);
            break;
        case PROCESS_INTERNAL_STATE_FEES_RECORDED:
            success = fees(arg);
            break;
        case PROCESS_INTERNAL_STATE_SCHEDULED:
            success = scheduled(arg);
            break;
        case PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED:
            success = mediators(arg);
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
    if (finalState == PROCESS_INTERNAL_STATE_NONE)
    {
        // we didn't get anywhere... which means we should return false.
        if(_errorMessage.isEmpty())
        {
            _errorMessage = "Message not set.";
        }
        errorMessage = _errorMessage;
        success = false;
    }
    else if (finalState < targetState)
    {
        qDebug() << "Regression! targetState was [" << targetState << "] and finalState was [" << finalState << "]";
        // we have regressed!
        stateMessage = _errorMessage;
    }
    else
    {
        success = true;
    }

    //return success;
    stateMessage = _stateMessage;

    // debug statements
    if(success)
    {
        qDebug() << "Success - Decided state: " << StateToString(finalState) << " stateMessage(" << _stateMessage << ")";
    }
    else
    {
        qDebug() << "Error - Decided status: " << StateToString(finalState) << " errorMessage(" << errorMessage << ") << should be blank!";
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
                arg->SetInternalState(PROCESS_INTERNAL_STATE_INFO_ONLY);
                advance = true;
                break;
            }
        }
    }

    if (!advance)
    {
        _errorMessage = "Cannot save: Enter at least one client with a name.";
        _stateMessage = "To save, enter at least one client with a name.";
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * info only state
 * checks if the info only check box got checked.
 *
 * success: state = PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS
 * failure: state = PROCESS_INTERNAL_STATE_INITIATED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::info(MediationProcess* arg)
{
    bool advance;
    qDebug() << "Validating Info Only State.";

    if(arg->GetInfoOnly())
    {
        advance = false;
        _infoOnly = true;
        _stateMessage = "Info only, no further action required.";
        _errorMessage = "Info only, no further action required.";
    }
    else
    {
        advance = true;
        arg->SetInternalState(PROCESS_INTERNAL_STATE_INITIATED);
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * initiated state: at least a name has been provided
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
                _errorMessage = "Cannot schedule: two or more clients are the same person.";
                _stateMessage = "To proceed, ensure each client name is unique.";
                advance = false;
                break;
            }
        }
    }
    else if (arg->GetSessionType() == COACHING_SESSION)
    {
        // coaching sessions do not require more than 1 person.
        advance = true;
    }
    else
    {
        // need at least two clients to proceed.
        _errorMessage = "Cannot schedule: At least two clients are needed.";
        _stateMessage = "To create session, two or more client(s) or coaching need to be identified.";
        advance = false;
    }
    if(advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS);
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * unique state: we know there are at least two unique clients
 * checks to see if party1 primary == party2 primary
 * AND ensure we have some contact info for both parties
 * success: state = PROCESS_INTERNAL_STATE_ATTORNEY_INFO
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
        arg->SetInternalState(PROCESS_INTERNAL_STATE_ATTORNEY_INFO);
    }
    else
    {
        _errorMessage = "Cannot schedule: Enter a phone number then enter email or mailing address for each client.";
        _stateMessage = "To schedule, enter a phone number then enter either email or a mailing address for each client.";
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * unique state: we know there are at least two unique clients
 * checks to see if party1 primary == party2 primary
 * AND ensure we have some contact info for both parties
 * success: state = PROCESS_INTERNAL_STATE_CLIENT_INFO
 * failure: state = PROCESS_INTERNAL_STATE_ATTORNEY_INFO
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::attorney(MediationProcess* arg)
{
    qDebug() << "Validating Attorney State.";
    auto parties = arg->GetParties();
    bool advance = true;

    for (unsigned int i=0; i < parties->size(); i++)
    {
        auto primary = parties->at(i)->GetPrimary();
        advance &= ValidateName(primary->getAttorney());
    }

    if (advance)
    {
        arg->SetInternalState(PROCESS_INTERNAL_STATE_CLIENT_INFO);
    }
    else
    {
        _errorMessage = "Cannot schedule: Enter a name (or the word none) for each parties attorney.";
        _stateMessage = "To schedule, enter an attorney name for each client.";
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * clientinfo state: we have enough client info to schedule.
 * checks to see if the fees have been recorded.
 *
 * success: state = PROCESS_INTERNAL_STATE_FEES_RECORDED
 * failure: state = PROCESS_INTERNAL_STATE_CLIENT_INFO
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::clientinfo(MediationProcess *arg)
{
    qDebug() << "Validating clientinfo state.";
    bool advance;

    // is there a session?
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
        _errorMessage = "Cannot schedule: Add a session.";
        _stateMessage = "To proceed, add a session.";
    }
    else
    {
        // have fees been added for the latest session?
        MediationSession* session = arg->getMediationSessionVector()->at(arg->getMediationSessionVector()->size() - 1);
        if (session->getFeeStatus() ==  "No fees added")
        {
            advance = false;
            _errorMessage = "Cannot schedule: Enter session fees.";
            _stateMessage = "To proceed, enter session fees.";
        }
        else
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_FEES_RECORDED);
            advance = true;
        }
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * fees state: fees have been recorded.
 * checks to see if the most recent session has mediators assigned.
 *
 * success: state = PROCESS_INTERNAL_STATE_SCHEDULED
 * failure: state = PROCESS_INTERNAL_STATE_FEES_RECORDED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::fees(MediationProcess *arg)
{
    qDebug() << "Validating mediators state.";
    bool advance;

    // is there a session?
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
        _errorMessage = "Cannot schedule: Add a session.";
        _stateMessage = "To proceed, add a session.";
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
            advance = false;
            _errorMessage = "Cannot mark scheduled: Select confirmed for session status.";
            _stateMessage = "To mark as scheduled, confirm session.";
        }
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * mediator state: mediators have been assigned.
 * checks to see if the most recent session is confirmed.
 *
 * success: state = PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED
 * failure: state = PROCESS_INTERNAL_STATE_SCHEDULED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::scheduled(MediationProcess *arg)
{
    qDebug() << "Validating Mediators state.";
    bool advance;

    // is there a session?
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
        _errorMessage = "Cannot schedule: Add a session.";
        _stateMessage = "To proceed, add a session.";
    }
    else
    {
        // are any mediators missing?
        MediationSession* session = arg->getMediationSessionVector()->at(arg->getMediationSessionVector()->size() - 1);
        if (session->getMediator1().isEmpty() || session->getMediator2().isEmpty())
        {
            advance = false;
            _errorMessage = "Cannot schedule: Enter session mediator(s).";
            _stateMessage = "To schedule, enter names of session mediator(s).";
        }
        else
        {
            arg->SetInternalState(PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED);
            advance = true;
        }
    }


    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/* -------------------------------------------------------------------------------------------------------
 * scheduled state
 * checks to see the latest session has some outcome selected,
 * and all fees are paid in full.
 * success: state = PROCESS_INTERNAL_STATE_OUTCOME_SELECTED
 * failure: state = PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED
 * -------------------------------------------------------------------------------------------------------
 */
bool StateUpdate::mediators(MediationProcess *arg)
{
    qDebug() << "Validating Scheduled state.";
    bool advance = true;
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
        _errorMessage = "Cannot schedule: Add a session.";
        _stateMessage = "To proceed, add a session.";
    }
    else
    {
        MediationSessionVector* sessions = arg->getMediationSessionVector();
        foreach(MediationSession* session, *sessions)
        {
            if(session->getOutcome() == SESSION_OUTCOME_NONE)
            {
                _errorMessage = "Cannot close: Select session outcome.";
                _stateMessage = "To close, select session outcome.";
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
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
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
    if(arg->getMediationSessionVector()->size() == 0)
    {
        advance = false;
        _errorMessage = "Cannot schedule: Add a session.";
        _stateMessage = "To proceed, add a session.";
    }
    else
    {
        MediationSessionVector* sessions = arg->getMediationSessionVector();
        foreach(MediationSession* session, *sessions)
        {
            if(!session->isFullyPaid())
            {
                advance = false;
                _errorMessage = "Cannot close: All fees must be paid in full.";
                _stateMessage = "To close, all fees must be paid in full.";
            }
            else
            {
                advance = true;
                arg->SetInternalState(PROCESS_INTERNAL_STATE_CLOSED);
                _stateMessage = "Intake process complete.";
            }
        }
    }

    // debug statements
    if(advance)
    {
        qDebug() << "Validation status: transition criteria met, advancing.";
    }
    else
    {
        qDebug() << "Validation status: state calculation complete, final state=" << StateToString(arg->GetInternalState());
    }

    return advance;
}

/*  GetExternalState - map internal state to external state
 *  NONE -> NONE
 *  INITIATED, UNIQUE_CLIENTS, CLIENT_INFO, FEES, & MEDIATORS go to CLOSED_NO_SESSION if it is info only,
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
        case PROCESS_INTERNAL_STATE_INFO_ONLY:
        case PROCESS_INTERNAL_STATE_INITIATED:
        case PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS:
        case PROCESS_INTERNAL_STATE_ATTORNEY_INFO:
        case PROCESS_INTERNAL_STATE_CLIENT_INFO:
        case PROCESS_INTERNAL_STATE_FEES_RECORDED:
            if (arg->GetInfoOnly()) externalState = PROCESS_STATE_CLOSED_NO_SESSION;
            else externalState = PROCESS_STATE_PENDING;
            break;
        case PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED:
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
                else externalState = PROCESS_STATE_CLOSED_NO_SESSION;   // No outcome has been reached yet.
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

QString StateUpdate::StateToString(DisputeProcessInternalStates state)
{
  switch(state)
  {
  case PROCESS_INTERNAL_STATE_NONE:
      return "NONE";
      break;
  case PROCESS_INTERNAL_STATE_INFO_ONLY:
      return "INFO_ONLY";
      break;
  case PROCESS_INTERNAL_STATE_INITIATED:
      return "INITIATED";
      break;
  case PROCESS_INTERNAL_STATE_UNIQUE_CLIENTS:
      return "UNIQUE_CLIENTS";
      break;
  case PROCESS_INTERNAL_STATE_ATTORNEY_INFO:
      return "ATTORNEY_INFO";
      break;
  case PROCESS_INTERNAL_STATE_CLIENT_INFO:
      return "CLIENT_INFO";
      break;
  case PROCESS_INTERNAL_STATE_FEES_RECORDED:
      return "FEES_RECORDED";
      break;
  case PROCESS_INTERNAL_STATE_MEDIATORS_ASSIGNED:
      return "MEDIATORS_ASSIGNED";
      break;
  case PROCESS_INTERNAL_STATE_SCHEDULED:
      return "SCHEDULED";
      break;
  case PROCESS_INTERNAL_STATE_OUTCOME_SELECTED:
      return "OUTCOME_SELECTED";
      break;
  case PROCESS_INTERNAL_STATE_CLOSED:
      return "CLOSED";
      break;
  default:
      return "NONE";
      break;
  }

}
