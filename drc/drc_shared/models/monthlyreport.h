#ifndef MONTHLYREPORT_H
#define MONTHLYREPORT_H

#include "drctypes.h"
#include <map>
#include <QTextDocument>

/*!
 * \brief The monthlyreport class
 */
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
    int m_totalReferals;
    std::map<DisputeTypes, int> m_disputes;
    int m_totalServices;
    std::map<SessionOutcomes, int> m_outcomes;
    int m_infoOnly;
    int m_sessionsCancelled;
    int m_openCases;
    int m_totalIntake;
    int totalCasesMediated();
    std::map<CountyIds, int> m_countyCounts;
    QTextDocument *_report;

    const int m_childrenDirect = 0;

    /*!
     * \brief setTranslator
     * \param value
     */
    void setTranslator(int value) {m_translator = value;}
    /*!
     * \brief setAtTable
     * \param value
     */
    void setAtTable(int value) {m_atTable = value;}
    /*!
     * \brief setPeopleIndirect
     * \param value
     */
    void setPeopleIndirect(int value) {m_peopleIndirect = value;}
    /*!
     * \brief setChildrenIndirect
     * \param value
     */
    void setChildrenIndirect(int value) {m_childrenIndirect = value;}
    /*!
     * \brief setReferrals
     * \param value
     */
    void setReferrals(std::map<ReferralTypes, int> value) {m_referrals = value;}
    /*!
     * \brief setDisputes
     * \param value
     */
    void setDisputes(std::map<DisputeTypes, int> value) {m_disputes = value;}
    /*!
     * \brief setOutcomes
     * \param value
     */
    void setOutcomes(std::map<SessionOutcomes, int> value) {m_outcomes = value;}
    /*!
     * \brief setCountyCounts
     * \param value
     */
    void setCountyCounts(std::map<CountyIds, int> value) {m_countyCounts = value;}
    /*!
     * \brief setTotalReferals
     * \param value
     */
    void setTotalReferals(int value) {m_totalReferals = value;}
    /*!
     * \brief setTotalServices
     * \param value
     */
    void setTotalServices(int value) {m_totalServices = value;}
    /*!
     * \brief setSessionsCancelled
     * \param value
     */
    void setSessionsCancelled(int value) {m_sessionsCancelled = value;}
    /*!
     * \brief setOpenCases
     * \param value
     */
    void setOpenCases(int value) {m_openCases = value;}
    /*!
     * \brief setTotalIntake
     * \param value
     */
    void setTotalIntake(int value) {m_totalIntake = value;}
    /*!
     * \brief setInfoOnlyCount
     * \param value
     */
    void setInfoOnlyCount(int value) {m_infoOnly = value;}

public:
    monthlyreport();
    /*!
     * \brief setMonth
     * \param value
     */
    void setMonth(short int value) {m_month = value;}
    /*!
     * \brief setYear
     * \param value
     */
    void setYear(short int value) {m_year = value;}
    /*!
     * \brief setCounty
     * \param value
     */
    void setCounty(CountyIds value) {m_county = value;}
    /*!
     * \brief BuildReport
     * \param mpVec
     */
    void BuildReport(MediationProcessVector* mpVec);
    /*!
     * \brief getMonth
     * \return
     */
    int getMonth() {return m_month;}
    /*!
     * \brief getYear
     * \return
     */
    int getYear() {return m_year;}
    /*!
     * \brief getCounty
     * \return
     */
    int getCounty() {return m_county;}
    /*!
     * \brief getTranslator
     * \return
     */
    int getTranslator() {return m_translator;}
    /*!
     * \brief getAtTable
     * \return
     */
    int getAtTable() {return m_atTable;}
    /*!
     * \brief getPeopleIndirect
     * \return
     */
    int getPeopleIndirect() {return m_peopleIndirect;}
    /*!
     * \brief getChildrenIndirect
     * \return
     */
    int getChildrenIndirect() {return m_childrenIndirect;}
    /*!
     * \brief getReferrals
     * \return
     */
    std::map<ReferralTypes, int> getReferrals() {return m_referrals;}
    /*!
     * \brief getDisputes
     * \return
     */
    std::map<DisputeTypes, int> getDisputes() {return m_disputes;}
    /*!
     * \brief getOutcomes
     * \return
     */
    std::map<SessionOutcomes, int> getOutcomes() {return m_outcomes;}
    /*!
     * \brief getCountyCounts
     * \return
     */
    std::map<CountyIds, int> getCountyCounts() {return m_countyCounts;}
    /*!
     * \brief getTotalReferals
     * \return
     */
    int getTotalReferals() {return m_totalReferals;}
    /*!
     * \brief getTotalServices
     * \return
     */
    int getTotalServices() {return m_totalServices;}
    /*!
     * \brief getSessionsCancelled
     * \return
     */
    int getSessionsCancelled() {return m_sessionsCancelled;}
    /*!
     * \brief getOpenCases
     * \return
     */
    int getOpenCases() {return m_openCases;}
    /*!
     * \brief getTotalIntake
     * \return
     */
    int getTotalIntake() {return m_totalIntake;}
    /*!
     * \brief getInfoOnlyCount
     * \return
     */
    int getInfoOnlyCount() {return m_infoOnly;}
    /*!
     * \brief pdfReport
     */
    void pdfReport();
};

#endif // MONTHLYREPORT_H
