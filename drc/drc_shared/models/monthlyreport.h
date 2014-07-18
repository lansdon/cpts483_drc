#ifndef MONTHLYREPORT_H
#define MONTHLYREPORT_H

#include "drctypes.h"
#include <map>

class monthlyreport
{
private:
    short int m_month;
    short int m_year;
    CountyIds m_county;
    int m_translator;
    int m_atTable;
    int m_peopleIndirect;
    int m_childrenIndirect;
    std::map<ReferralTypes, int> m_referrals;
    std::map<DisputeTypes, int> m_disputes;
    std::map<SessionOutcomes, int> m_outcomes;
    std::map<CountyIds, int> m_countyCounts;

    const int m_childrenDirect = 0;

    void setTranslator(int value) {m_translator = value;}
    void setAtTable(int value) {m_atTable = value;}
    void setPeopleIndirect(int value) {m_peopleIndirect = value;}
    void setChildrenIndirect(int value) {m_childrenIndirect = value;}
    void setReferrals(std::map<ReferralTypes, int> value) {m_referrals = value;}
    void setDisputes(std::map<DisputeTypes, int> value) {m_disputes = value;}
    void setOutcomes(std::map<SessionOutcomes, int> value) {m_outcomes = value;}
    void setCountyCounts(std::map<CountyIds, int> value) {m_countyCounts = value;}


public:
    monthlyreport();

    void setMonth(short int value) {m_month = value;}
    void setYear(short int value) {m_year = value;}
    void setCounty(CountyIds value) {m_county = value;}

    void BuildReport(MediationProcessVector mpVec);

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
};

#endif // MONTHLYREPORT_H
