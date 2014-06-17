#include <QString>
#include <QtTest>

#include "drcdb.h"
#include "Person.h"

//Tests:
//
//Open Database
//1.  Ensure database file is named the name we named it.
//2.  To check database name, database must be opened first.
//3.  Is the database using the driver we needed?
//
//Create Table  (In truth, schema is largely pre-determined; but might as well)
//1.  Was the Table successfully created?
//2.  Does the Schema of the table match with what we intended?
//3.  Does the name of the Table already exist?
//3a.   Seems redundant, but it maybe more efficient to find a table name
//      rather than to have the SQL DBMS discover it on compiling the command.
//4.  Is the database even open?
//5.  Was a table name parameter passed?
//6.  Does the column vector parameter have any values?


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
    void InsertObject();
    void CheckErrors();

private slots:
    void cleanupTestCase()
    {
        QCOMPARE(_db.CloseDatabase(), true);

        //For the sake of this Test Suite, we delete database after every run.
        //Comment out if undesirable; IE, looking inside file directly.
        //Be sure to manually delete if you do comment this line out.
        //QCOMPARE(QFile::remove(database_name), true);
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

}

void DRC_DB_TESTS::CheckErrors()
{
    //QVector<QString> RecentError = _db.GetLastErrors();
    //QCOMPARE(RecentError.first(), QString("Something here."));
}

QTEST_APPLESS_MAIN(DRC_DB_TESTS)

#include "tst_drc_db_tests.moc"
