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
#define INSERT_EMPTY_CLIENT_SESSION_DEBUG true
#define INSERT_FULL_CLIENT_SESSION_DEBUG true

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

enum ClientColumns
{
    NUMBERINHOUSEHOLD = 15,
    NUMBERCHILDRENINHOUSEHOLD = 16,
    ATTORNEY = 17,
    ATTORNEYPHONE = 18,
    ATTORNEYEMAIL = 19,
    ASSISTANTNAME = 20,
    ASSISTANTPHONE = 21,
    ASSISTANTEMAIL = 22
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

enum ClientSessionColumns
{
    INCOME = 3,
    FEESCHARGED = 4,
    FEESPAID = 5,
    ATTORNEYEXPECTED = 6,
    ATTORNEYATTENDED = 7,
    SUPPORT = 8,
    CLIENTPHONE = 9,
    ATTABLE = 10
};

class DRC_DB_TESTS : public QObject
{
    Q_OBJECT

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
    void CheckInsertFullClientObject();

    void CheckCreateClientSessionTable();
    void CheckClientSessionColumn();
    void CheckInsertEmptyClientSessionObject();
    void CheckInsertFullClientSessionObject();

    void CheckCreateNotesTable();
    void CheckNotesColumn();
    void CheckInsertEmptyNoteObject();
    void CheckInsertFullNoteObject();


//    void CheckNotesColumn();

//    void InsertPersonObject();
//    void InsertMediationProcess();

//    void CheckErrors();
//    void FindFirstName();

public:
    DRC_DB_TESTS();
    void OutputDebugInfo(QVector<QString> TableColumns, QVector<QString> FromDatabase, QVector<QString> FromFile, QString OutputFileName);
    void OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName);

    void PrintVectorStrings(QVector<QString> PrintThis);

    void PrintObjects();

    void PrintProcessObject(MediationProcess *object);
    void PrintSessionObject(MediationSession *object);
    void PrintClientObject(Party *object);
    void PrintPersonObject(Person *object);
    void PrintNoteObject(Note *object);

    Person* InitializePersonObject(QVector<QString> PersonStringValues);
    MediationProcess* InitializeProcessObject(QVector<QString> ProcessStringValues);
    MediationSession* InitializeSessionObject(QVector<QString> SessionStringValues);
    Party* InitializeClientObject(Person *Primary);
    ClientSessionData* InitializeClientSessionObject(QVector<QString> ClientSessionValues);
    Note* InitializeNoteObject(QVector<QString> NoteStringValues, MediationProcess* ProcessID, MediationSession* SessionID);

    void AllocateTableNames();
    void AllocateVectorValues();
    void AllocateTableColumns();

    void AllocatePersonColumns();
    void AllocateProcessColumns();
    void AllocateSessionColumns();
    void AllocateClientColumns();
    void AllocateClientSessionColumns();
    void AllocateNotesColumns();

    void AllocateEmptyPersonVector();
    void AllocateFullPersonVector();

    void AllocateEmptyProcessVector();
    void AllocateFullProcessVector();

    void AllocateEmptySessionVector();
    void AllocateFullSessionVector();

    void AllocateEmptyClientVector();
    void AllocateFullClientVector();

    void AllocateEmptyClientSessionVector();
    void AllocateFullClientSessionVector();

    void AllocateEmptyNoteValues();
    void AllocateFullNoteValues();

private:
    DRCDB _db;

    QVector<Person*> PersonObjectsTracker;
    QVector<MediationProcess*> ProcessObjectsTracker;
    QVector<MediationSession*> SessionObjectsTracker;
    QVector<Party*> PartyObjectsTracker;
    QVector<ClientSessionData*> ClientSessionObjectsTracker;
    QVector<Note*> NoteObjectsTracker;

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
    QVector<QString> client_session_table_columns;
    QVector<QString> notes_table_columns;

    QVector<QString> empty_person_values;
    QVector<QString> full_person_values;

    QVector<QString> empty_process_values;
    QVector<QString> full_process_values;

    QVector<QString> empty_session_values;
    QVector<QString> full_session_values;

