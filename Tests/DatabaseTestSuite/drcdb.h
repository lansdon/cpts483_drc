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

    QString GetDatabaseName();

    bool OpenDatabase(QString database_name);

    QString WhatDriver();

    bool CloseDatabase();

    bool CheckTableExists(QString table_name);

    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool InsertObject(DBBaseObject* db_object);

    void WhatLastError(const QSqlQuery &query_object);
};

#endif // DRCDB_H
