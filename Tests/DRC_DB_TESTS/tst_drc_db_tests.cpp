#include <QString>
#include <QtTest>
#include <QTextStream>
#include <QFile>

#include "drcdb.h"
#include "mediationprocess.h"
#include "Person.h"
#include "drctypes.h"

#define INSERT_EMPTY_PERSON_DEBUG true
#define INSERT_FULL_PERSON_DEBUG true
#define INSERT_EMPTY_PROCESS_DEBUG true
#define INSERT_FULL_PROCESS_DEBUG true
#define INSERT_EMPTY_SESSION_DEBUG true
#define INSERT_FULL_SESSION_DEBUG true

#define TITLE_COLUMNS 45
#define DISTANCE_FROM_COLON -30
#define SMALLER_DISTANCE_BETWEEN 37
#define DISTANCE_BETWEEN_COLUMNS 45
#define FILL_CHARACTER ' '

enum PersonColumns
{
    PERSON_ID = 0,
    FIRST_NAME = 1,
    MIDDLE_NAME = 2,
    LAST_NAME = 3,
    STREET_NAME = 4,
    UNIT_NAME = 5,
    CITY_NAME = 6,
    STATE_NAME = 7,
    ZIP_CODE = 8,
    COUNTY_NAME = 9,
    PRIMARY_PHONE = 10,
    PRIMARY_PHONE_EXT = 11,
    SECONDARY_PHONE = 12,
    SECONDARY_PHONE_EXT = 13,
    EMAIL_ADDRESS = 14
};

enum ProcessColumns
{
    PROCESS_ID = 0,
    DISPUTETYPE = 1,
    CREATIONDATE = 2,
    UPDATEDDATE = 3,
    PROCESS_CREATIONDATETIME = 4,
    PROCESS_UPDATEDDATETIME = 5,
    DISPUTESTATE = 6,
    DISPUTEINTERNALSTATE = 7,
    DISPUTECOUNTY = 8,
    REFERALSOURCE = 9,
    INQUIRYTYPE = 10,
    INFOONLY = 11,
    ISCOURTCASE = 12,
    COURTDATE = 13,
    COURTCASETYPE = 14,
    COURTORDERTYPE = 15,
    TRANSLATORREQUIRED = 16,
    SESSIONTYPE = 17,
    MEDIATIONCLAUSE = 18
};

enum SessionColumns
{
    ID = 0,
    FOREIGN_PROCESS_ID = 1,
    SESSIONSTATUS = 2,
    SESSIONOUTCOME = 3,
    SESSION_CREATEDDATETIME = 4,
    SESSION_UPDATEDDATETIME = 5,
    SCHEDULEDTIME = 6,
    MEDIATOR1 = 7,
    MEDIATOR2 = 8,
    OBSERVER1 = 9,
    OBSERVER2 = 10,
    SHUTTLE = 11
};


class DRC_DB_TESTS : public QObject
{
    Q_OBJECT

public:
    DRC_DB_TESTS();
    void OutputDebugInfo(QVector<QString> TableColumns, QVector<QString> FromDatabase, QVector<QString> FromFile, QString OutputFileName);
    void OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName);
    void PrintVectorStrings(QVector<QString> PrintThis);

    void AllocateTableNames();

    void AllocatePersonColumns();
    void AllocateProcessColumns();
    void AllocateSessionColumns();
    void AllocateClientColumns();

    void AllocateEmptyPersonVector();
    void AllocateFullPersonVector();

    void AllocateEmptyProcessVector();
    void AllocateFullProcessVector();

    void AllocateEmptySessionVector();
    void AllocateFullSessionVector();

    void AllocateEmptyClientVector();

private Q_SLOTS:
    void OpenDatabase();
    void CorrectDatabaseName();
    void ForeignKeysActive();

    void CheckCreatePersonTable();
    void CheckPersonColumn();
    void CheckInsertEmptyPersonObject();
    void CheckInsertFullPersonObject();

    void CheckCreateMediationTable();
    void CheckProcessColumn();
    void CheckInsertEmptyProcessObject();
    void CheckInsertFullProcessObject();

    void CheckCreateSessionTable();
    void CheckSessionColumn();
    void CheckInsertEmptySessionObject();
    void CheckInsertFullSessionObject();

    void CheckCreateClientTable();
    void CheckClientColumn();
    void CheckInsertEmptyClientObject();