    QVector<QString> empty_client_values;
    QVector<QString> full_client_values;

    QVector<QString> empty_client_session_values;
    QVector<QString> full_client_session_values;

    QVector<QString> empty_note_values;
    QVector<QString> full_note_values;

    Person* EmptyPerson;
    Person* FullPerson;

    MediationProcess* EmptyProcess;
    MediationProcess* FullProcess;

    MediationSession* EmptySession;
    MediationSession* FullSession;

    Party* EmptyParty;
    Party* FullParty;

    ClientSessionData* EmptyClientSession;
    ClientSessionData* FullClientSession;

    Note* EmptyNote;
    Note* FullNote;


private slots:
    void initTestCase()
    {
        QFile::remove(database_name);
    }

    void cleanupTestCase()
    {
        //Database should've closed successfully.
        QCOMPARE(_db.CloseDatabase(), true);

        foreach(Person* object, PersonObjectsTracker)
        {
            delete object;
            object = nullptr;
        }

        foreach(MediationProcess* object, ProcessObjectsTracker)
        {
            delete object;
            object = nullptr;
        }

        foreach(MediationSession* object, SessionObjectsTracker)
        {
            delete object;
            object = nullptr;
        }

        foreach(Party* object, PartyObjectsTracker)
        {
            object->SetPrimary(nullptr);
            delete object;
            object = nullptr;
        }

        foreach(ClientSessionData* object, ClientSessionObjectsTracker)
        {
            delete object;
            object = nullptr;
        }

        foreach(Note* object, NoteObjectsTracker)
        {
            delete object;
            object = nullptr;
        }

        //*******For the sake of this Test Suite, we delete database after every run.*******
        //*******Comment out if undesirable; IE, looking inside file directly.       *******
        //*******Be sure to manually delete if you do comment this line out.         *******

        //QCOMPARE(QFile::remove(database_name), true);
    }
};




//  Change information to accomodate new circumstances.
//======================================================
DRC_DB_TESTS::DRC_DB_TESTS() : DateFormat("yyyy-MM-dd"), DateTimeFormat("yyyy-MM-dd hh:mm:ss"), TimeFormat("hh:mm:ss")
{
    database_name = QString("drc_db.db3");

    AllocateTableNames();

    AllocateTableColumns();

    AllocateVectorValues();

    //Write method that accepts vector, and inserts into DB Object
    FullPerson = InitializePersonObject(full_person_values);
    EmptyPerson = InitializePersonObject(empty_person_values);

    EmptyProcess = InitializeProcessObject(empty_process_values);
    FullProcess = InitializeProcessObject(full_process_values);

    EmptySession = InitializeSessionObject(empty_session_values);
    FullSession = InitializeSessionObject(full_session_values);

    EmptyParty = InitializeClientObject(EmptyPerson);
    FullParty = InitializeClientObject(FullPerson);

    EmptyClientSession = InitializeClientSessionObject(empty_client_session_values);
    FullClientSession = InitializeClientSessionObject(full_client_session_values);

    EmptyNote = InitializeNoteObject(empty_note_values, EmptyProcess, EmptySession);
    FullNote = InitializeNoteObject(full_note_values, FullProcess, FullSession);

}
//=======================================================

void DRC_DB_TESTS::AllocateTableColumns()
{
    AllocatePersonColumns();
    AllocateProcessColumns();
    AllocateSessionColumns();
    AllocateClientColumns();
    AllocateClientSessionColumns();
    AllocateNotesColumns();
}

void DRC_DB_TESTS::AllocateVectorValues()
{
    AllocateEmptyPersonVector();
    AllocateFullPersonVector();

    AllocateEmptyProcessVector();
    AllocateFullProcessVector();

    AllocateEmptySessionVector();
    AllocateFullSessionVector();

    AllocateEmptyClientVector();
    AllocateFullClientVector();

    AllocateEmptyClientSessionVector();
    AllocateFullClientSessionVector();

    AllocateEmptyNoteValues();
    AllocateFullNoteValues();
}

