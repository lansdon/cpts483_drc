#include "monthlyreport.h"
#include "mediationprocess.h"
#include "mediationsession.h"
#include "drctypes.h"

const QString DEF_PDF_PATH = "MONTHLY_REPORT.pdf";

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
    int clauseCount = 0;

    for(size_t i = 0; i < mpVec->size(); i++)
    {
        MediationProcess* process = mpVec->at(i);
        int translatorCount = this->getTranslator();

        if(process->GetInfoOnly())
        {
            infoOnlyCount++;
        }

        if(process->getMediationClause())
        {
            clauseCount++;
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
                atTable += (session->getClientSessionDataVectorAt(num)->getAtTable() ||
                            session->getClientSessionDataVectorAt(num)->getOnPhone());
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

void monthlyreport::pdfReport()
{
    _report = new QTextDocument();
    _report->begin();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setOutputFileName(DEF_PDF_PATH);

    QFont font("Monospace");
    font.setStyleHint(QFont::Courier);
    font.setFixedPitch(true);
    font.setPointSize(10);
    _report->setDefaultFont(font);

    QTextCursor cursor(_report);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::End);

    QString pdfString = "DRCTC Summary Statistics ";
    QDate date(m_year,m_month,1);
    pdfString += "for ";
    pdfString += date.toString("MMMM yyyy");
    pdfString += ".\n\n";
    pdfString += QString("%1:%2")
            .arg(QString("%1").arg("# of Children Indirectly Served", 35))
            .arg(QString::number(m_childrenIndirect), 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg(QString("%1").arg("# of Children Directly Served", 35))
            .arg(QString::number(m_childrenDirect), 5);
    for(int i = 0; i < 7; i++)
    {
        if((CountyIds)i != COUNTY_NONE)
        {
            pdfString += "\n";
            pdfString += QString("%1:%2")
                    .arg(QString("%1").arg(StringForCountyIds((CountyIds)i), 35))
                    .arg(QString::number(m_countyCounts[(CountyIds)i]), 5);
        }
    }

    pdfString += "\n\n================ INTAKE/CASE OUTCOME ===================";
    for(int i = 0; i < 9; i++)
    {
        if((SessionOutcomes)i != SESSION_OUTCOME_NONE)
        {
            pdfString += "\n";
            pdfString += QString("%1%2")
                    .arg(QString("%1:").arg(StringForSessionOutcomes((SessionOutcomes)i), 35))
                    .arg(QString::number(m_outcomes[(SessionOutcomes)i]), 5);
        }
    }
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Open Cases", 35)
            .arg(QString::number(m_openCases), 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Total Intake", 35)
            .arg(QString::number(m_totalIntake), 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Sessions Set & Cancelled", 35)
            .arg(QString::number(m_sessionsCancelled), 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Total Cases Mediated",35)
            .arg(QString::number(totalCasesMediated()), 5);

    pdfString += "\n\n================ REGERRALS per SOURCE =================";
    for(int i = 0; i < 16; i++)
    {
        if((ReferralTypes)i != REFERRAL_T_NONE)
        {
            pdfString += "\n";
            pdfString += QString("%1%2")
                    .arg(QString("%1:").arg(StringForReferralTypes((ReferralTypes)i), 35))
                    .arg(QString::number(m_referrals[(ReferralTypes)i]), 5);
        }
    }
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Total Referrals", 35)
            .arg(QString::number(m_totalReferals), 5);

    pdfString += "\n\n================== CATAGORIES OF SERVICE ===================";
    for(int i = 0; i < 13; i++)
    {
        if((DisputeTypes)i != DISPUTE_T_NONE)
        {
            pdfString += "\n";
            pdfString += QString("%1%2")
                    .arg(QString("%1:").arg(StringForDisputeTypes((DisputeTypes)i), 35))
                    .arg(QString::number(m_disputes[(DisputeTypes)i]), 5);
        }
    }
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Total Services", 35)
            .arg(QString::number(m_totalServices), 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("Intake/Mediators Spanish", 35)
            .arg(m_translator, 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("# of People at the Table", 35)
            .arg(m_atTable, 5);
    pdfString += "\n";
    pdfString += QString("%1:%2")
            .arg("# of People Indirectly Served", 35)
            .arg(m_peopleIndirect, 5);
    pdfString += "\n";

    cursor.insertText(pdfString);

    _report->end();

    _report->print(&printer);

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(DEF_PDF_PATH)))
        qDebug() << "Error opening Monthly Report PDF";

}

int monthlyreport::totalCasesMediated()
{
    return m_outcomes[SESSION_OUTCOME_AGREEMENT] + m_outcomes[SESSION_OUTCOME_NO_AGREEMENT];
}