//    void CheckSessionColumn();
//    void CheckClientColumn();
//    void CheckNotesColumn();

//    void InsertPersonObject();
//    void InsertMediationProcess();

//    void CheckErrors();
//    void FindFirstName();

private:
    DRCDB _db;

    const QString DateFormat;
    const QString DateTimeFormat;
    const QString TimeFormat;

    QString database_name;

    QString person_table_name;
    QString mediation_table_name;
    QString session_table_name;
    QString client_table_name;
    QString notes_table_name;
    QString client_session_table_name;
    QString user_table_name;
    QString evaluationTableName;

    QVector<QString> person_table_columns;
    QVector<QString> mediation_table_columns;
    QVector<QString> session_table_columns;
    QVector<QString> client_table_columns;

    QVector<QString> empty_person_values;
    QVector<QString> full_person_values;

    QVector<QString> empty_process_values;
    QVector<QString> full_process_values;

    QVector<QString> empty_session_values;
    QVector<QString> full_session_values;

    QVector<QString> empty_client_values;
    QVector<QString> full_client_values;

    Person EmptyPerson;
    Person FullPerson;
    MediationProcess FullProcess;
    MediationProcess EmptyProcess;
    MediationSession EmptySession;
    MediationSession FullSession;

    Party EmptyParty;


private slots:
    void initTestCase()
    {
        QFile::remove(database_name);
    }

    void cleanupTestCase()
    {
        //Database should've closed successfully.
        QCOMPARE(_db.CloseDatabase(), true);

        //*******For the sake of this Test Suite, we delete database after every run.*******
        //*******Comment out if undesirable; IE, looking inside file directly.       *******
        //*******Be sure to manually delete if you do comment this line out.         *******

        //QCOMPARE(QFile::remove(database_name), true);
    }
};


