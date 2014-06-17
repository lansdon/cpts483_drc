#include <QString>
#include <QtTest>

#include "drcdb.h"
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


class DRC_DB_TESTS : public QObject
{
    Q_OBJECT

public:
    DRC_DB_TESTS();

private:
    DRCDB _db;

    QString database_name;
//    QString database_driver;
    QString table_name;
//    QVector<QString> column_container;
    QVector<QString> empty_container;


private Q_SLOTS:
    void OpenDatabase();
    void CreateTable();
    void CheckColumn();
    void InsertObject();
    void CheckErrors();

private slots:
    void cleanupTestCase()
    {
        QCOMPARE(_db.CloseDatabase(), true);

        //*******For the sake of this Test Suite, we delete database after every run.*******
        //*******Comment out if undesirable; IE, looking inside file directly.       *******
        //*******Be sure to manually delete if you do comment this line out.         *******

        QCOMPARE(QFile::remove(database_name), true);
    }
};

//  Change information to accomodate new circumstances.
//======================================================
DRC_DB_TESTS::DRC_DB_TESTS()
{
    database_name = QString("drc_db.db3");
    table_name = "Person_Table";
}
//=======================================================

void DRC_DB_TESTS::OpenDatabase()
{
    //Default constructor should've opened the database.
    QCOMPARE(_db.IsDatabaseOpen(), true);

    //Just making sure the database is named what it's supposed to.
    QCOMPARE(_db.WhatDatabaseName(), database_name);

}

void DRC_DB_TESTS::CreateTable()
{
    //Database should start out empty.
    QCOMPARE(_db.IsDatabaseEmpty(), false);

    //Table should already be created in the default constructor.
    QCOMPARE(_db.DoesTableExist(table_name), true);

}


void DRC_DB_TESTS::CheckColumn()
{
    //Verify all columns that should be inside table are there.
    QCOMPARE(_db.DoesColumnExist(QString("person_id"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("first_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("middle_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("last_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("street_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("unit_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("city_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("state_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("zip_code"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("county_name"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("primary_phone"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("secondary_phone"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("assistance_phone"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("email_address"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("number_in_house"), table_name), true);
    QCOMPARE(_db.DoesColumnExist(QString("attorney_name"), table_name), true);
}

void DRC_DB_TESTS::InsertObject()
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
    Bruce_Lee.setCounty(QString("Benton"));
    Bruce_Lee.setPrimaryPhone(QString("111-111-1111"));
    Bruce_Lee.setSecondaryPhone(QString("222-222-2222"));
    Bruce_Lee.setAssistantPhone("333-333-3333");
    Bruce_Lee.setEmail(QString("EnterTheDragon@BruceLee.com"));
    Bruce_Lee.setNumberInHousehold(8);
    Bruce_Lee.setAttorney(QString("Bird Man"));

    QCOMPARE(_db.InsertObject(&Bruce_Lee), true);

}

void DRC_DB_TESTS::CheckErrors()
{
    QVector<QString> RecentError = _db.GetLastErrors();
    if (!RecentError.isEmpty())
        qDebug() << RecentError.first();
}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
