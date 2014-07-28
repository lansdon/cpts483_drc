#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"
#include "mediationprocess.h"
#include "Mediator.h"
#include "MediatorArg.h"
#include "MediatorKeys.h"

#include <qstring.h>
#include <qdebug.h>
#include "stateupdate.h"
#include <set>
#include <algorithm>


DRCBL::DRCBL()
{
    midSubmitMP       = Mediator::Register(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, [this](MediatorArg arg){ValidateMediationProcess(arg);});
    midLoadMP         = Mediator::Register(MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){LoadMediationProcess(arg);});
    midRecentMP       = Mediator::Register(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS, [this](MediatorArg arg){LoadRecentMediations(arg);});
    midPendingMP      = Mediator::Register(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS, [this](MediatorArg arg){LoadPendingMediations(arg);});
    midScheduledMP    = Mediator::Register(MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS, [this](MediatorArg arg){LoadScheduledMediations(arg);});
    midClosedMP       = Mediator::Register(MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS, [this](MediatorArg arg){LoadClosedMediations(arg);});
    midQueryMP        = Mediator::Register(MKEY_GUI_QUERY_MEDIATION, [this](MediatorArg arg){QueryMediations(arg);});
    midReswaRpt       = Mediator::Register(MKEY_GUI_REQUEST_RESWA_REPORT, [this](MediatorArg arg){QueryResWaReport(arg);});
    midMonthlyRpt     = Mediator::Register(MKEY_GUI_REQUEST_MONTHLY_REPORT, [this](MediatorArg arg){QueryMonthlyReport(arg);});
    midSavePendingMP  = Mediator::Register(MKEY_GUI_MP_SAVE_PENDING, [this](MediatorArg arg) {CalculateInternalStateOnSavePending(arg);});
}

DRCBL::~DRCBL()
{
    Mediator::Unregister(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, midSubmitMP);
    Mediator::Unregister(MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE, midLoadMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS, midRecentMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS, midPendingMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS, midScheduledMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS, midClosedMP);
    Mediator::Unregister(MKEY_GUI_QUERY_MEDIATION, midQueryMP);
    Mediator::Unregister(MKEY_GUI_REQUEST_RESWA_REPORT, midReswaRpt);
    Mediator::Unregister(MKEY_GUI_REQUEST_MONTHLY_REPORT, midMonthlyRpt);
    Mediator::Unregister(MKEY_GUI_MP_SAVE_PENDING, midSavePendingMP);
}

void DRCBL::ValidateMediationProcess(MediatorArg arg) const
{
    QString errorMessage = arg.ErrorMessage();
    bool success = arg.IsSuccessful();
    MediationProcess* mp = nullptr;
    if (success)
    {
       mp = arg.getArg<MediationProcess*>();
       if (mp)
       {
           QString stateMessage = mp->GetStateMessage();
           qDebug() << "BL Begin Validation";
           StateUpdate stateUpdate;
           success = stateUpdate.StateCheck(mp, errorMessage, stateMessage);
           qDebug() << "BL End Validation. Success: " << success << " " << errorMessage;
           mp->SetStateMessage(stateMessage);
       }
       else
       {
           errorMessage = "Invalid Mediation Process";
           success = false;
       }
    }
    if(success)
        Mediator::Call(MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE, mp, success, errorMessage);
    else Mediator::Call(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, mp, success, errorMessage);

}

void DRCBL::CalculateInternalStateOnSavePending(MediatorArg arg) const
{
    QString errorMessage = arg.ErrorMessage();
    bool success = arg.IsSuccessful();
    MediationProcess* mp = nullptr;
    if (success)
    {
       mp = arg.getArg<MediationProcess*>();
       if (mp)
       {
           QString stateMessage = mp->GetStateMessage();
           qDebug() << "BL Begin State Calc";
           StateUpdate stateUpdate;
           success = stateUpdate.StateCheck(mp, errorMessage, stateMessage);
           qDebug() << "BL End State Calc. Success: " << success << " " << errorMessage;
           mp->SetStateMessage(stateMessage);
       }
       else
       {
           errorMessage = "Invalid Mediation Process";
           success = false;
       }
    }
    if(success)
        Mediator::Call(MKEY_BL_SAVE_EVALUATION, mp, success, errorMessage);
    else Mediator::Call(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, mp, success, errorMessage);
}

void DRCBL::LoadRecentMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_RECENT_MEDIATIONS_DONE, arg);
}
void DRCBL::LoadPendingMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_PENDING_MEDIATIONS_DONE, arg);
}
void DRCBL::LoadScheduledMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_SCHEDULED_MEDIATIONS_DONE, arg);
}
void DRCBL::LoadClosedMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_CLOSED_MEDIATIONS_DONE, arg);
}

//
void DRCBL::LoadMediationProcess(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_VALIDATE_LOAD_MEDIATION_PROCESS_FORM_DONE, arg);
}

// Add comments here
void DRCBL::QueryMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_QUERY_MEDIATION, arg);
}

void DRCBL::QueryResWaReport(MediatorArg arg) const
{   qDebug() << "BL ResWaReport request event caught.  Now calling MKEY_BL_REQUEST_RESWA_REPORT";
    Mediator::Call(MKEY_BL_REQUEST_RESWA_REPORT, arg);
    qDebug() << "BL -- AFTER calling report request.";
}

void DRCBL::QueryMonthlyReport(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_MONTHLY_REPORT, arg);
}