Note* DRC_DB_TESTS::InitializeNoteObject(QVector<QString> NoteStringValues, MediationProcess* ProcessID, MediationSession* SessionID)
{
    Note* object = new Note;
    NoteObjectsTracker.push_back(object);

    qDebug() << ProcessID->GetId();
    qDebug() << SessionID->GetId();

    object->SetMediationId(ProcessID->GetId());
    object->SetSessionId(SessionID->GetId());
    object->SetMessage(                                                        NoteStringValues[3]);
    object->SetCreatedDate(             QDateTime::fromString(                 NoteStringValues[4], DateTimeFormat));

    return object;
}

ClientSessionData* DRC_DB_TESTS::InitializeClientSessionObject(QVector<QString> ClientSessionValues)
{
    ClientSessionData* object = new ClientSessionData;
    ClientSessionObjectsTracker.push_back(object);

    object->setIncome(                                                ClientSessionValues[INCOME]); //income
    object->setFee(                                                   ClientSessionValues[FEESCHARGED]); //feesCharged
    object->setPaid(           (bool)                                 ClientSessionValues[FEESPAID].toInt()); //feesPaid
    object->setAttySaidAttend( (bool)                                 ClientSessionValues[ATTORNEYEXPECTED].toInt()); //AttorneyExpected
    object->setAttyDidAttend(  (bool)                                 ClientSessionValues[ATTORNEYATTENDED].toInt()); //AttorneyAttended
    object->setSupport(                                               ClientSessionValues[SUPPORT].toInt()); //Support
    object->setOnPhone(        (bool)                                 ClientSessionValues[CLIENTPHONE].toInt()); //ClientPhone
    object->setAtTable(        (bool)                                 ClientSessionValues[ATTABLE].toInt()); //AtTable

    return object;
}

Party* DRC_DB_TESTS::InitializeClientObject(Person* Primary)
{
    Party* object = new Party;
    PartyObjectsTracker.push_back(object);

    object->SetPrimary(Primary);

    return object;
}

MediationSession* DRC_DB_TESTS::InitializeSessionObject(QVector<QString> SessionStringValues)
{
    MediationSession* object = new MediationSession;
    SessionObjectsTracker.push_back(object);

    object->SetState(               (SessionStates)                         SessionStringValues[SESSIONSTATUS].toInt());
    object->setOutcome(             (SessionOutcomes)                       SessionStringValues[SESSIONOUTCOME].toInt());
    object->SetCreatedDate(         QDateTime::fromString(                  SessionStringValues[SESSION_CREATEDDATETIME], DateTimeFormat));
    object->SetUpdatedDate(         QDateTime::fromString(                  SessionStringValues[SESSION_UPDATEDDATETIME], DateTimeFormat));
    object->setScheduledDate(       QDate::fromString(                      SessionStringValues[SCHEDULEDTIME].split(" ")[0], DateFormat));
    object->setScheduledTime(       QTime::fromString(                      SessionStringValues[SCHEDULEDTIME].split(" ")[1], TimeFormat));
    object->setMediator1(                                                   SessionStringValues[MEDIATOR1]);
    object->setMediator2(                                                   SessionStringValues[MEDIATOR2]);
    object->setObserver1(                                                   SessionStringValues[OBSERVER1]);
    object->setObserver2(                                                   SessionStringValues[OBSERVER2]);
    object->SetIsShuttle(           (bool)                                  SessionStringValues[SHUTTLE].toInt());

    return object;
}

