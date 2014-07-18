#include "monthlyreport.h"
#include "mediationprocess.h"
#include "mediationsession.h"
#include "drctypes.h"

monthlyreport::monthlyreport()
{
    this->m_atTable = 0;
    this->m_childrenIndirect = 0;
    this->m_peopleIndirect = 0;
    this->m_translator = 0;
}

void monthlyreport::BuildReport(MediationProcessVector* mpVec)
{
    int referalCount = 0;
    int servicesCount = 0;
    int cancelCount = 0;
    int intakeCount = 0;
    int openCount = 0;
    int infoOnlyCount = 0;

    for(size_t i = 0; i < mpVec->size(); i++)
    {
        MediationProcess* process = mpVec->at(i);
        int translatorCount = this->getTranslator();

        if(process->GetInfoOnly())
        {
            infoOnlyCount++;
        }

        this->setTranslator(translatorCount++);

        if(process->GetReferralType() != REFERRAL_T_NONE)
        {
            referalCount++;
        }

        this->m_referrals[process->GetReferralType()]++;

        if(process->GetDisputeType() != DISPUTE_T_NONE)
        {
            servicesCount++;
        }

        this->m_disputes[process->GetDisputeType()]++;
        for(size_t sess = 0; sess < process->getMediationSessionVector()->size(); sess++)
        {
            MediationSession* session = process->getMediationSessionVector()->at(sess);
            this->m_outcomes[session->getOutcome()]++;
            intakeCount++;



            int atTable = 0;
            for(size_t num = 0; num < session->getClientSessionDataVector()->size(); num++)
            {
                atTable += session->getClientSessionDataVectorAt(num)->getAtTable();
            }

            if((session->GetState() == SESSION_STATE_CANCELLED) ||
                    (session->GetState() == SESSION_STATE_RESCHEDULED))
            {
                cancelCount++;
            }

            this->setAtTable(this->getAtTable() + atTable);
        }

        if(process->getMediationSessionVector()->size() == 0)
        {
            openCount++;
        }
        else
        {
            MediationSession* session = process->getMediationSessionVector()->at((process->getMediationSessionVector()->size() - 1));
            if((session->getOutcome() != SESSION_OUTCOME_AGREEMENT) ||
                    (session->getOutcome() != SESSION_OUTCOME_AGREEMENT) ||
                    (session->getOutcome() != SESSION_OUTCOME_SELF_RESOLVED))
            {
                openCount++;
            }
        }

        for(size_t num = 0; num < process->GetParties()->size(); num++)
        {
            this->m_countyCounts[process->GetPartyAtIndex(num)->GetPrimary()->getCounty()]++;
            this->setPeopleIndirect(this->getPeopleIndirect() + process->GetPartyAtIndex(num)->GetPrimary()->getNumberInHousehold());
            this->setChildrenIndirect(this->getChildrenIndirect() + process->GetPartyAtIndex(num)->GetPrimary()->getNumberChildrenInHousehold());
        }
    }
    this->setInfoOnlyCount(infoOnlyCount);
    this->setTotalReferals(referalCount);
    this->setTotalServices(servicesCount);
    this->setSessionsCancelled(cancelCount);
    this->setTotalIntake(intakeCount);
    this->setOpenCases(openCount);

}
