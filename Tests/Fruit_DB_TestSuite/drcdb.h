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

    //Made it a vector in the event that multiple errors have occurred.
    //Though it shouldn't happen if we're doing accurate checks.
    QVector<QString> LastErrors;

    bool DB_ERROR;

    bool ExecuteCommand(QString command_string, QSqlQuery &query_object);

public:
    DRCDB();

    DRCDB(QString database_name);

    bool OpenDatabase(QString database_name);

    bool CloseDatabase();

    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool InsertObject(DBBaseObject* db_object);

    bool DuplicateInsert(const QString &duplicate_query);

    QVector<QString> SelectAllFields(QString table_name);

    bool ExtractError(const QSqlError &error_object);

    bool GetErrorOccurred();

    QVector<QString> GetLastErrors();
};

#endif // DRCDB_H