MediationProcess* DRC_DB_TESTS::InitializeProcessObject(QVector<QString> ProcessStringValues)
{
    MediationProcess* object = new MediationProcess;
    ProcessObjectsTracker.push_back(object);

    object->SetDisputeType(              (DisputeTypes)                      ProcessStringValues[DISPUTETYPE].toInt());
    object->SetCreatedDate(              QDateTime::fromString(              ProcessStringValues[PROCESS_CREATIONDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    object->SetUpdatedDate(              QDateTime::fromString(              ProcessStringValues[PROCESS_UPDATEDDATETIME], QString("yyyy-MM-dd hh:mm:ss")));
    object->SetState(                    (DisputeProcessStates)              ProcessStringValues[DISPUTESTATE].toInt());                  //DisputeProcessStates - PROCESS_STATE_SCHEDULED
    object->SetInternalState(            (DisputeProcessInternalStates)      ProcessStringValues[DISPUTEINTERNALSTATE].toInt());  //DisputeProcessInternalStates - PROCESS_INTERNAL_STATE_SCHEDULED
    object->SetCountyId(                 (CountyIds)                         ProcessStringValues[DISPUTECOUNTY].toInt());                          //CountyIds - COUNTY_BENTON
    object->SetReferralType(             (ReferralTypes)                     ProcessStringValues[REFERALSOURCE].toInt());                  //ReferralTypes - REFERRAL_T_PHONEBOOK
    object->SetInquiryTypes(             (InquiryTypes)                      ProcessStringValues[INQUIRYTYPE].toInt());                   //InquiryTypes - INQUIRY_T_WALKIN
    object->SetInfoOnly(                 (bool)                              ProcessStringValues[INFOONLY].toInt());                               //Info Only - FALSE
    object->SetIsCourtCase(              (bool)                              ProcessStringValues[ISCOURTCASE].toInt());                           //Is Court Case - TRUE
    object->SetCourtDate(                QDate::fromString(                  ProcessStringValues[COURTDATE], DateFormat));
    object->SetCourtType(                (CourtCaseTypes)                    ProcessStringValues[COURTCASETYPE].toInt());                   //CourtCaseTypes - COURT_T_SUPERIOR
    object->SetCourtOrder(                                                   ProcessStringValues[COURTORDERTYPE]);
    object->SetRequiresSpanish(          (bool)                              ProcessStringValues[TRANSLATORREQUIRED].toInt());
    object->SetSessionType(              (SessionTypes)                      ProcessStringValues[SESSIONTYPE].toInt());
    object->setMediationClause(          (bool)                              ProcessStringValues[MEDIATIONCLAUSE].toInt());

    return object;
}

Person* DRC_DB_TESTS::InitializePersonObject(QVector<QString> PersonStringValues)
{
    Person* object = new Person;
    PersonObjectsTracker.push_back(object);

    object->setFirstName(                                                     PersonStringValues[FIRST_NAME]);
    object->setMiddleName(                                                    PersonStringValues[MIDDLE_NAME]);
    object->setLastName(                                                      PersonStringValues[LAST_NAME]);
    object->setStreet(                                                        PersonStringValues[STREET_NAME]);
    object->setUnit(                                                          PersonStringValues[UNIT_NAME]);
    object->setCity(                                                          PersonStringValues[CITY_NAME]);
    object->setState(                                                         PersonStringValues[STATE_NAME]);
    object->setZip(                                                           PersonStringValues[ZIP_CODE]);
    object->setCounty((CountyIds)                                             PersonStringValues[COUNTY_NAME].toInt());
    object->setPrimaryPhone(                                                  PersonStringValues[PRIMARY_PHONE]);
    object->setPrimaryPhoneExt(                                               PersonStringValues[PRIMARY_PHONE_EXT]);
    object->setSecondaryPhone(                                                PersonStringValues[SECONDARY_PHONE]);
    object->setSecondaryPhoneExt(                                             PersonStringValues[SECONDARY_PHONE_EXT]);
    object->setEmail(                                                         PersonStringValues[EMAIL_ADDRESS]);
    object->setNumberInHousehold(                                             PersonStringValues[NUMBERINHOUSEHOLD].toInt());
    object->setNumberChildrenInHousehold(                                     PersonStringValues[NUMBERCHILDRENINHOUSEHOLD].toInt());
    object->setAttorney(                                                      PersonStringValues[ATTORNEY]);
    object->setAttorneyPhone(                                                 PersonStringValues[ATTORNEYPHONE]);
    object->SetAttorneyEmail(                                                 PersonStringValues[ATTORNEYEMAIL]);
    object->setAssistantName(                                                 PersonStringValues[ASSISTANTNAME]);
    object->setAssistantPhone(                                                PersonStringValues[ASSISTANTPHONE]);
    object->setAssistantEmail(                                                PersonStringValues[ASSISTANTEMAIL]);

    return object;
}

void DRC_DB_TESTS::PrintObjects()
{
    PrintPersonObject(FullPerson);
    PrintClientObject(FullParty);
    PrintSessionObject(FullSession);
    PrintNoteObject(FullNote);
    PrintProcessObject(FullProcess);
}

void DRC_DB_TESTS::PrintProcessObject(MediationProcess *object)
{
    qDebug() << "Process Object:------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetDisputeType();
    qDebug() << object->GetCreatedDate().toString(DateTimeFormat);
    qDebug() << object->GetUpdatedDate().toString(DateTimeFormat);
    qDebug() << object->GetState();
    qDebug() << object->GetInternalState();
    qDebug() << object->GetCountyId();
    qDebug() << object->GetReferralType();
    qDebug() << object->GetInquiryType();
    qDebug() << object->GetInfoOnly();
    qDebug() << object->GetIsCourtCase();
    qDebug() << object->GetCourtDate().toString(DateFormat);
    qDebug() << object->GetCourtType();
    qDebug() << object->GetCourtOrder();
    qDebug() << object->GetRequiresSpanish();
    qDebug() << object->GetSessionType();
    qDebug() << object->getMediationClause();
}

void DRC_DB_TESTS::PrintNoteObject(Note *object)
{
    qDebug() << "Note Object:---------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetmediationId();
    qDebug() << object->GetSessionId();
    qDebug() << object->GetMessage();
    qDebug() << object->GetCreatedDate().toString(DateFormat);
}

void DRC_DB_TESTS::PrintSessionObject(MediationSession *object)
{
    qDebug() << "Session Object:------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetState();
    qDebug() << object->getOutcome();
    qDebug() << object->GetCreatedDate().toString(DateTimeFormat);
    qDebug() << object->GetUpdatedDate().toString(DateTimeFormat);
    qDebug() << object->getScheduledDate().toString(DateFormat);
    qDebug() << object->getScheduledTime().toString(TimeFormat);
    qDebug() << object->getMediator1();
    qDebug() << object->getMediator2();
    qDebug() << object->getObserver1();
    qDebug() << object->getObserver2();
    qDebug() << object->GetIsShuttle();
}

void DRC_DB_TESTS::PrintClientObject(Party *object)
{
    qDebug() << "Party Object:---------------------------";
    qDebug() << object->GetId();
    qDebug() << object->GetPrimary()->getNumberInHousehold();
    qDebug() << object->GetPrimary()->getNumberChildrenInHousehold();
    qDebug() << object->GetPrimary()->getAttorney();
    qDebug() << object->GetPrimary()->getAttorneyPhone();
    qDebug() << object->GetPrimary()->getAttorneyEmail();
    qDebug() << object->GetPrimary()->getAssistantName();
    qDebug() << object->GetPrimary()->getAssistantPhone();
    qDebug() << object->GetPrimary()->getAssistantEmail();
}

void DRC_DB_TESTS::PrintPersonObject(Person *object)
{
    qDebug() << "Person Object:--------------------------";
    qDebug() << object->GetId();
    qDebug() << object->getFirstName();
    qDebug() << object->getMiddleName();
    qDebug() << object->getLastName();
    qDebug() << object->getStreet();
    qDebug() << object->getUnit();
    qDebug() << object->getCity();
    qDebug() << object->getState();
    qDebug() << object->getZip();
    qDebug() << object->getCounty();
    qDebug() << object->getPrimaryPhone();
    qDebug() << object->getPrimaryPhoneExt();
    qDebug() << object->getSecondaryPhone();
    qDebug() << object->getSecondaryPhoneExt();
    qDebug() << object->getEmail();
}

void DRC_DB_TESTS::OutputColumnInfo(QVector<QString> DatabaseColumns, QVector<QString> TestColumns, QString OutputFileName)
{
    QFile file(OutputFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString("%1%2\n")
        .arg(QString("Column read from Database"))
        .arg(QString("Column read from File"), SMALLER_DISTANCE_BETWEEN, QLatin1Char(FILL_CHARACTER));
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

void DRC_DB_TESTS::OpenDatabase()
{
    _db.OpenDatabase(database_name);
    QCOMPARE(_db.IsDatabaseOpen(), true);
}

void DRC_DB_TESTS::CorrectDatabaseName()
{
    QCOMPARE(_db.WhatDatabaseName(), database_name);
}

void DRC_DB_TESTS::ForeignKeysActive()
{
    QCOMPARE(_db.WhatOptionsEnabled(), QString("foreign_keys = ON"));
}

void DRC_DB_TESTS::CheckCreatePersonTable()
{
    QCOMPARE(_db.CreatePersonTable(person_table_name), true);
    QCOMPARE(_db.DoesTableExist(person_table_name), true);
}

void DRC_DB_TESTS::CheckPersonColumn()
{
    QVERIFY2(person_table_columns.size() > 0, "Person TestColumn Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(person_table_name);

    QVERIFY2(database_columns.size() > 0, "Person DatabaseColumn Vector Contains No Columns");
    QCOMPARE(person_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, person_table_columns, "VERIFY_PERSON_COLUMNS_DEBUG.txt");
    QCOMPARE(person_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyPersonObject()
{
    QCOMPARE(_db.InsertObject(EmptyPerson), true);
    QVector<QString> EmptyResults = _db.SelectOneFields(person_table_name, "Person_id", 1);
    QVector<QString> TruncatedEmpty = empty_person_values.mid(0,15);
    QCOMPARE(TruncatedEmpty.size(), EmptyResults.size());

    if(INSERT_EMPTY_PERSON_DEBUG)
        OutputDebugInfo(person_table_columns, EmptyResults, TruncatedEmpty, "INSERT_EMPTY_PERSON_DEBUG.txt");

    QCOMPARE(TruncatedEmpty, EmptyResults);
}

void DRC_DB_TESTS::CheckInsertFullPersonObject()
{
    QCOMPARE(_db.InsertObject(FullPerson), true);
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

    OutputColumnInfo(database_columns, mediation_table_columns, "VERIFY_MEDIATION_COLUMNS_DEBUG.txt");
    QCOMPARE(mediation_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyProcessObject()
{
    QCOMPARE(_db.InsertObject(EmptyProcess), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(mediation_table_name, "Process_id", 1);
    QCOMPARE(EmptyResults.size(), empty_process_values.size());

    if(INSERT_EMPTY_PROCESS_DEBUG)
        OutputDebugInfo(mediation_table_columns, EmptyResults, empty_process_values, "INSERT_EMPTY_PROCESS_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_process_values);
}

void DRC_DB_TESTS::CheckInsertFullProcessObject()
{
    QCOMPARE(_db.InsertObject(FullProcess),true);

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

    OutputColumnInfo(database_columns, session_table_columns, "VERIFY_SESSION_COLUMNS_DEBUG.txt");
    QCOMPARE(session_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptySessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(EmptyProcess->GetId(), EmptySession), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(session_table_name, "Session_id", 1);

    QCOMPARE(EmptyResults.size(), empty_session_values.size());

    if(INSERT_EMPTY_SESSION_DEBUG)
        OutputDebugInfo(session_table_columns, EmptyResults, empty_session_values, "INSERT_EMPTY_SESSION_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_session_values);
}

void DRC_DB_TESTS::CheckInsertFullSessionObject()
{
    QCOMPARE(_db.InsertLinkedObject(FullProcess->GetId(), FullSession), true);

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

    OutputColumnInfo(database_columns, client_table_columns, "VERIFY_CLIENT_COLUMNS_DEBUG.txt");
    QCOMPARE(client_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyClientObject()
{
    QCOMPARE(_db.InsertClientObject(EmptyProcess, EmptyParty), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(client_table_name, "Client_id", 1);

    QCOMPARE(EmptyResults.size(), empty_client_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(client_table_columns, EmptyResults, empty_client_values, "INSERT_EMPTY_CLIENT_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_client_values);
}

void DRC_DB_TESTS::CheckInsertFullClientObject()
{
    QCOMPARE(_db.InsertClientObject(FullProcess, FullParty), true);

    QVector<QString> FullResults = _db.SelectOneFields(client_table_name, "Client_id", 2);

    QCOMPARE(FullResults.size(), full_client_values.size());

    if(INSERT_FULL_SESSION_DEBUG)
        OutputDebugInfo(client_table_columns, FullResults, full_client_values, "INSERT_FULL_CLIENT_DEBUG.txt");

    QCOMPARE(FullResults, full_client_values);
}

void DRC_DB_TESTS::CheckCreateClientSessionTable()
{
    QCOMPARE(_db.CreateClientSessionTable(client_session_table_name), true);
    QCOMPARE(_db.DoesTableExist(client_session_table_name), true);
}

void DRC_DB_TESTS::CheckClientSessionColumn()
{
    QVERIFY2(client_session_table_columns.size() > 0, "ClientSession Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(client_session_table_name);

    QVERIFY2(database_columns.size() > 0, "ClientSession DatabaseColumn Vector Contains No Columns");
    QCOMPARE(client_session_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, client_session_table_columns, "VERIFY_CLIENTSESSION_COLUMNS_DEBUG.txt");
    QCOMPARE(client_session_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyClientSessionObject()
{
    QCOMPARE(_db.InsertClientSessionData(EmptyClientSession, EmptySession->GetId(), EmptyParty->GetId()), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(client_session_table_name, "Data_id", 1);

    //PrintVectorStrings(EmptyResults);

    QCOMPARE(EmptyResults.size(), empty_client_session_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(client_session_table_columns, EmptyResults, empty_client_session_values, "INSERT_EMPTY_CLIENTSESSION_DEBUG.txt");

    QCOMPARE(EmptyResults, empty_client_session_values);
}

void DRC_DB_TESTS::CheckInsertFullClientSessionObject()
{
    QCOMPARE(_db.InsertClientSessionData(FullClientSession, FullSession->GetId(), FullParty->GetId()), true);

    QVector<QString> FullResults = _db.SelectOneFields(client_session_table_name, "Data_id", 2);

    QCOMPARE(FullResults.size(), full_client_session_values.size());

    if(INSERT_FULL_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(client_session_table_columns, FullResults, full_client_session_values, "INSERT_FULL_CLIENTSESSION_DEBUG.txt");

    QCOMPARE(FullResults, full_client_session_values);
}

void DRC_DB_TESTS::CheckCreateNotesTable()
{
    QCOMPARE(_db.CreateNotesTable(notes_table_name), true);
    QCOMPARE(_db.DoesTableExist(notes_table_name), true);
}

void DRC_DB_TESTS::CheckNotesColumn()
{
    QVERIFY2(notes_table_columns.size() > 0, "Notes Column Vector Contains No Columns");
    QVector<QString> database_columns = _db.GetColumnsList(notes_table_name);

    QVERIFY2(database_columns.size() > 0, "Notes DatabaseColumn Vector Contains No Columns");
    QCOMPARE(notes_table_columns.size(), database_columns.size());

    OutputColumnInfo(database_columns, notes_table_columns, "VERIFY_NOTES_COLUMNS_DEBUG.txt");
    QCOMPARE(notes_table_columns, database_columns);
}

void DRC_DB_TESTS::CheckInsertEmptyNoteObject()
{
//    EmptyNote.SetMediationId(EmptyProcess->GetId());
//    EmptyNote.SetSessionId(EmptySession->GetId());
//    EmptyNote.SetMessage(                                                       empty_note_values[3]);
//    EmptyNote.SetCreatedDate(           QDateTime::fromString(                  empty_note_values[4], DateTimeFormat));

    QCOMPARE(_db.InsertObject(EmptyNote), true);

    QVector<QString> EmptyResults = _db.SelectOneFields(notes_table_name, "Note_id", 1);

    QCOMPARE(EmptyResults.size(), empty_note_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(notes_table_columns, EmptyResults, empty_note_values, "INSERT_EMPTY_NOTE_DEBUG.txt");

     QCOMPARE(EmptyResults, empty_note_values);
}

void DRC_DB_TESTS::CheckInsertFullNoteObject()
{
//    FullNote.SetMediationId(FullProcess->GetId());
//    FullNote.SetSessionId(FullSession->GetId());
//    FullNote.SetMessage(                                                        full_note_values[3]);
//    FullNote.SetCreatedDate(             QDateTime::fromString(                 full_note_values[4], DateTimeFormat));

    QCOMPARE(_db.InsertObject(FullNote), true);

    QVector<QString> FullResults = _db.SelectOneFields(notes_table_name, "Note_id", 2);

    QCOMPARE(FullResults.size(), full_note_values.size());

    if(INSERT_EMPTY_CLIENT_SESSION_DEBUG)
        OutputDebugInfo(notes_table_columns, FullResults, full_note_values, "INSERT_FULL_NOTE_DEBUG.txt");

    QCOMPARE(FullResults, full_note_values);
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

void DRC_DB_TESTS::AllocateClientSessionColumns()
{
    client_session_table_columns.push_back("Data_id");
    client_session_table_columns.push_back("Client_id");
    client_session_table_columns.push_back("Session_id");
    client_session_table_columns.push_back("income");
    client_session_table_columns.push_back("feesCharged");
    client_session_table_columns.push_back("feesPaid");
    client_session_table_columns.push_back("AttorneyExpected");
    client_session_table_columns.push_back("AttorneyAttended");
    client_session_table_columns.push_back("Support");
    client_session_table_columns.push_back("ClientPhone");
    client_session_table_columns.push_back("AtTable");
}

void DRC_DB_TESTS::AllocateNotesColumns()
{
    notes_table_columns.push_back("Note_id");
    notes_table_columns.push_back("Process_id");
    notes_table_columns.push_back("Session_id");
    notes_table_columns.push_back("Note");
    notes_table_columns.push_back("CreateDate");
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

void DRC_DB_TESTS::AllocateFullClientVector()
{
    full_client_values.push_back("2");     //Client ID
    full_client_values.push_back("2");     //Process ID
    full_client_values.push_back("2");     //Person ID
    full_client_values.push_back("1000");     //Number of Children in Household
    full_client_values.push_back("7");     //Number of Adults in Houeshold
    full_client_values.push_back("Birdman");      //Attorney Name
    full_client_values.push_back("123-123-1234");      //Attorney Phone
    full_client_values.push_back("Birdman@Attorney.law");      //Attorney Email
    full_client_values.push_back("Rachel Dawes");      //Assistant Name
    full_client_values.push_back("333-333-3333");      //Assistant Phone
    full_client_values.push_back("MaskNotMe@Attorney.law");      //Assistant Email
}

void DRC_DB_TESTS::AllocateEmptyClientSessionVector()
{
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("1");
    empty_client_session_values.push_back("");
    empty_client_session_values.push_back("");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
    empty_client_session_values.push_back("0");
}

void DRC_DB_TESTS::AllocateFullClientSessionVector()
{
    full_client_session_values.push_back("2");                      //Data_id
    full_client_session_values.push_back("2");                      //Client_id
    full_client_session_values.push_back("2");                      //Session_id
    full_client_session_values.push_back("100000000");              //income - QString
    full_client_session_values.push_back("50");                     //feesCharged - QString
    full_client_session_values.push_back("1");                      //feesPaid - TRUE
    full_client_session_values.push_back("1");                      //AttorneyExpected - TRUE
    full_client_session_values.push_back("1");                      //AttorneyAttended - TRUE
    full_client_session_values.push_back("5000");                   //Support - INT
    full_client_session_values.push_back("1");                      //ClientPhone - TRUE
    full_client_session_values.push_back("1");                      //AtTable - TRUE
}

void DRC_DB_TESTS::AllocateEmptyNoteValues()
{
    empty_note_values.push_back("1");
    empty_note_values.push_back("1");
    empty_note_values.push_back("1");
    empty_note_values.push_back("Empty Note of Justice.");
    empty_note_values.push_back("2014-07-26 17:23:01");
}

void DRC_DB_TESTS::AllocateFullNoteValues()
{
    full_note_values.push_back("2");
    full_note_values.push_back("2");
    full_note_values.push_back("2");
    full_note_values.push_back("This note is going to be filled with wonderfully meaningful, and useful things.");
    full_note_values.push_back("2700-12-31 23:59:59");
}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
