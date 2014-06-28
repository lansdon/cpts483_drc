#ifndef DRCDB_H
#define DRCDB_H
//#include "Mediator.h"

#include "DBBaseObject.h"
#include "Crypto/SHA256_Crypto.h"
#include <string>
#include <vector>
#include <map>
#include <QtSql/QtSql>
#include "DRCModels.h"
#include "MediatorArg.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include "User.h"

//--Note:   I don't know how to create a scenario where a database can
//          fail to open.  As such, the error mechanism currently isn't
//          tested against that.

class DRCDB
{
private:
    QSqlDatabase database;

    QVector<QString> ErrorMessageVec;

    std::map<QString, QString> UserMap;

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

    bool CreateMediationTable(const QString& mediation_table_name);

    bool CreateSessionTable(const QString& session_table_name);

    bool CreateClientTable(const QString& client_table_name);

    bool CreateNotesTable(const QString& notes_table_name);
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

    // Method to insert, for example, a session which needs to know the id of what it's linking to, the dispute
    bool InsertLinkedObject(int linkedID, DBBaseObject* db_object);

    // Possible method. not correctly implemented yet
    bool InsertJoinObject(DBBaseObject* db_object1, DBBaseObject* db_object2);

    bool InsertJoinObject(MediationProcess* dispute_object, Party* party_object);

    QVector<QString> SelectAllFields(QString table_name);

    //Parameters are temporary until Filter Object finalized.
    QVector<QString> SelectPersonField(QString column_name, QString table_name, QString compare_value, QString find_value);

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

    void AuthenticateUser(MediatorArg arg);

    void InsertMediation(MediatorArg arg);

    void LoadRecentMediations(MediatorArg arg);

    void LoadRecentMediations(void);
};

#endif // DRCDB_H