void DRC_DB_TESTS::OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName)
{
    QFile file(OutputFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString("%1%2\n")
        .arg(QString("Data read from Database"))
        .arg(QString("Data read from File"), SMALLER_DISTANCE_BETWEEN, QLatin1Char(FILL_CHARACTER));
    for (int index = 0 ; index < TestColumns.size() ; ++index)
    {
        out << QString("%1%2")
            .arg(QString("\"") + DatabaseColumns[index] + QString("\""))
            .arg(QString("\"") + TestColumns[index] + QString("\""), DISTANCE_BETWEEN_COLUMNS , QLatin1Char(FILL_CHARACTER));

        if(DatabaseColumns[index] == TestColumns[index])
            out << QString("\n\n");
        else
            out << QString("%1\n\n").arg("**ERROR**", DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    }
}

//  Change information to accomodate new circumstances.
//======================================================
DRC_DB_TESTS::DRC_DB_TESTS() : DateFormat("yyyy-MM-dd"), DateTimeFormat("yyyy-MM-dd hh:mm:ss"), TimeFormat("hh:mm:ss")
{
    database_name = QString("drc_db.db3");

    AllocateTableNames();

    AllocatePersonColumns();
    AllocateProcessColumns();
    AllocateSessionColumns();
    AllocateClientColumns();

    AllocateEmptyPersonVector();
    AllocateFullPersonVector();

    AllocateEmptyProcessVector();
    AllocateFullProcessVector();

    AllocateEmptySessionVector();
    AllocateFullSessionVector();

    AllocateEmptyClientVector();

    //Write method that accepts vector, and inserts into DB Object
    FullPerson.setFirstName(                                                     full_person_values[FIRST_NAME]);
    FullPerson.setMiddleName(                                                    full_person_values[MIDDLE_NAME]);
    FullPerson.setLastName(                                                      full_person_values[LAST_NAME]);
    FullPerson.setStreet(                                                        full_person_values[STREET_NAME]);
    FullPerson.setUnit(                                                          full_person_values[UNIT_NAME]);
    FullPerson.setCity(                                                          full_person_values[CITY_NAME]);
    FullPerson.setState(                                                         full_person_values[STATE_NAME]);
    FullPerson.setZip(                                                           full_person_values[ZIP_CODE]);
    FullPerson.setCounty((CountyIds)                                             full_person_values[COUNTY_NAME].toInt());
    FullPerson.setPrimaryPhone(                                                  full_person_values[PRIMARY_PHONE]);
    FullPerson.setPrimaryPhoneExt(                                               full_person_values[PRIMARY_PHONE_EXT]);
    FullPerson.setSecondaryPhone(                                                full_person_values[SECONDARY_PHONE]);
    FullPerson.setSecondaryPhoneExt(                                             full_person_values[SECONDARY_PHONE_EXT]);
    FullPerson.setEmail(                                                         full_person_values[EMAIL_ADDRESS]);
    FullPerson.setNumberInHousehold(                                             full_person_values[15].toInt());
    FullPerson.setNumberChildrenInHousehold(                                     full_person_values[16].toInt());
    FullPerson.setAttorney(                                                      full_person_values[17]);
    FullPerson.setAttorneyPhone(                                                 full_person_values[18]);
    FullPerson.SetAttorneyEmail(                                                 full_person_values[19]);
    FullPerson.setAssistantName(                                                 full_person_values[20]);
    FullPerson.setAssistantPhone(                                                full_person_values[21]);
    FullPerson.setAssistantEmail(                                                full_person_values[22]);

    EmptyProcess.SetCreatedDate(QDateTime::fromString(empty_process_values[PROCESS_CREATIONDATETIME], DateTimeFormat));
    EmptyProcess.SetUpdatedDate(QDateTime::fromString(empty_process_values[PROCESS_UPDATEDDATETIME], DateTimeFormat));
    EmptyProcess.SetCourtDate(QDate::fromString(empty_process_values[COURTDATE], DateFormat));

    FullProcess.SetDisputeType(              (DisputeTypes)                      full_process_values[DISPUTETYPE].toInt());
    FullProcess.SetCreatedDate(              QDateTime::fromString(              full_process_values[PROCESS_CREATIONDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    FullProcess.SetUpdatedDate(              QDateTime::fromString(              full_process_values[PROCESS_UPDATEDDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    FullProcess.SetState(                    (DisputeProcessStates)              full_process_values[DISPUTESTATE].toInt());                  //DisputeProcessStates - PROCESS_STATE_SCHEDULED
    FullProcess.SetInternalState(            (DisputeProcessInternalStates)      full_process_values[DISPUTEINTERNALSTATE].toInt());  //DisputeProcessInternalStates - PROCESS_INTERNAL_STATE_SCHEDULED
    FullProcess.SetCountyId(                 (CountyIds)                         full_process_values[DISPUTECOUNTY].toInt());                          //CountyIds - COUNTY_BENTON
    FullProcess.SetReferralType(             (ReferralTypes)                     full_process_values[REFERALSOURCE].toInt());                  //ReferralTypes - REFERRAL_T_PHONEBOOK
    FullProcess.SetInquiryTypes(             (InquiryTypes)                      full_process_values[INQUIRYTYPE].toInt());                   //InquiryTypes - INQUIRY_T_WALKIN
    FullProcess.SetInfoOnly(                 (bool)                              full_process_values[INFOONLY].toInt());                               //Info Only - FALSE
    FullProcess.SetIsCourtCase(              (bool)                              full_process_values[ISCOURTCASE].toInt());                           //Is Court Case - TRUE
    FullProcess.SetCourtDate(                QDate::fromString(                  full_process_values[COURTDATE], DateFormat));
    FullProcess.SetCourtType(                (CourtCaseTypes)                    full_process_values[COURTCASETYPE].toInt());                   //CourtCaseTypes - COURT_T_SUPERIOR
    FullProcess.SetCourtOrder(                                                   full_process_values[COURTORDERTYPE]);
    FullProcess.SetRequiresSpanish(          (bool)                              full_process_values[TRANSLATORREQUIRED].toInt());
    FullProcess.SetSessionType(              (SessionTypes)                      full_process_values[SESSIONTYPE].toInt());
    FullProcess.setMediationClause(          (bool)                              full_process_values[MEDIATIONCLAUSE].toInt());

//    FullProcess.SetCourtOrderType(           (CourtOrderTypes)                   full_process_values[COURTORDERTYPE].toInt());
//    FullProcess.SetCourtOrderExpiration(     QDateTime::fromString(              full_process_values[COURTORDEREXPIRATION], "yyyy-MM-dd"));
//    FullProcess.SetIsShuttle(                (bool)                              full_process_values[SHUTTLEREQUIRED].toInt());

    //EmptySession.SetId(                 empty_session_values[0].toInt());
    EmptySession.SetState(              (SessionStates)                         empty_session_values[SESSIONSTATUS].toInt());
    EmptySession.setOutcome(            (SessionOutcomes)                       empty_session_values[SESSIONOUTCOME].toInt());
    EmptySession.SetCreatedDate(        QDateTime::fromString(                  empty_session_values[SESSION_CREATEDDATETIME], DateTimeFormat));
    EmptySession.SetUpdatedDate(        QDateTime::fromString(                  empty_session_values[SESSION_UPDATEDDATETIME], DateTimeFormat));
    EmptySession.setScheduledDate(      QDate::fromString(                      empty_session_values[SCHEDULEDTIME].split(" ")[0], DateFormat));
    EmptySession.setScheduledTime(      QTime::fromString(                      empty_session_values[SCHEDULEDTIME].split(" ")[1], TimeFormat));
    EmptySession.setMediator1(                                                  empty_session_values[MEDIATOR1]);
    EmptySession.setMediator2(                                                  empty_session_values[MEDIATOR2]);
    EmptySession.setObserver1(                                                  empty_session_values[OBSERVER1]);
    EmptySession.setObserver2(                                                  empty_session_values[OBSERVER2]);
    EmptySession.SetIsShuttle(          (bool)                                  empty_session_values[SHUTTLE].toInt());

    FullSession.SetState(               (SessionStates)                         full_session_values[SESSIONSTATUS].toInt());
    FullSession.setOutcome(             (SessionOutcomes)                       full_session_values[SESSIONOUTCOME].toInt());
    FullSession.SetCreatedDate(         QDateTime::fromString(                  full_session_values[SESSION_CREATEDDATETIME], DateTimeFormat));
    FullSession.SetUpdatedDate(         QDateTime::fromString(                  full_session_values[SESSION_UPDATEDDATETIME], DateTimeFormat));
    FullSession.setScheduledDate(       QDate::fromString(                      full_session_values[SCHEDULEDTIME].split(" ")[0], DateFormat));
    FullSession.setScheduledTime(       QTime::fromString(                      full_session_values[SCHEDULEDTIME].split(" ")[1], TimeFormat));
    FullSession.setMediator1(                                                   full_session_values[MEDIATOR1]);
    FullSession.setMediator2(                                                   full_session_values[MEDIATOR2]);
    FullSession.setObserver1(                                                   full_session_values[OBSERVER1]);
    FullSession.setObserver2(                                                   full_session_values[OBSERVER2]);
    FullSession.SetIsShuttle(           (bool)                                  full_session_values[SHUTTLE].toInt());

    EmptyParty.SetPrimary(&EmptyPerson);
}
//=======================================================

void DRC_DB_TESTS::OutputDebugInfo(QVector<QString> TableColumns, QVector<QString> FromDatabase, QVector<QString> FromFile, QString OutputFileName)
{
    QFile file(OutputFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString("%1%2\n")
        .arg(QString("Data read from Database"), TITLE_COLUMNS, QLatin1Char(FILL_CHARACTER))
        .arg(QString("Data read from File"), DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    for (int index = 0 ; index < FromFile.size() ; ++index)
    {
        out << QString("%1%2%3")
            .arg(TableColumns[index] + QString(": "), DISTANCE_FROM_COLON, QLatin1Char(FILL_CHARACTER))
            .arg(QString("\"") + FromDatabase[index] + QString("\""))
            .arg(QString("\"") + FromFile[index] + QString("\""), DISTANCE_BETWEEN_COLUMNS , QLatin1Char(FILL_CHARACTER));

        if(FromDatabase[index] == FromFile[index])
            out << QString("\n\n");
        else
            out << QString("%1\n\n").arg("**ERROR**", DISTANCE_BETWEEN_COLUMNS, QLatin1Char(FILL_CHARACTER));
    }
}

void DRC_DB_TESTS::PrintVectorStrings(QVector<QString> PrintThis)
{
    qDebug() << "Printing your damn Vector:";
    foreach (QString line, PrintThis)
        qDebug() << line;
    qDebug();
}

//Default constructor should've opened the database.
void DRC_DB_TESTS::OpenDatabase()
{
    _db.OpenDatabase(database_name);
    QCOMPARE(_db.IsDatabaseOpen(), true);
}

//Just making sure the database is named what it's supposed to.
void DRC_DB_TESTS::CorrectDatabaseName()
{
    QCOMPARE(_db.WhatDatabaseName(), database_name);
}

//Make sure Foreign keys were enabled.
void DRC_DB_TESTS::ForeignKeysActive()
{
    QCOMPARE(_db.WhatOptionsEnabled(), QString("foreign_keys = ON"));
}

void DRC_DB_TESTS::CheckCreatePersonTable()
{
    QCOMPARE(_db.CreatePersonTable(person_table_name), true);
    QCOMPARE(_db.DoesTableExist(person_table_name), true);
}

//Verify all person columns that should be inside table are there.
void DRC_DB_TESTS::CheckPersonColumn()
{
    QVERIFY2(person_table_columns.size() > 0, "Person TestColumn Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(person_table_name);

    QVERIFY2(database_columns.size() > 0, "Person DatabaseColumn Vector Contains No Columns");
    QCOMPARE(person_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, person_table_columns, "PERSON_COLUMNS_DEBUG.txt");
    QCOMPARE(person_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyPersonObject()
{
    QCOMPARE(_db.InsertObject(&EmptyPerson), true);
    QVector<QString> EmptyResults = _db.SelectOneFields(person_table_name, "Person_id", 1);
    QVector<QString> TruncatedEmpty = empty_person_values.mid(0,15);
    QCOMPARE(TruncatedEmpty.size(), EmptyResults.size());

    if(INSERT_EMPTY_PERSON_DEBUG)
        OutputDebugInfo(person_table_columns, EmptyResults, TruncatedEmpty, "INSERT_EMPTY_PERSON_DEBUG.txt");

    QCOMPARE(TruncatedEmpty, EmptyResults);
}

void DRC_DB_TESTS::CheckInsertFullPersonObject()
{
    QCOMPARE(_db.InsertObject(&FullPerson), true);
    QVector<QString> FullResults = _db.SelectOneFields(person_table_name, "Person_id", 2);

    QCOMPARE(15, FullResults.size());

    QVector<QString> TruncatedPerson = full_person_values.mid(0,15);

    QCOMPARE(FullResults.size(), TruncatedPerson.size());

    if (INSERT_FULL_PERSON_DEBUG)
        OutputDebugInfo(person_table_columns, FullResults, TruncatedPerson, "INSERT_FULL_PERSON_DEBUG.txt");

    QCOMPARE(TruncatedPerson, FullResults);
}

void DRC_DB_TESTS::CheckCreateMediationTable()
{
    QCOMPARE(_db.CreateMediationTable(mediation_table_name), true);
    QCOMPARE(_db.DoesTableExist(mediation_table_name), true);
}

void DRC_DB_TESTS::CheckProcessColumn()
{
    QVERIFY2(mediation_table_columns.size() > 0, "Mediation Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(mediation_table_name);

    QVERIFY2(database_columns.size() > 0, "Mediation DatabaseColumn Vector Contains No Columns");
    QCOMPARE(mediation_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, mediation_table_columns, "MEDIATION_COLUMNS_DEBUG.txt");
    QCOMPARE(mediation_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyProcessObject()
{
    QCOMPARE(_db.InsertObject(&EmptyProcess), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(mediation_table_name, "Process_id", 1);
    QCOMPARE(EmptyResults.size(), empty_process_values.size());

    if(INSERT_EMPTY_PROCESS_DEBUG)
        OutputDebugInfo(mediation_table_columns, EmptyResults, empty_process_values, "INSERT_EMPTY_PROCESS_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_process_values);
}

void DRC_DB_TESTS::CheckInsertFullProcessObject()
{
    QCOMPARE(_db.InsertObject(&FullProcess),true);

    QVector<QString> FullResults = _db.SelectOneFields(mediation_table_name, "Process_id", 2);

    if(INSERT_FULL_PROCESS_DEBUG)
        OutputDebugInfo(mediation_table_columns, FullResults, full_process_values, "INSERT_FULL_PROCESS_DEBUG.txt");

    QCOMPARE(full_process_values, FullResults);
}

void DRC_DB_TESTS::CheckCreateSessionTable()
{
    QCOMPARE(_db.CreateSessionTable(session_table_name), true);
    QCOMPARE(_db.DoesTableExist(session_table_name), true);
}

void DRC_DB_TESTS::CheckSessionColumn()
{
    QVERIFY2(session_table_columns.size() > 0, "Session Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(session_table_name);

    QVERIFY2(database_columns.size() > 0, "Session DatabaseColumn Vector Contains No Columns");
    QCOMPARE(session_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, session_table_columns, "SESSION_COLUMNS_DEBUG.txt");
    QCOMPARE(session_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptySessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(EmptyProcess.GetId(), &EmptySession), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(session_table_name, "Session_id", 1);

    QCOMPARE(EmptyResults.size(), empty_session_values.size());

    if(INSERT_EMPTY_SESSION_DEBUG)
        OutputDebugInfo(session_table_columns, EmptyResults, empty_session_values, "INSERT_EMPTY_SESSION_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_session_values);
}

void DRC_DB_TESTS::CheckInsertFullSessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(FullProcess.GetId(), &FullSession), true);

    QVector<QString> FullResults = _db.SelectOneFields(session_table_name, "Session_id", 2);

    QCOMPARE(FullResults.size(), empty_session_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(session_table_columns, FullResults, full_session_values, "INSERT_FULL_SESSION_DEBUG.txt");

    QCOMPARE(FullResults, full_session_values);
}

void DRC_DB_TESTS::CheckCreateClientTable()
{
    QCOMPARE(_db.CreateClientTable(client_table_name), true);
    QCOMPARE(_db.DoesTableExist(client_table_name), true);
}

void DRC_DB_TESTS::CheckClientColumn()
{
    QVERIFY2(client_table_columns.size() > 0, "Client Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(client_table_name);

    QVERIFY2(database_columns.size() > 0, "Client DatabaseColumn Vector Contains No Columns");
    QCOMPARE(client_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, client_table_columns, "CLIENT_COLUMNS_DEBUG.txt");
    QCOMPARE(client_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyClientObject()
{
    QCOMPARE(_db.InsertClientObject(&EmptyProcess, &EmptyParty), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(client_table_name, "Client_id", 1);

    QCOMPARE(EmptyResults.size(), empty_client_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(client_table_columns, EmptyResults, empty_client_values, "INSERT_EMPTY_CLIENT_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_client_values);
}

void DRC_DB_TESTS::AllocateTableNames()
{
    person_table_name = QString("Person_Table");
    mediation_table_name = QString("Mediation_Table");
    session_table_name = QString("Session_Table");
    client_table_name = QString("Client_Table");
    notes_table_name = QString("Notes_Table");
    client_session_table_name = QString("Client_session_table");
    user_table_name = QString("User_Table");
    evaluationTableName = QString("Evaluation_Table");
}


void DRC_DB_TESTS::AllocatePersonColumns()
{
    person_table_columns.push_back("Person_id");
    person_table_columns.push_back("first_name");
    person_table_columns.push_back("middle_name");
    person_table_columns.push_back("last_name");
    person_table_columns.push_back("street_name");
    person_table_columns.push_back("unit_name");
    person_table_columns.push_back("city_name");
    person_table_columns.push_back("state_name");
    person_table_columns.push_back("zip_code");
    person_table_columns.push_back("county_name");
    person_table_columns.push_back("primary_phone");
    person_table_columns.push_back("primary_phone_ext");
    person_table_columns.push_back("secondary_phone");
    person_table_columns.push_back("secondary_phone_ext");
    person_table_columns.push_back("email_address");
}

void DRC_DB_TESTS::AllocateProcessColumns()
{
    mediation_table_columns.push_back("Process_id");
    mediation_table_columns.push_back("DisputeType");
    mediation_table_columns.push_back("CreationDate");
    mediation_table_columns.push_back("UpdatedDate");
    mediation_table_columns.push_back("CreationDateTime");
    mediation_table_columns.push_back("UpdatedDateTime");
    mediation_table_columns.push_back("DisputeState");
    mediation_table_columns.push_back("DisputeInternalState");
    mediation_table_columns.push_back("DisputeCounty");
    mediation_table_columns.push_back("ReferalSource");
    mediation_table_columns.push_back("InquiryType");
    mediation_table_columns.push_back("InfoOnly");
    mediation_table_columns.push_back("IsCourtCase");
    mediation_table_columns.push_back("CourtDate");
    mediation_table_columns.push_back("CourtCaseType");
    mediation_table_columns.push_back("CourtOrderType");
    mediation_table_columns.push_back("TranslatorRequired");
    mediation_table_columns.push_back("SessionType");
    mediation_table_columns.push_back("MediationClause");
}

void DRC_DB_TESTS::AllocateSessionColumns()
{
    session_table_columns.push_back("Session_id");
    session_table_columns.push_back("Process_id");
    session_table_columns.push_back("SessionStatus");
    session_table_columns.push_back("SessionOutcome");
    session_table_columns.push_back("CreatedDateTime");
    session_table_columns.push_back("UpdatedDateTime");
    session_table_columns.push_back("ScheduledTime");
    session_table_columns.push_back("Mediator1");
    session_table_columns.push_back("Mediator2");
    session_table_columns.push_back("Observer1");
    session_table_columns.push_back("Observer2");
    session_table_columns.push_back("Shuttle");
}

void DRC_DB_TESTS::AllocateClientColumns()
{
    client_table_columns.push_back("Client_id");
    client_table_columns.push_back("Process_id");
    client_table_columns.push_back("Person_id");
    client_table_columns.push_back("Children");
    client_table_columns.push_back("Adult");
    client_table_columns.push_back("AttorneyName");
    client_table_columns.push_back("AttorneyPhone");
    client_table_columns.push_back("AttorneyEmail");
    client_table_columns.push_back("AssistantName");
    client_table_columns.push_back("AssistantPhone");
    client_table_columns.push_back("AssistantEmail");
}


void DRC_DB_TESTS::AllocateEmptyPersonVector()
{
    empty_person_values.push_back(QString("1"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString("0"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString(""));
}

void DRC_DB_TESTS::AllocateFullPersonVector()
{
    full_person_values.push_back(QString("2"));
    full_person_values.push_back(QString("Bruce"));
    full_person_values.push_back(QString("Chan"));
    full_person_values.push_back(QString("Lee"));
    full_person_values.push_back(QString("55555 Huntington Place"));
    full_person_values.push_back(QString("B"));
    full_person_values.push_back(QString("New York"));
    full_person_values.push_back(QString("Alaska"));
    full_person_values.push_back(QString("55555"));
    full_person_values.push_back(QString("2"));
    full_person_values.push_back(QString("111-111-1111"));
    full_person_values.push_back(QString("111"));
    full_person_values.push_back(QString("222-222-2222"));
    full_person_values.push_back(QString("222"));
    full_person_values.push_back(QString("EnterTheDragon@BruceLee.com"));
    full_person_values.push_back(QString("7"));
    full_person_values.push_back(QString("1000"));
    full_person_values.push_back(QString("Birdman"));
    full_person_values.push_back(QString("123-123-1234"));
    full_person_values.push_back(QString("Birdman@Attorney.law"));
    full_person_values.push_back(QString("Rachel Dawes"));
    full_person_values.push_back(QString("333-333-3333"));
    full_person_values.push_back(QString("MaskNotMe@Attorney.law"));
}

void DRC_DB_TESTS::AllocateEmptyProcessVector()
{
    empty_process_values.push_back(QString("1"));                           //PROCESS_ID
    empty_process_values.push_back(QString("0"));                           //DISPUTETYPE
    empty_process_values.push_back(QString("2000-01-01"));                  //CREATIONDATE
    empty_process_values.push_back(QString("2000-01-01"));                  //UPDATEDDATE
    empty_process_values.push_back(QString("2000-01-01 12:00:01"));         //CREATIONDATETIME
    empty_process_values.push_back(QString("2000-01-01 12:00:01"));         //UPDATEDDATETIME
    empty_process_values.push_back(QString("0"));                           //DISPUTESTATE
    empty_process_values.push_back(QString("0"));                           //DISPUTEINTERNALSTATE
    empty_process_values.push_back(QString("1"));                           //DISPUTECOUNTY
    empty_process_values.push_back(QString("0"));                           //REFERALSOURCE
    empty_process_values.push_back(QString("0"));                           //INQUIRYTYPE
    empty_process_values.push_back(QString("0"));                           //INFOONLY
    empty_process_values.push_back(QString("0"));                           //ISCOURTCASE
    empty_process_values.push_back(QString("2000-01-01"));                  //COURTDATE
    empty_process_values.push_back(QString("0"));                           //COURTCASETYPE
    empty_process_values.push_back(QString(""));                            //COURTORDERTYPE
    empty_process_values.push_back(QString("0"));                           //TRANSLATORREQUIRED
    empty_process_values.push_back(QString("0"));                           //SESSIONTYPE
    empty_process_values.push_back(QString("0"));                           //MEDIATIONCLAUSE
}

void DRC_DB_TESTS::AllocateFullProcessVector()
{
    full_process_values.push_back("2");                     //Process ID
    full_process_values.push_back("8");                     //DisputeTypes - DISPUTE_T_WORKPLACE
    full_process_values.push_back("2014-07-24");            //Creation Date     QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    full_process_values.push_back("2014-07-25");            //Updated Date      QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    full_process_values.push_back("2014-07-24 12:00:01");   //Creation DateTime QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    full_process_values.push_back("2014-07-25 12:00:02");   //Updated DateTime  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    full_process_values.push_back("3");                     //DisputeProcessStates - PROCESS_STATE_SCHEDULED
    full_process_values.push_back("7");                     //DisputeProcessInternalStates - PROCESS_INTERNAL_STATE_SCHEDULED
    full_process_values.push_back("2");                     //CountyIds - COUNTY_BENTON
    full_process_values.push_back("14");                    //ReferralTypes - REFERRAL_T_PHONEBOOK
    full_process_values.push_back("4");                     //InquiryTypes - INQUIRY_T_WALKIN
    full_process_values.push_back("0");                     //Info Only - FALSE
    full_process_values.push_back("1");                     //Is Court Case - TRUE
    full_process_values.push_back("2015-07-22");            //COURT DATE
    full_process_values.push_back("2");                     //CourtCaseTypes - COURT_T_SUPERIOR
    full_process_values.push_back("Ultimate Fists of Fury!!!");                     //CourtOrderTypes
    full_process_values.push_back("1");                     //Is Spanish Required - TRUE
    full_process_values.push_back("1");                     //SessionTypes - MEDIATION_SESSION
    full_process_values.push_back("1");                     //MediationClause - TRUE
}

void DRC_DB_TESTS::AllocateEmptySessionVector()
{
    empty_session_values.push_back("1");                        //SESSION_ID
    empty_session_values.push_back("1");                        //PROCESS_ID
    empty_session_values.push_back("1");                        //SESSION_STATE - NONE
    empty_session_values.push_back("1");                        //SESSION_OUTCOME - NONE
    empty_session_values.push_back("2014-07-24 00:00:01");
    empty_session_values.push_back("2014-07-24 00:00:02");
    empty_session_values.push_back("2014-07-28 00:00:03");
    empty_session_values.push_back("MediatorNone1");
    empty_session_values.push_back("MediatorNone2");
    empty_session_values.push_back("ObserverNone1");
    empty_session_values.push_back("ObserverNone2");
    empty_session_values.push_back("0");
}

void DRC_DB_TESTS::AllocateFullSessionVector()
{
    full_session_values.push_back("2");
    full_session_values.push_back("2");
    full_session_values.push_back("3");        //SESSION_STATE_CONFIRMED
    full_session_values.push_back("4");        //SESSION_OUTCOME_AGREEMENT
    full_session_values.push_back("2025-08-25 03:44:55");
    full_session_values.push_back("2025-08-26 06:00:00");
    full_session_values.push_back("2700-08-26 01:00:44");
    full_session_values.push_back("Ironfist");
    full_session_values.push_back("Luke Cage");
    full_session_values.push_back("Red Arrow");
    full_session_values.push_back("Bizzaro");
    full_session_values.push_back("1");
}

void DRC_DB_TESTS::AllocateEmptyClientVector()
{
    
    empty_client_values.push_back("1");     //Client ID
    empty_client_values.push_back("1");     //Process ID
    empty_client_values.push_back("1");     //Person ID
    empty_client_values.push_back("0");     //Number of Children in Household
    empty_client_values.push_back("0");     //Number of Adults in Houeshold
    empty_client_values.push_back("");      //Attorney Name
    empty_client_values.push_back("");      //Attorney Phone
    empty_client_values.push_back("");      //Attorney Email
    empty_client_values.push_back("");      //Assistant Name
    empty_client_values.push_back("");      //Assistant Phone
    empty_client_values.push_back("");      //Assistant Email
}

//void DRC_DB_TESTS::CheckNotesColumn()
//{
//    QCOMPARE(_db.DoesColumnExist(QString("Note_id"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Note"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("CreateDate"), notes_table_name), true);
//}

//    QCOMPARE(_db.DoesColumnExist(QString("first_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("middle_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("last_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("street_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("unit_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("city_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("state_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("zip_code"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("county_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("primary_phone"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("primary_phone_ext"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone_ext"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("email_address"), person_table_name), true);

//    QCOMPARE(_db.DoesColumnExist(QString("number_adult_in_house"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("number_children_in_house"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("attorney_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("attorney_phone"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("attorney_email"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("assistant_name"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("assistant_phone"), person_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("assistant_email"), person_table_name), true);

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
