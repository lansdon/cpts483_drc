#ifndef REPORTREQUEST_H
#define REPORTREQUEST_H
#include "DBBaseObject.h"

class ReportRequest
{
public:
    ReportRequest(int month = 1, int year = 2014) : _month(month), _year(year)
    {}

    // reswa helper - use to check 1st/2nd half of year
    bool IsForFirstHalfOfYear() { return (_month >= 1 && _month <= 6); }

    int GetYear() { return _year; }
    void SetYear(int year) { _year = year; }
    int GetMonth() { return _month; }
    void SetMonth(int month) { _month = month; }

private:
    // For reswa, set the month anywhere 1-6 for first half of year
    // 7- 12 for last half of year. Use helper function above to check.
    int _month;

    int _year;

};

#endif // REPORTREQUEST_H
