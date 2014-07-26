#ifndef RESWAREPORT_H
#define RESWAREPORT_H
#include "drctypes.h"
#include <QTextCursor>
#include <QTextDocument>

/*!
 * \brief The ResWaReport class
 */
class ResWaReport
{
public:
    // Always initialize object with mediation processes from 6 month period
    /*!
     * \brief ResWaReport
     * \param processes
     */
    ResWaReport(MediationProcessVector* processes);

    ///////////////// Report Builder ///////////////////
    /*!
     * \brief BuildReport
     */
    void BuildReport();         // Primary call

    ///////////////// User input Section ///////////////////
    /*!
     * \brief SetDRCName
     * \param val
     */
    void SetDRCName(QString val) { _nameOfDRC = val; }
    /*!
     * \brief SetDirectorName
     * \param val
     */
    void SetDirectorName(QString val) { _director = val; }
    /*!
     * \brief SetDirectorPhoneName
     * \param val
     */
    void SetDirectorPhoneName(QString val) { _nameOfDRC = val; }
    /*!
     * \brief SetDirectorEmail
     * \param val
     */
    void SetDirectorEmail(QString val) { _directorEmail = val; }
    /*!
     * \brief SetContactName
     * \param val
     */
    void SetContactName(QString val) { _contactName = val; }
    /*!
     * \brief SetContactPhone
     * \param val
     */
    void SetContactPhone(QString val) { _contactPhone = val; }
    /*!
     * \brief SetContactEmail
     * \param val
     */
    void SetContactEmail(QString val) { _contactEmail = val; }

    ////////////////// Section 2 - Calls ///////////////////
    /*!
     * \brief SetTotalCalls
     * \param num
     */
    void SetTotalCalls(int num) { _totalCalls = num; }

    ///////////////// Evaluation Sums - (Set by DB!) ///////////////////
    /*!
     * \brief SetQ1Yes
     * \param num
     */
    void SetQ1Yes(int num) { _q1Yes = num; }
    /*!
     * \brief SetQ1No
     * \param num
     */
    void SetQ1No(int num) { _q1No = num; }
    /*!
     * \brief SetQ1Somewhat
     * \param num
     */
    void SetQ1Somewhat(int num) { _q1Somewhat = num; }
    /*!
     * \brief SetQ2Yes
     * \param num
     */
    void SetQ2Yes(int num) { _q2Yes = num; }
    /*!
     * \brief SetQ2No
     * \param num
     */
    void SetQ2No(int num) { _q2No = num; }
    /*!
     * \brief SetQ2Somewhat
     * \param num
     */
    void SetQ2Somewhat(int num) { _q2Somewhat = num; }
    /*!
     * \brief SetQ3Yes
     * \param num
     */
    void SetQ3Yes(int num) { _q3Yes = num; }
    /*!
     * \brief SetQ3No
     * \param num
     */
    void SetQ3No(int num) { _q3No = num; }
    /*!
     * \brief SetQ3Somewhat
     * \param num
     */
    void SetQ3Somewhat(int num) { _q3Somewhat = num; }
    /*!
     * \brief SetQ4Yes
     * \param num
     */
    void SetQ4Yes(int num) { _q4Yes = num; }
    /*!
     * \brief SetQ4No
     * \param num
     */
    void SetQ4No(int num) { _q4No = num; }
    /*!
     * \brief SetQ4Somewhat
     * \param num
     */
    void SetQ4Somewhat(int num) { _q4Somewhat = num; }
    /*!
     * \brief SetQ5Yes
     * \param num
     */
    void SetQ5Yes(int num) { _q5Yes = num; }
    /*!
     * \brief SetQ5No
     * \param num
     */
    void SetQ5No(int num) { _q5No = num; }
    /*!
     * \brief SetQ5Somewhat
     * \param num
     */
    void SetQ5Somewhat(int num) { _q5Somewhat = num; }
    /*!
     * \brief SetQ6Yes
     * \param num
     */
    void SetQ6Yes(int num) { _q6Yes = num; }
    /*!
     * \brief SetQ6No
     * \param num
     */
    void SetQ6No(int num) { _q6No = num; }
    /*!
     * \brief SetQ6Somewhat
     * \param num
     */
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
    /*!
     * \brief BuildHeaderSection
     * \param cursor
     */
    void BuildHeaderSection(QTextCursor& cursor);
    /*!
     * \brief BuildCasesSection
     * \param cursor
     */
    void BuildCasesSection(QTextCursor& cursor);
    /*!
     * \brief BuildCallsSection
     * \param cursor
     */
    void BuildCallsSection(QTextCursor& cursor);
    /*!
     * \brief BuildContactsSection
     * \param cursor
     */
    void BuildContactsSection(QTextCursor& cursor);
    /*!
     * \brief BuildTrainingSection
     * \param cursor
     */
    void BuildTrainingSection(QTextCursor& cursor);
    /*!
     * \brief BuildPeopleServedSection
     * \param cursor
     */
    void BuildPeopleServedSection(QTextCursor& cursor);
    /*!
     * \brief BuildOutreachSection
     * \param cursor
     */
    void BuildOutreachSection(QTextCursor& cursor);
    /*!
     * \brief BuildStaffSection
     * \param cursor
     */
    void BuildStaffSection(QTextCursor& cursor);
    /*!
     * \brief BuildEvaluationSection
     * \param cursor
     */
    void BuildEvaluationSection(QTextCursor& cursor);
    /*!
     * \brief OpenReportPDF
     */
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
    /*!
     * \brief CalculateCasesTable
     */
    void CalculateCasesTable();
    /*!
     * \brief AddMPToCasesTable
     * \param disputeType
     * \param courtType
     * \param settled
     */
    void AddMPToCasesTable(DisputeTypes disputeType, CourtCaseTypes courtType, bool settled);

    // 4) TRAININGS
    /*!
     * \brief CalculateTraining
     * \param numTrainings
     * \param numAttendingTraining
     */
    void CalculateTraining(int& numTrainings, int& numAttendingTraining);
    /*!
     * \brief GetNumberAttending
     * \param session
     * \return
     */
    int GetNumberAttending(MediationSession* session);

    // 5) PEOPLE
    /*!
     * \brief CalculatePeople
     */
    void CalculatePeople();

};

#endif // RESWAREPORT_H
