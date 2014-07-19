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
    QString mediation_table_name;
    QString session_table_name;
    QString client_table_name;
    QString notes_table_name;

    QVector<QString> empty_container;


private Q_SLOTS:
    void OpenDatabase();
    void CorrectDatabaseName();
    void ForeignKeysActive();
    void CreateTable();

    void CheckPersonColumn();
    void CheckMediationColumn();
    void CheckSessionColumn();
    void CheckClientColumn();
    void CheckNotesColumn();

    void InsertPersonObject();
    void InsertMediationProcess();

    void CheckErrors();
    void FindFirstName();

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
    mediation_table_name = QString("Mediation_Table");
    session_table_name = QString("Session_Table");
    client_table_name = QString("Client_Table");
    notes_table_name = QString("Notes_Table");
}
//=======================================================




void DRC_DB_TESTS::OpenDatabase()
{
    //Default constructor should've opened the database.
    QCOMPARE(_db.IsDatabaseOpen(), true);
}
void DRC_DB_TESTS::CorrectDatabaseName()
{
    //Just making sure the database is named what it's supposed to.
    QCOMPARE(_db.WhatDatabaseName(), database_name);
}

void DRC_DB_TESTS::ForeignKeysActive()
{
    //Make sure Foreign keys were enabled.
    QCOMPARE(_db.WhatOptionsEnabled(), QString("foreign_keys = ON"));
}

void DRC_DB_TESTS::CreateTable()
{
    //Table should be created by the default constructor.
    QCOMPARE(_db.DoesTableExist(person_table_name), true);
    QCOMPARE(_db.DoesTableExist(mediation_table_name), true);
    QCOMPARE(_db.DoesTableExist(session_table_name), true);
    QCOMPARE(_db.DoesTableExist(client_table_name), true);
    QCOMPARE(_db.DoesTableExist(notes_table_name), true);
}

void DRC_DB_TESTS::CheckPersonColumn()
{
    //Verify all columns that should be inside table are there.
    QCOMPARE(_db.DoesColumnExist(QString("person_id"), person_table_name), true);
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
    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("assistance_phone"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("email_address"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("number_in_house"), person_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("attorney_name"), person_table_name), true);
}

void DRC_DB_TESTS::CheckMediationColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeType"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CreationDate"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("UpdatedDate"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeState"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeCounty"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("DisputeNotes"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("ReferalSource"), mediation_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("TranslatorRequired"), mediation_table_name), true);
}

void DRC_DB_TESTS::CheckSessionColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("Session_id"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("SessionStatus"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Fee1Paid"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Fee2Paid"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("FeeFamilyPaid"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Fee1OtherPaid"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Fee1"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Fee2"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("FeeFamily"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("FeeOther"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("IncomeFee1"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("IncomeFee2"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("IncomeFeeFamily"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("IncomeFeeOther"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Mediator1"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Mediator2"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Observer1"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Observer2"), session_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), session_table_name), true);
}

void DRC_DB_TESTS::CheckClientColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("Client_id"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Person_id"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Children"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Observers"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Attorney"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), client_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Person_id"), client_table_name), true);
}

void DRC_DB_TESTS::CheckNotesColumn()
{
    QCOMPARE(_db.DoesColumnExist(QString("Note_id"), notes_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Process_id"), notes_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("Note"), notes_table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("CreateDate"), notes_table_name), true);
}

void DRC_DB_TESTS::InsertPersonObject()
{
    Person Tim_Schafer(QString("Tim"));

    QCOMPARE(_db.InsertObject(&Tim_Schafer), true);

    Person Bruce_Lee(QString("Bruce"));
    Bruce_Lee.setMiddleName(QString("Chan"));
    Bruce_Lee.setLastName(QString("Lee"));
    Bruce_Lee.setStreet(QString("55555 Huntington Place"));
    Bruce_Lee.setUnit(QString("#6"));
    Bruce_Lee.setCity(QString("New York"));
    Bruce_Lee.setState(QString("Alaska"));
    Bruce_Lee.setZip(QString("55555"));
    Bruce_Lee.setCounty(COUNTY_BENTON);
    Bruce_Lee.setPrimaryPhone(QString("111-111-1111"));
    Bruce_Lee.setSecondaryPhone(QString("222-222-2222"));
    Bruce_Lee.setAssistantPhone("333-333-3333");
    Bruce_Lee.setEmail(QString("EnterTheDragon@BruceLee.com"));
    Bruce_Lee.setNumberInHousehold(8);
    Bruce_Lee.setAttorney(QString("Bird Man"));

    Person Elvis_Presley(QString("Elvis"));
    Elvis_Presley.setMiddleName(QString("Lee"));
    Elvis_Presley.setLastName(QString("Chan"));
    Elvis_Presley.setStreet(QString("4444 Chapelhill Blvd"));
    Elvis_Presley.setUnit(QString("#5"));
    Elvis_Presley.setCity(QString("Austin"));
    Elvis_Presley.setState(QString("Texas"));
    Elvis_Presley.setZip(QString("44444"));
    Elvis_Presley.setCounty(COUNTY_FRANLKIN);
    Elvis_Presley.setPrimaryPhone(QString("222-222-2222"));
    Elvis_Presley.setSecondaryPhone(QString("111-111-1111"));
    Elvis_Presley.setAssistantPhone("444-444-4444");
    Elvis_Presley.setEmail(QString("RushHour@JackieChan.com"));
    Elvis_Presley.setNumberInHousehold(8);
    Elvis_Presley.setAttorney(QString("Pheonix Wright"));

    QCOMPARE(_db.InsertObject(&Bruce_Lee), true);
    QCOMPARE(_db.InsertObject(&Elvis_Presley), true);

}

void DRC_DB_TESTS::InsertMediationProcess()
{
    MediationProcess* object = MediationProcess::SampleData();

    MediatorArg arg;
    arg.SetArg(object);

    _db.InsertMediation(arg);
    //QCOMPARE(_db.InsertMediation(arg), true);
}

//Sloppy Initial Test
void DRC_DB_TESTS::FindFirstName()
{
    QVector<QString> EnterTheDragon = _db.SelectPersonField(QString("first_name"), QString("Person_Table"), QString("="), QString("Bruce"));

    QVERIFY(EnterTheDragon.size() > 0);
    qDebug() << EnterTheDragon.size();
    if (!EnterTheDragon.isEmpty())
    {
        foreach (QString first_name, EnterTheDragon)
            qDebug() << first_name;
    }
}

void DRC_DB_TESTS::CheckErrors()
{
    QVector<QString> RecentError = _db.GetLastErrors();

    if (!RecentError.isEmpty())
    {
        foreach (QString error_msg, RecentError)
            qDebug() << error_msg;
    }

}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
