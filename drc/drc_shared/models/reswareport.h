#ifndef RESWAREPORT_H
#define RESWAREPORT_H
#include "drctypes.h"
#include <QTextCursor>
#include <QTextDocument>

class ResWaReport
{
public:
    // Always initialize object with mediation processes from 6 month period
    ResWaReport(MediationProcessVector &processes);

    ///////////////// Report Builder ///////////////////
    void BuildReport();         // Primary call

     ///////////////// User input Section ///////////////////
    void SetDRCName(QString val) { _nameOfDRC = val; }
    void SetDirectorName(QString val) { _director = val; }
    void SetDirectorPhoneName(QString val) { _nameOfDRC = val; }
    void SetDirectorEmail(QString val) { _directorEmail = val; }
    void SetContactName(QString val) { _contactName = val; }
    void SetContactPhone(QString val) { _contactPhone = val; }
    void SetContactEmail(QString val) { _contactEmail = val; }


    ///////////////// Evaluation Sums - (Set by DB!) ///////////////////
    void SetNumByPhone(int num) { _numByPhone = num; }
    void SetNumChildByPhone(int num) { _numChildByPhone = num; }
    void SetNumByCoaching(int num) { _numByCoaching = num; }
    void SetNumChildByCoaching(int num) { _numChildByCoaching = num; }
    void SetNumByPhoneConcilliation(int num) { _numByPhoneConcilliation = num; }
    void SetNumChildByPhoneConcilliation(int num) { _numChildByPhoneConcilliation = num; }
    void SetNumBySessions(int num) { _numBySessions = num; }
    void SetNumChildBySessions(int num) { _numChildBySessions = num; }
    void SetNumBySessionFacilliation(int num) { _numBySessionFacilliation = num; }
    void SetNumChildBySessionFacilliation(int num) { _numChildByPhone = num; }
    void SetNumIndirectly(int num) { _numIndirectly = num; }
    void SetNumChildIndirectly(int num) { _numChildIndirectly = num; }
    void SetNumByTraining(int num) { _numByTraining = num; }
    void SetNumChildByTraining(int num) { _numChildByTraining = num; }
    void SetNumAdditionalServed(int num) { _numAdditionalServed = num; }
    void SetNumChildAdditionalServed(int num) { _numChildAdditionalServed = num; }

private:
    // MP's spanning 6 month period.
    // All calculations are based on this collection.
    MediationProcessVector _processes;

    // The final report object after it's been built.
    QTextDocument* _report;

    // Store Form Meta Data (not part of calculations. user entered?)
    QString _nameOfDRC;
    QString _director;
    QString _directorPhoneNum;
    QString _directorEmail;
    QString _contactName;
    QString _contactPhone;
    QString _contactEmail;

    ///////  Evaluation Fields - Set by DB !!!
    int _numByPhone;
    int _numChildByPhone;
    int _numByCoaching;
    int _numChildByCoaching;
    int _numByPhoneConcilliation;
    int _numChildByPhoneConcilliation;
    int _numBySessions;
    int _numChildBySessions;
    int _numBySessionFacilliation;
    int _numChildBySessionFacilliation;
    int _numIndirectly;
    int _numChildIndirectly;
    int _numByTraining;
    int _numChildByTraining;
    int _numAdditionalServed;
    int _numChildAdditionalServed;



    ///////////////// Report Builder - INTERNAL ///////////////////
    // These functions build the different sections of the report
    ///////////////////////////////////////////////////////////////
    void BuildHeaderSection(QTextCursor& cursor);
    void BuildCasesSection(QTextCursor& cursor);
    void BuildCallsSection(QTextCursor& cursor);
    void BuildContactsSection(QTextCursor& cursor);
    void BuildTrainingSection(QTextCursor& cursor);
    void BuildPeopleServedSection(QTextCursor& cursor);
    void BuildOutreachSection(QTextCursor& cursor);
    void BuildStaffSection(QTextCursor& cursor);
    void BuildEvaluationSection(QTextCursor& cursor);

    void OpenReportPDF();

};

#endif // RESWAREPORT_H
