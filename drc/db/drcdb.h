#ifndef DRCDB_H
#define DRCDB_H
//#include "Mediator.h"

//#include "sqlite3.h"

#include "DBBaseObject.h"
//#include <string>
//#include <vector>
#include <QtSql/QtSql>

class DRCDB
{
private:
    QSqlDatabase database;

    //Made it a vector in the event that multiple errors have occurred.
    //Though it shouldn't happen if we're doing accurate checks.
    QVector<QString> LastErrors;

    bool DB_ERROR;

public:
    //==========================================================================
    //These methods are made public for the sake of easier testing.
    //--------------------------------------------------------------------------
    bool ExecuteCommand(QString command_string, QSqlQuery &query_object);

    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool ExtractError(const QSqlError &error_object);

    bool CloseDatabase();
    //==========================================================================
    DRCDB();

    DRCDB(QString database_name);

    ~DRCDB();

    bool OpenDatabase(QString database_name);

    bool InsertObject(DBBaseObject* db_object);

    bool DuplicateInsert(const QString &duplicate_query);

    QVector<QString> SelectAllFields(QString table_name);

    bool DidErrorOccur();

    QVector<QString> GetLastErrors();

    // Incoming Events
//    void PersistIntakeForm(MediatorArg arg) const;

//    void PersistFruit(MediatorArg arg);

//    void LoadIntake(MediatorArg arg) const;

//    void LoadFruit(MediatorArg arg);

};

#endif // DRCDB_H
