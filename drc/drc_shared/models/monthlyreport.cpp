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
    for(size_t i = 0; i < mpVec->size(); i++)
    {
        MediationProcess* process = mpVec->at(i);
        int translatorCount = this->getTranslator();

        this->setTranslator(translatorCount++);

        this->m_referrals[process->GetReferralType()]++;
        this->m_disputes[process->GetDisputeType()]++;
        for(size_t sess = 0; sess < process->getMediationSessionVector()->size(); sess++)
        {
            MediationSession* session = process->getMediationSessionVector()->at(sess);
            this->m_outcomes[session->getOutcome()]++;

            int atTable = 0;
            for(size_t num = 0; num < session->getClientSessionDataVector()->size(); num++)
            {
                atTable += session->getClientSessionDataVectorAt(num)->getAtTable();
            }


            this->setAtTable(this->getAtTable() + atTable);
        }
        for(size_t num = 0; num < process->GetParties()->size(); num++)
        {
            this->m_countyCounts[process->GetPartyAtIndex(num)->GetPrimary()->getCounty()]++;
            this->setPeopleIndirect(this->getPeopleIndirect() + process->GetPartyAtIndex(num)->GetPrimary()->getNumberInHousehold());
            this->setChildrenIndirect(this->getChildrenIndirect() + process->GetPartyAtIndex(num)->GetPrimary()->getNumberChildrenInHousehold());
        }
    }

}
