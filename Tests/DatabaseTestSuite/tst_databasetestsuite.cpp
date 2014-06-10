#include <QString>
#include <QtTest>
#include <QDebug>
#include <QFile>
#include <QVector>

#include <iostream>
#include "drcdb.h"

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

class DatabaseTestSuite : public QObject
{
    Q_OBJECT

public:
    DatabaseTestSuite();

private:
    DRCDB _db;

    QString database_name;
    QString database_driver;
    QString table_name;
    QVector<QString> column_container;
    QVector<QString> empty_container;


private Q_SLOTS:
    void OpenDatabase();
    void CreateTable();
    void CreateDuplicateTable();

private slots:
    void cleanupTestCase()
    {
        QCOMPARE(_db.CloseDatabase(), false);

        //For the sake of this Test Suite, we delete database after every run.
        //Comment out if undesirable; IE, looking inside file directly.
        //QCOMPARE(QFile::remove(database_name), true);
    }
};

//  Change information to accomodate new circumstances.
//======================================================
DatabaseTestSuite::DatabaseTestSuite()
{
    //Name of the database we're using / creating.
    database_name = QString("database_test_name.db");

    //Name of the driver we're using.
    database_driver = QString("QSQLITE");

    //Name of the table we're creating.
    table_name = QString("Safeway");

    //Name and Datatypes of all Table columns
    column_container.push_back(QString("fruit_name char(50)"));

}
//=======================================================

void DatabaseTestSuite::OpenDatabase()
{
    //Did the database open?
    QCOMPARE(_db.OpenDatabase(database_name), true);

    //Does the name of the database match the name we used to open it.
    QCOMPARE(_db.GetDatabaseName(), database_name);

    //Is the driver used SQLITE3?
    QCOMPARE(_db.WhatDriver(), database_driver);
}

void DatabaseTestSuite::CreateTable()
{
    //Does table shouldn't already exist.
    QCOMPARE(_db.CheckTableExists(table_name), false);

    //Create table with name and column data.
    QCOMPARE(_db.CreateTable(table_name, column_container), true);

    //Error should be an empty string.
    QCOMPARE(_db.WhatLastError(), QString(""));
}

void DatabaseTestSuite::CreateDuplicateTable()
{
    //Table already exists.
    QCOMPARE(_db.CheckTableExists(table_name), true);

    //Create table with same name.  (Should fail)
    QCOMPARE(_db.CreateTable(table_name, empty_container), false);

}

    //So far, can't figure out how to trigger the last error method.
    //QCOMPARE(_db.WhatLastError(), QString("Should be an error here."));


















QTEST_APPLESS_MAIN(DatabaseTestSuite)

#include "tst_databasetestsuite.moc"
