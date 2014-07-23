#include <QString>
#include <QtTest>

#include "drcdb.h"
#include "mediationprocess.h"
#include "Person.h"

//Tests Still Needed
//1.  Check for Duplicate Insert
//1a.   How can we be sure that they're duplicates and not just different persons?
//2.  Need to prevent table creation if table already exists
//3.  Need to prevent column generation if columns already exist.
//4.  Need a retrieve by first name method
//5.  Need a retrieve by last name method

//Questions / Confirmations
//1.  What is phone number format
//2.  How are extensions to be dealt with

//Notes
//1.  Removed duplicate table check | This check is made in the default constructor


class DRC_DB_TESTS : public QObject
{
    Q_OBJECT

public:
    DRC_DB_TESTS();

private:
    DRCDB _db;

    QString database_name;

    QString person_table_name;
    QString process_table_name;
    QString session_table_name;
    QString client_table_name;
    QString notes_table_name;
    QString client_session_table_name;
    QString user_table_name;
    QString evaluationTableName;

    QVector<QString> full_person_values;
    QVector<QString> empty_person_values;
    Person Bruce_Lee;

private Q_SLOTS:
    void OpenDatabase();
    void CorrectDatabaseName();
    void ForeignKeysActive();

    void CreatePersonTable();
    void CheckPersonColumn();
    void CheckInsertPersonObject();
    void CheckInsertEmptyPersonObject();

