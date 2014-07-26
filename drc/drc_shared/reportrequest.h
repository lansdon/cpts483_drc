#ifndef REPORTREQUEST_H
#define REPORTREQUEST_H
#include "DBBaseObject.h"
#include "drctypes.h"

/*!
 * \brief The ReportRequest class
 */
class ReportRequest
{
public:
    ReportRequest(int month = 1, int year = 2014, CountyIds county = COUNTY_NONE)
        : _month(month)
        , _year(year)
        , _county(county)
    {}

    // reswa helper - use to check 1st/2nd half of year
    /*!
     * \brief IsForFirstHalfOfYear
     * \return
     */
    bool IsForFirstHalfOfYear() { return (_month >= 1 && _month <= 6); }
    /*!
     * \brief GetYear
     * \return
     */
    int GetYear() { return _year; }
    /*!
     * \brief SetYear
     * \param year
     */
    void SetYear(int year) { _year = year; }
    /*!
     * \brief GetMonth
     * \return
     */
    int GetMonth() { return _month; }
    /*!
     * \brief SetMonth
     * \param month
     */
    void SetMonth(int month) { _month = month; }
    /*!
     * \brief GetCounty
     * \return
     */
    CountyIds GetCounty() { return _county; }
    /*!
     * \brief SetCounty
     * \param county
     */
    void SetCounty(CountyIds county) { _county = county; }

private:
    // For reswa, set the month anywhere 1-6 for first half of year
    // 7- 12 for last half of year. Use helper function above to check.
    int _month;

    int _year;

    CountyIds _county;

};

#endif // REPORTREQUEST_H
