#include <QString>
#include <QtTest>

#include <iostream>
#include "drcdb.h"

class DatabaseTestSuite : public QObject
{
    Q_OBJECT

public:
    DatabaseTestSuite();

private:
    DRCDB _db;

private Q_SLOTS:
    void OpenDatabase();
    void CheckDriver();
    void initTestCase();
};

DatabaseTestSuite::DatabaseTestSuite()
{
    _db.OpenDatabase("");
}

void DatabaseTestSuite::initTestCase()
{
    QCOMPARE(_db.WhatDriver(), QString("QSQLITE"));
    QCOMPARE(_db.WhatDatabase(), QString("Albertsons"));
}

void DatabaseTestSuite::CheckDriver()
{
}


void DatabaseTestSuite::OpenDatabase()
{

}

QTEST_APPLESS_MAIN(DatabaseTestSuite)

#include "tst_databasetestsuite.moc"
