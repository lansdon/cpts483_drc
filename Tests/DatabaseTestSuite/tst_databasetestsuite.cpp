#include <QString>
#include <QtTest>
#include <QDebug>
#include <QFile>

#include <iostream>
#include "drcdb.h"

//Tests:
//
//Open Database
//1.  Ensure database file is named the name we named it.
//2.  To check database name, database must be opened first.
//3.  Is the database using the driver we needed?
//
//Create Table
//1.  Was the Table successfully created?
//2.  Does the Schema of the table match with what we intended?
//3.

class DatabaseTestSuite : public QObject
{
    Q_OBJECT

public:
    DatabaseTestSuite();

private:
    DRCDB _db;

    QString database_name;
    QString database_driver;

private Q_SLOTS:
    void OpenDatabase();

private slots:
    void cleanupTestCase()
    {
        QCOMPARE(_db.CloseDatabase(), false);
        QCOMPARE(QFile::remove(database_name), true);
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




















QTEST_APPLESS_MAIN(DatabaseTestSuite)

#include "tst_databasetestsuite.moc"