    void CheckCreateProcessTable();
    void CheckProcessColumn();
    void CheckInsertEmptyProcessObject();


//    void CheckSessionColumn();
//    void CheckClientColumn();
//    void CheckNotesColumn();

//    void InsertPersonObject();
//    void InsertMediationProcess();

//    void CheckErrors();
//    void FindFirstName();

private slots:
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

//  Change information to accomodate new circumstances.
//======================================================
DRC_DB_TESTS::DRC_DB_TESTS()
{
    database_name = QString("drc_db.db3");

    //Names of all the tables
    person_table_name = QString("Person_Table");
    process_table_name = QString("Process_Table");
    session_table_name = QString("Session_Table");
    client_table_name = QString("Client_Table");
    notes_table_name = QString("Notes_Table");
    client_session_table_name = QString("Client_session_table");
    user_table_name = QString("User_Table");
    evaluationTableName = QString("Evaluation_Table");

    full_person_values.push_back(QString("1"));
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

    empty_person_values.push_back(QString("2"));
    empty_person_values.push_back(QString("John"));
    empty_person_values.push_back(QString(""));
    empty_person_values.push_back(QString("Doe"));
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

    //Insert Fully Populated Object
    Bruce_Lee.setFirstName(full_person_values[1]);
    Bruce_Lee.setMiddleName(full_person_values[2]);
    Bruce_Lee.setLastName(full_person_values[3]);
    Bruce_Lee.setStreet(full_person_values[4]);
    Bruce_Lee.setUnit(full_person_values[5]);
    Bruce_Lee.setCity(full_person_values[6]);
    Bruce_Lee.setState(full_person_values[7]);
    Bruce_Lee.setZip(full_person_values[8]);
    Bruce_Lee.setCounty((CountyIds)full_person_values[9].toInt());
    Bruce_Lee.setPrimaryPhone(full_person_values[10]);
    Bruce_Lee.setPrimaryPhoneExt(full_person_values[11]);
    Bruce_Lee.setSecondaryPhone(full_person_values[12]);
    Bruce_Lee.setSecondaryPhoneExt(full_person_values[13]);
    Bruce_Lee.setEmail(full_person_values[14]);
    Bruce_Lee.setNumberInHousehold(full_person_values[15].toInt());
    Bruce_Lee.setNumberChildrenInHousehold(full_person_values[16].toInt());
    Bruce_Lee.setAttorney(full_person_values[17]);
    Bruce_Lee.setAttorneyPhone(full_person_values[18]);
    Bruce_Lee.SetAttorneyEmail(full_person_values[19]);
    Bruce_Lee.setAssistantName(full_person_values[20]);
    Bruce_Lee.setAssistantPhone(full_person_values[21]);
    Bruce_Lee.setAssistantEmail(full_person_values[22]);
}
//=======================================================




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

void DRC_DB_TESTS::CreatePersonTable()
{
    QCOMPARE(_db.CreatePersonTable(person_table_name), true);
    QCOMPARE(_db.DoesTableExist(person_table_name), true);
}

//Verify all person columns that should be inside table are there.
void DRC_DB_TESTS::CheckPersonColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("id"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("first_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("middle_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("last_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("street_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("unit_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("city_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("state_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("zip_code"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("county_name"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("primary_phone"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("primary_phone_ext"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone_ext"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("email_address"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("number_adult_in_house"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("number_children_in_house"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("attorney_name"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("attorney_phone"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("attorney_email"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("assistant_name"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("assistant_phone"), person_table_name), true);
    // QCOMPARE(_db.DoesColumnExist(QString("assistant_email"), person_table_name), true);
}

void DRC_DB_TESTS::CheckInsertPersonObject()
{
    QCOMPARE(_db.InsertObject(&Bruce_Lee), true);
    QVector<QString> FullResults = _db.SelectOneFields(person_table_name, 1);

    QCOMPARE(15, FullResults.size());

    QVector<QString> TruncatedPerson = full_person_values.mid(0,15);

    QCOMPARE(TruncatedPerson, FullResults);

//  Visually verify that all the values match.
//    for (int index = 0 ; index < full_person_values.size() ; ++index)
//        qDebug() << full_person_values[index] << FullResults[index];

}

void DRC_DB_TESTS::CheckInsertEmptyPersonObject()
{
    Person John_Doe;
    John_Doe.setFirstName("John");
    John_Doe.setLastName("Doe");

    QCOMPARE(_db.InsertObject(&John_Doe), true);
    QVector<QString> EmptyResults = _db.SelectOneFields(person_table_name, 2);
    QVector<QString> TruncatedEmpty = empty_person_values.mid(0,15);
    QCOMPARE(TruncatedEmpty.size(), EmptyResults.size());

    QCOMPARE(TruncatedEmpty, EmptyResults);

//  Visually verify that all the values match.
//    for (int index = 0 ; index < TruncatedEmpty.size() ; ++index)
//        qDebug() << EmptyResults[index] << TruncatedEmpty[index];

}

void DRC_DB_TESTS::CheckCreateProcessTable()
{
    QCOMPARE(_db.CreateProcessTable(process_table_name), true);
    QCOMPARE(_db.DoesTableExist(process_table_name), true);
}

void DRC_DB_TESTS::CheckProcessColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("id"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeType"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CreationDate"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("UpdatedDate"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CreationDateTime"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("UpdatedDateTime"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeState"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeInternalState"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeCounty"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("ReferalSource"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("InquiryType"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("InfoOnly"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CourtCase"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CourtDate"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CourtCaseType"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CourtOrderType"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CourtOrderExpiration"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("ShuttleRequired"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("TranslatorRequired"), process_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("SessionType"), process_table_name), true);
}

void DRC_DB_TESTS::CheckInsertEmptyProcessObject()
{
    MediationProcess EmptyProcess;
    _db.InsertObject(&EmptyProcess);

    QVector<QString> empty_process_values;
    empty_process_values.push_back(QString("1"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(EmptyProcess.GetCreatedDate().toString("yyyy-MM-dd"));
    empty_process_values.push_back(EmptyProcess.GetUpdatedDate().toString("yyyy-MM-dd"));
    empty_process_values.push_back(EmptyProcess.GetCreatedDate().toString("yyyy-MM-dd hh:mm:ss"));
    empty_process_values.push_back(EmptyProcess.GetUpdatedDate().toString("yyyy-MM-dd hh:mm:ss"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("1"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString(""));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString(""));
    empty_process_values.push_back(QString("127"));
    empty_process_values.push_back(QString("0"));
    empty_process_values.push_back(QString("0"));

    QVector<QString> EmptyResults = _db.SelectOneFields(process_table_name, 1);
    QCOMPARE(EmptyResults.size(), empty_process_values.size());

//    for (int index = 0 ; index < EmptyResults.size() ; ++index)
//        qDebug() << EmptyResults[index] << empty_process_values[index];

    QCOMPARE(EmptyResults, empty_process_values);
}

//void DRC_DB_TESTS::CheckSessionColumn()
//{
//    QCOMPARE(_db.DoesColumnExist(QString("Session_id"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("SessionStatus"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Fee1Paid"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Fee2Paid"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("FeeFamilyPaid"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Fee1OtherPaid"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Fee1"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Fee2"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("FeeFamily"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("FeeOther"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("IncomeFee1"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("IncomeFee2"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("IncomeFeeFamily"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("IncomeFeeOther"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Mediator1"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Mediator2"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Observer1"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Observer2"), session_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), session_table_name), true);
//}

//void DRC_DB_TESTS::CheckClientColumn()
//{
//    QCOMPARE(_db.DoesColumnExist(QString("Client_id"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Person_id"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Children"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Observers"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Attorney"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), client_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Person_id"), client_table_name), true);
//}

//void DRC_DB_TESTS::CheckNotesColumn()
//{
//    QCOMPARE(_db.DoesColumnExist(QString("Note_id"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("Note"), notes_table_name), true);
//    QCOMPARE(_db.DoesColumnExist(QString("CreateDate"), notes_table_name), true);
//}

//void DRC_DB_TESTS::InsertPersonObject()
//{
//    Person Tim_Schafer(QString("Tim"));

//    QCOMPARE(_db.InsertObject(&Tim_Schafer), true);

//    Person Bruce_Lee(QString("Bruce"));
//    Bruce_Lee.setMiddleName(QString("Chan"));
//    Bruce_Lee.setLastName(QString("Lee"));
//    Bruce_Lee.setStreet(QString("55555 Huntington Place"));
//    Bruce_Lee.setUnit(QString("#6"));
//    Bruce_Lee.setCity(QString("New York"));
//    Bruce_Lee.setState(QString("Alaska"));
//    Bruce_Lee.setZip(QString("55555"));
//    Bruce_Lee.setCounty(COUNTY_BENTON);
//    Bruce_Lee.setPrimaryPhone(QString("111-111-1111"));
//    Bruce_Lee.setSecondaryPhone(QString("222-222-2222"));
//    Bruce_Lee.setAssistantPhone("333-333-3333");
//    Bruce_Lee.setEmail(QString("EnterTheDragon@BruceLee.com"));
//    Bruce_Lee.setNumberInHousehold(8);
//    Bruce_Lee.setAttorney(QString("Bird Man"));

//    Person Elvis_Presley(QString("Elvis"));
//    Elvis_Presley.setMiddleName(QString("Lee"));
//    Elvis_Presley.setLastName(QString("Chan"));
//    Elvis_Presley.setStreet(QString("4444 Chapelhill Blvd"));
//    Elvis_Presley.setUnit(QString("#5"));
//    Elvis_Presley.setCity(QString("Austin"));
//    Elvis_Presley.setState(QString("Texas"));
//    Elvis_Presley.setZip(QString("44444"));
//    Elvis_Presley.setCounty(COUNTY_FRANLKIN);
//    Elvis_Presley.setPrimaryPhone(QString("222-222-2222"));
//    Elvis_Presley.setSecondaryPhone(QString("111-111-1111"));
//    Elvis_Presley.setAssistantPhone("444-444-4444");
//    Elvis_Presley.setEmail(QString("RushHour@JackieChan.com"));
//    Elvis_Presley.setNumberInHousehold(8);
//    Elvis_Presley.setAttorney(QString("Pheonix Wright"));

//    QCOMPARE(_db.InsertObject(&Bruce_Lee), true);
//    QCOMPARE(_db.InsertObject(&Elvis_Presley), true);

//}

//void DRC_DB_TESTS::InsertMediationProcess()
//{
//    MediationProcess* object = MediationProcess::SampleData();

//    MediatorArg arg;
//    arg.SetArg(object);

//    //_db.InsertMediation(arg);
//    //QCOMPARE(_db.InsertMediation(arg), true);
//}

////Sloppy Initial Test
//void DRC_DB_TESTS::FindFirstName()
//{
//    QVector<QString> EnterTheDragon = _db.SelectPersonField(QString("first_name"), QString("Person_Table"), QString("="), QString("Bruce"));

//    QVERIFY(EnterTheDragon.size() > 0);
//    qDebug() << EnterTheDragon.size();
//    if (!EnterTheDragon.isEmpty())
//    {
//        foreach (QString first_name, EnterTheDragon)
//            qDebug() << first_name;
//    }
//}

//void DRC_DB_TESTS::CheckErrors()
//{
//    QVector<QString> RecentError = _db.GetLastErrors();

//    if (!RecentError.isEmpty())
//    {
//        foreach (QString error_msg, RecentError)
//            qDebug() << error_msg;
//    }

//}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
