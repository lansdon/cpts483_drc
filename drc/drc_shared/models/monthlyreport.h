#ifndef MONTHLYREPORT_H
#define MONTHLYREPORT_H

#include "drctypes.h"
#include <map>
#include <QTextDocument>

class monthlyreport
{
private:
    short int m_month;
    short int m_year;
    CountyIds m_county; // county clients are from
    CountyIds r_county; // county for which the report is generated.
    int m_translator;
    int m_atTable;
    int m_peopleIndirect;
    int m_childrenIndirect;
    std::map<ReferralTypes, int> m_referrals;
    int m_totalReferals;
    std::map<DisputeTypes, int> m_disputes;
    int m_totalServices;
    std::map<SessionOutcomes, int> m_outcomes;
    int m_infoOnly;
    int m_sessionsCancelled;
    int m_openCases;
    int m_totalIntake;
    int m_clauseCount;
    int totalCasesMediated();
    std::map<CountyIds, int> m_countyCounts;
    QTextDocument *_report;

    const int m_childrenDirect = 0;

    void setTranslator(int value) {m_translator = value;}
    void setAtTable(int value) {m_atTable = value;}
    void setPeopleIndirect(int value) {m_peopleIndirect = value;}
    void setChildrenIndirect(int value) {m_childrenIndirect = value;}
    void setReferrals(std::map<ReferralTypes, int> value) {m_referrals = value;}
    void setDisputes(std::map<DisputeTypes, int> value) {m_disputes = value;}
    void setOutcomes(std::map<SessionOutcomes, int> value) {m_outcomes = value;}
    void setCountyCounts(std::map<CountyIds, int> value) {m_countyCounts = value;}
    void setTotalReferals(int value) {m_totalReferals = value;}
    void setTotalServices(int value) {m_totalServices = value;}
    void setSessionsCancelled(int value) {m_sessionsCancelled = value;}
    void setOpenCases(int value) {m_openCases = value;}
    void setTotalIntake(int value) {m_totalIntake = value;}
    void setInfoOnlyCount(int value) {m_infoOnly = value;}
    void setClauseCount(int value) {m_clauseCount = value;}


public:
    monthlyreport();

    void setMonth(short int value) {m_month = value;}
    void setYear(short int value) {m_year = value;}
    void setCounty(CountyIds value) {m_county = value;}

    void BuildReport(MediationProcessVector* mpVec);

    int getMonth() {return m_month;}
    int getYear() {return m_year;}
    int getCounty() {return m_county;}
    int getTranslator() {return m_translator;}
    int getAtTable() {return m_atTable;}
    int getPeopleIndirect() {return m_peopleIndirect;}
    int getChildrenIndirect() {return m_childrenIndirect;}
    std::map<ReferralTypes, int> getReferrals() {return m_referrals;}
    std::map<DisputeTypes, int> getDisputes() {return m_disputes;}
    std::map<SessionOutcomes, int> getOutcomes() {return m_outcomes;}
    std::map<CountyIds, int> getCountyCounts() {return m_countyCounts;}
    int getTotalReferals() {return m_totalReferals;}
    int getTotalServices() {return m_totalServices;}
    int getSessionsCancelled() {return m_sessionsCancelled;}
    int getOpenCases() {return m_openCases;}
    int getTotalIntake() {return m_totalIntake;}
    int getInfoOnlyCount() {return m_infoOnly;}
    int getClauseCount() {return m_clauseCount;}

    void pdfReport();
};

#endif // MONTHLYREPORT_H
