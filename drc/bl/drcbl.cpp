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
    _midSubmitMP       = Mediator::Register(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, [this](MediatorArg arg){ValidateMediationProcess(arg);});
    _midLoadMP         = Mediator::Register(MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){LoadMediationProcess(arg);});
    _midRecentMP       = Mediator::Register(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS, [this](MediatorArg arg){LoadRecentMediations(arg);});
    _midPendingMP      = Mediator::Register(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS, [this](MediatorArg arg){LoadPendingMediations(arg);});
    _midScheduledMP    = Mediator::Register(MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS, [this](MediatorArg arg){LoadScheduledMediations(arg);});
    _midClosedMP       = Mediator::Register(MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS, [this](MediatorArg arg){LoadClosedMediations(arg);});
    _midClosedFeesDueMP = Mediator::Register(MKEY_DOCK_REQUEST_CLOSED_FEES_DUE_MEDIATIONS, [this](MediatorArg arg){LoadClosedFeesDueMediations(arg);});
    _midQueryMP        = Mediator::Register(MKEY_GUI_QUERY_MEDIATION, [this](MediatorArg arg){QueryMediations(arg);});
    _midReswaRpt       = Mediator::Register(MKEY_GUI_REQUEST_RESWA_REPORT, [this](MediatorArg arg){QueryResWaReport(arg);});
    _midMonthlyRpt     = Mediator::Register(MKEY_GUI_REQUEST_MONTHLY_REPORT, [this](MediatorArg arg){QueryMonthlyReport(arg);});
    _midSavePendingMP  = Mediator::Register(MKEY_GUI_MP_SAVE_PENDING, [this](MediatorArg arg) {CalculateInternalStateOnSavePending(arg);});
    _midPointer        = Mediator::Register(MKEY_GUI_SEND_MP_POINTER, [this](MediatorArg arg) {ReceiveMPPointer(arg);});

    _activeMP = nullptr;
}

DRCBL::~DRCBL()
{
    Mediator::Unregister(MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM, _midSubmitMP);
    Mediator::Unregister(MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE, _midLoadMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_RECENT_MEDIATIONS, _midRecentMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS, _midPendingMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS, _midScheduledMP);
    Mediator::Unregister(MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS, _midClosedMP);
    Mediator::Unregister(MKEY_GUI_QUERY_MEDIATION, _midQueryMP);
    Mediator::Unregister(MKEY_GUI_REQUEST_RESWA_REPORT, _midReswaRpt);
    Mediator::Unregister(MKEY_GUI_REQUEST_MONTHLY_REPORT, _midMonthlyRpt);
    Mediator::Unregister(MKEY_GUI_MP_SAVE_PENDING, _midSavePendingMP);
    Mediator::Unregister(MKEY_GUI_SEND_MP_POINTER, _midPointer);
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
    MediationProcess* mp = _activeMP;
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

    //Mediator::Call(MKEY_GUI_MP_POPULATE, mp, success, errorMessage);

}

void DRCBL::ReceiveMPPointer(MediatorArg arg)
{
    _activeMP = arg.getArg<MediationProcess*>();
    CalculateInternalStateOnSavePending(nullptr);
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
void DRCBL::LoadClosedFeesDueMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_CLOSED_FEES_DUE_MEDIATIONS_DONE, arg);
}
//
void DRCBL::LoadMediationProcess(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_VALIDATE_LOAD_MEDIATION_PROCESS_FORM_DONE, arg);
}

void DRCBL::QueryMediations(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_QUERY_MEDIATION, arg);
}

void DRCBL::QueryResWaReport(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_RESWA_REPORT, arg);
}

void DRCBL::QueryMonthlyReport(MediatorArg arg) const
{
    Mediator::Call(MKEY_BL_REQUEST_MONTHLY_REPORT, arg);
}


