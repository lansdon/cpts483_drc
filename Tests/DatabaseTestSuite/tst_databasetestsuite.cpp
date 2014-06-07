#include <QString>
#include <QtTest>

#include <iostream>
#include "drcdb.h"

class DatabaseTestSuite : public QObject
{
    Q_OBJECT

public:
    DatabaseTestSuite();

private Q_SLOTS:
    void OpenDatabase();
    void CheckDriver();

};

DatabaseTestSuite::DatabaseTestSuite()
{

}


void DatabaseTestSuite::OpenDatabase()
{
    DRCDB _db;
    _db.OpenDatabase("Albert");
    QCOMPARE(_db.WhatDatabase(), QString("Albertsons"));
    QCOMPARE(_db.isOpen(), true);
    _db.CloseDatabase();
    QSqlDatabase::removeDatabase("QSQLITE");
}

void DatabaseTestSuite::CheckDriver()
{
      DRCDB _db;
    _db.OpenDatabase("Albertsons");
//    QCOMPARE(_db.WhatDriver(), QString("QSQLITE"));
//    _db.CloseDatabase();
//    QSqlDatabase::removeDatabase("QSQLITE");
}

QTEST_APPLESS_MAIN(DatabaseTestSuite)

#include "tst_databasetestsuite.moc"
