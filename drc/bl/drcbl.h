#ifndef DRCBL_H
#define DRCBL_H

//namespace drc {
//namespace bl {

#include "mediationprocess.h"
#include "Mediator.h"

class MediatorArg;

/*!
 * \brief The DRCBL class
 */
class DRCBL
{
public:
    DRCBL();
    ~DRCBL();
    /*!
     * \brief AuthenticateUser
     * \param arg
     */
    void AuthenticateUser(MediatorArg arg) const;
    /*!
     * \brief ValidateMediationProcess
     * \param arg the MediationProcess for which state is calculated.
     */
    void ValidateMediationProcess(MediatorArg arg) const;
    /*!
     * \brief Calculates internal state on save pending event
     *
     * \param null
     *
     * Does not send anything to db, so nothing gets saved, but
     * the internal state is calculated for more interactive state
     * message feedback.  Saves calculated message to private activeMP pointer.
     */
    void CalculateInternalStateOnSavePending(MediatorArg arg) const;
    /*!
     * \brief LoadMediationProcess
     * \param arg
     */
    void ReceiveMPPointer(MediatorArg arg);
    /*!
     * \brief LoadMediationProcess
     * \param arg
     */
    void LoadMediationProcess(MediatorArg arg) const;
    /*!
     * \brief LoadRecentMediations
     * \param arg
     */
    void LoadRecentMediations(MediatorArg arg) const;
    /*!
     * \brief LoadPendingMediations
     * \param arg
     */
    void LoadPendingMediations(MediatorArg arg) const;
    /*!
     * \brief LoadScheduledMediations
     * \param arg
     */
    void LoadScheduledMediations(MediatorArg arg) const;
    /*!
     * \brief LoadClosedMediations saves the pointer to the most recent mp
     * \param arg this mediation process pointer will be saved as activeMP
     */
    void LoadClosedMediations(MediatorArg arg) const;
    /*!
     * \brief QueryMediations
     * \param arg
     */
    void QueryMediations(MediatorArg arg) const;
    /*!
     * \brief QueryResWaReport
     * \param arg
     */
    void QueryResWaReport(MediatorArg arg) const;
    /*!
     * \brief QueryMonthlyReport
     * \param arg
     */
    void QueryMonthlyReport(MediatorArg arg) const;

    MediationProcess *GetActiveMP() { return _activeMP; }
    void SetActiveMP(MediationProcess *mp) { _activeMP = mp; }
private:
    MediatorId _midSubmitMP;
    MediatorId _midLoadMP;
    MediatorId _midRecentMP;
    MediatorId _midPendingMP;
    MediatorId _midScheduledMP;
    MediatorId _midClosedMP;
    MediatorId _midQueryMP;
    MediatorId _midReswaRpt;
    MediatorId _midMonthlyRpt;
    MediatorId _midSavePendingMP;
    MediatorId _midPointer;

    MediationProcess* _activeMP;
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
