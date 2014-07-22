#ifndef RESWAREPORT_H
#define RESWAREPORT_H
#include "drctypes.h"
#include <QTextCursor>
#include <QTextDocument>

class ResWaReport
{
public:
    // Always initialize object with mediation processes from 6 month period
    ResWaReport(MediationProcessVector* processes);

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

    ////////////////// Section 2 - Calls ///////////////////
    void SetTotalCalls(int num) { _totalCalls = num; }

    ///////////////// Evaluation Sums - (Set by DB!) ///////////////////
    void SetQ1Yes(int num) { _q1Yes = num; }
    void SetQ1No(int num) { _q1No = num; }
    void SetQ1Somewhat(int num) { _q1Somewhat = num; }
    void SetQ2Yes(int num) { _q2Yes = num; }
    void SetQ2No(int num) { _q2No = num; }
    void SetQ2Somewhat(int num) { _q2Somewhat = num; }
    void SetQ3Yes(int num) { _q3Yes = num; }
    void SetQ3No(int num) { _q3No = num; }
    void SetQ3Somewhat(int num) { _q3Somewhat = num; }
    void SetQ4Yes(int num) { _q4Yes = num; }
    void SetQ4No(int num) { _q4No = num; }
    void SetQ4Somewhat(int num) { _q4Somewhat = num; }
    void SetQ5Yes(int num) { _q5Yes = num; }
    void SetQ5No(int num) { _q5No = num; }
    void SetQ5Somewhat(int num) { _q5Somewhat = num; }
    void SetQ6Yes(int num) { _q6Yes = num; }
    void SetQ6No(int num) { _q6No = num; }
    void SetQ6Somewhat(int num) { _q6Somewhat = num; }

private:
    // MP's spanning 6 month period.
    // All calculations are based on this collection.
    MediationProcessVector* _processes;

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
    int _q1Yes, _q1No, _q1Somewhat;
    int _q2Yes, _q2No, _q2Somewhat;
    int _q3Yes, _q3No, _q3Somewhat;
    int _q4Yes, _q4No, _q4Somewhat;
    int _q5Yes, _q5No, _q5Somewhat;
    int _q6Yes, _q6No, _q6Somewhat;


    ///////  Person section. Set in CalculatePeople()
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

    // 3) Total Calls
    int _totalCalls;

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

    // Text Formatters
    QTextCharFormat _headerFormat;
    QTextCharFormat _tableTextFormat;
    QTextTableCellFormat _tableCellBlue;
    QTextTableCellFormat _tableIndexDark;
    QTextTableCellFormat _tableIndexLight;


    void TextToCell(QTextTable* table, int row, int col, QString txt, QTextCharFormat* format = nullptr, QTextTableCellFormat* cellFormat = nullptr);


     ///////////////////////////////////////////////////
    // Calculations
    ///////////////////////////////////////////////////

    // 1) CASES
    typedef std::vector<std::vector<int>> CasesTable;
    CasesTable _casesTable;
    void CalculateCasesTable();
    void AddMPToCasesTable(DisputeTypes disputeType, CourtCaseTypes courtType, bool settled);

    // 4) TRAININGS
    void CalculateTraining(int& numTrainings, int& numAttendingTraining);
    int GetNumberAttending(MediationSession* session);

    // 5) PEOPLE
    void CalculatePeople();

};

#endif // RESWAREPORT_H
