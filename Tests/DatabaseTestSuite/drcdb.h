#ifndef DRCDB_H
#define DRCDB_H

#include <QString>
#include <QVector>
#include <QtSql/QtSql>
#include "DBBaseObject.h"

class DRCDB
{
private:
    QSqlDatabase database;

public:
    DRCDB();

    DRCDB(QString database_name);

    bool OpenDatabase(QString database_name);

    bool CloseDatabase();

    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool InsertObject(DBBaseObject* db_object);

    QVector<QString> SelectAllFields(QString table_name);

    void WhatLastError(const QSqlQuery &query_object);

    //  Methods that aren't necessary, but are helpful for testing.
    //======================================================================
private:
    bool ExecuteCommand(QString command_string);

    void DebugDisplay(QString error_message, bool active = false);

public:
    QString GetDatabaseName();

    QString WhatDriver();

    //bool CheckTableExists(QString table_name);
};

#endif // DRCDB_H
