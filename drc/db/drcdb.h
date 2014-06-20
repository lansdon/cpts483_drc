#ifndef DRCDB_H
#define DRCDB_H
//#include "Mediator.h"

#include "DBBaseObject.h"
#include <QtSql/QtSql>

//--Note:   I don't know how to create a scenario where a database can
//          fail to open.  As such, the error mechanism currently isn't
//          tested against that.

class DRCDB
{
private:
    QSqlDatabase database;

    QVector<QString> ErrorMessageVec;

    bool DB_ERROR;

public:
    //==========================================================================
    //These methods are used only by methods inside this database class.
    //They should be made private when in main project.
    //--------------------------------------------------------------------------
    bool ExecuteCommand(QString command_string, QSqlQuery &query_object);

    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool ExtractError(const QSqlError &error_object);

    bool CloseDatabase();

    bool DoesTableExist(QString table_name);

    bool CreatePersonTable(const QString &person_table_name);
    //==========================================================================

    //==========================================================================
    //These methods are only used for testing purposes.  Comment them out
    //when in the main project.
    //--------------------------------------------------------------------------
    bool IsDatabaseOpen();

    QString WhatDatabaseName();

    bool DoesColumnExist(QString column_name, QString table_name);    

    QString WhatOptionsEnabled();
    //==========================================================================

    DRCDB();

    ~DRCDB();

    bool OpenDatabase(QString database_name);

    bool InsertObject(DBBaseObject* db_object);

    QVector<QString> SelectAllFields(QString table_name);

    bool DidErrorOccur();

    QVector<QString> GetLastErrors();

//  Incoming Events
//  void PersistIntakeForm(MediatorArg arg) const;

//  void PersistFruit(MediatorArg arg);

//  void LoadIntake(MediatorArg arg) const;

//  void LoadFruit(MediatorArg arg);

//  DRCDB(QString database_name);

//********************************Deprecated Methods********************************
//  bool DuplicateInsert(const QString &duplicate_query);
//  bool IsDatabaseEmpty();
//********************************Deprecated Methods********************************

};

#endif // DRCDB_H
