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
    /*!
     * \brief AuthenticateUser
     * \param arg
     */
    void AuthenticateUser(MediatorArg arg) const;
    /*!
     * \brief ValidateMediationProcess
     * \param arg
     */
    void ValidateMediationProcess(MediatorArg arg) const;
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
     * \brief LoadClosedMediations
     * \param arg
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
private:
};

//}   // end namespace
//}   // end namespace

#endif // DRCBL_H
