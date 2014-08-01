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
#include "mediationevaluation.h"
#include "User.h"

//--Note:   I don't know how to create a scenario where a database can
//          fail to open.  As such, the error mechanism currently isn't
//          tested against that.
/*!
 * \brief The DRCDB class
 */
class DRCDB
{
private:
    QSqlDatabase database;

    QVector<QString> ErrorMessageVec;

    //std::map<QString, QString> UserMap;
    std::vector<User*> UserMap;

    bool DB_ERROR;
    MediatorId _unregAuthUserCall;
    MediatorId _unregValidatSaveMediationCall;
    MediatorId _unregRequestRecentCall;
    MediatorId _unregRequsetPendingCall;
    MediatorId _unregRequsetScheduledCall;
    MediatorId _unregRequsetClosedCall;
    MediatorId _unregRequestClosedFeesDueCall;
    MediatorId _unregQueryMediationCall;
    MediatorId _unregAddNewUserCall;
    MediatorId _unregRemoveUserCall;
    MediatorId _unregUpdateUserCall;
    MediatorId _unregGetAllUserCall;
    MediatorId _unregRequestMonthlyCall;
    MediatorId _unregSaveEvaluationCall;
    MediatorId _unregRequestResWaCall;

public:
    /*!
     * \brief LoadDatabase
     * \param filename
     */
    void LoadDatabase(QString filename = "db.db3");

    //==========================================================================
    //These methods are used only by methods inside this database class.
    //They should be made private when in main project.
    //--------------------------------------------------------------------------
    /*!
     * \brief ExecuteCommand
     * \param command_string
     * \param query_object
     * \return
     */
    bool ExecuteCommand(QString command_string, QSqlQuery &query_object);
    /*!
     * \brief CreateTable
     * \param table_name
     * \param column_data
     * \return
     */
    bool CreateTable(QString table_name, QVector<QString> column_data);

    bool ExtractError(const QSqlError &error_object, QString command_string);

    /*!
     * \brief ExtractError
     * \param error_object
     * \return
     */
    bool ExtractError(const QSqlError &error_object);
    /*!
     * \brief CloseDatabase
     * \return
     */
    bool CloseDatabase();
    /*!
     * \brief DoesTableExist
     * \param table_name
     * \return
     */
    bool DoesTableExist(QString table_name);
    /*!
     * \brief CreatePersonTable
     * \param person_table_name
     * \return
     */
    bool CreatePersonTable(const QString &person_table_name);


    /*!
     * \brief CreateMediationTable
     * \param mediation_table_name
     * \return
     */
    bool CreateMediationTable(const QString& mediation_table_name);
    /*!
     * \brief CreateSessionTable
     * \param session_table_name
     * \return
     */
    bool CreateSessionTable(const QString& session_table_name);
    /*!
     * \brief CreateClientTable
     * \param client_table_name
     * \return
     */
    bool CreateClientTable(const QString& client_table_name);
    /*!
     * \brief CreateNotesTable
     * \param notes_table_name
     * \return
     */
    bool CreateNotesTable(const QString& notes_table_name);
    /*!
     * \brief CreateClientSessionTable
     * \param client_session_table_name
     * \return
     */
    bool CreateClientSessionTable(const QString& client_session_table_name);
    /*!
     * \brief CreateUserTable
     * \param user_table_name
     * \return
     */
    bool CreateUserTable(const QString& user_table_name);
    //==========================================================================

    //==========================================================================
    //These methods are only used for testing purposes.  Comment them out
    //when in the main project.
    //--------------------------------------------------------------------------
    /*!
     * \brief IsDatabaseOpen
     * \return
     */
    bool IsDatabaseOpen();
    /*!
     * \brief WhatDatabaseName
     * \return
     */
    QString WhatDatabaseName();
    /*!
     * \brief DoesColumnExist
     * \param column_name
     * \param table_name
     * \return
     */
    QVector<QString> GetColumnsList(QString table_name);
    /*!
     * \brief WhatOptionsEnabled
     * \return
     */
    QString WhatOptionsEnabled();
    //==========================================================================

    DRCDB();

    ~DRCDB();
    /*!
     * \brief OpenDatabase
     * \param database_name
     * \return
     */
    bool OpenDatabase(QString database_name);
    /*!
     * \brief InsertObject
     * \param db_object
     * \return
     */
    bool InsertObject(DBBaseObject* db_object);
    /*!
     * \brief UpdateObject
     * \param db_object
     * \return
     */
    bool UpdateObject(DBBaseObject* db_object);

    // Method to insert, for example, a session which needs to know the id of what it's linking to, the dispute
    /*!
     * \brief InsertLinkedObject
     * \param linkedID
     * \param db_object
     * \return
     */
    bool InsertLinkedObject(int linkedID, DBBaseObject* db_object);
    /*!
     * \brief InsertClientObject
     * \param dispute_object
     * \param party_object
     * \return
     */
    bool InsertClientObject(MediationProcess* dispute_object, Party* party_object);
    /*!
     * \brief InsertClientSessionData
     * \param data
     * \param sessionId
     * \param clientId
     * \return
     */
    bool InsertClientSessionData(ClientSessionData* data, int sessionId, int clientId);

    QVector<QString> SelectOneFields(QString table_name, QString id_name, int id);
    /*!
     * \brief SelectAllFields
     * \param table_name
     * \return
     */

    //Parameters are temporary until Filter Object finalized.
    /*!
     * \brief SelectPersonField
     * \param column_name
     * \param table_name
     * \param compare_value
     * \param find_value
     * \return
     */
    QVector<QString> SelectPersonField(QString column_name, QString table_name, QString compare_value, QString find_value);
    /*!
     * \brief DidErrorOccur
     * \return
     */
    bool DidErrorOccur();
    /*!
     * \brief GetLastErrors
     * \return
     */
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
    /*!
     * \brief AuthenticateUser
     * \param arg
     */
    void AuthenticateUser(MediatorArg arg);
    /*!
     * \brief AddNewUser
     * \param arg
     */
    void AddNewUser(MediatorArg arg);
    /*!
     * \brief RemoveUser
     * \param arg
     */
    void RemoveUser(MediatorArg arg);
    /*!
     * \brief UpdateUser
     * \param arg
     */
    void UpdateUser(MediatorArg arg);
    /*!
     * \brief GetAllUsers
     * \param arg
     */
    void GetAllUsers(MediatorArg arg);
    /*!
     * \brief InsertMediation
     * \param arg
     */
    void InsertMediation(MediatorArg arg);
    /*!
     * \brief UpdateMediation
     * \param arg
     */
    void UpdateMediation(MediatorArg arg);
    /*!
     * \brief InsertOrUpdateMediation
     * \param arg
     */
    void InsertOrUpdateMediation(MediatorArg arg);
    /*!
     * \brief LoadMediations
     * \param processIds
     * \return
     */
    MediationProcessVector* LoadMediations(QString processIds);
    /*!
     * \brief LoadRecentMediations
     * \param arg
     */
    void LoadRecentMediations(MediatorArg arg);
    /*!
     * \brief LoadPendingMediations
     * \param arg
     */
    void LoadPendingMediations(MediatorArg arg);
    /*!
     * \brief LoadScheduledMediations
     * \param arg
     */
    void LoadScheduledMediations(MediatorArg arg);
    /*!
     * \brief LoadClosedMediations
     * \param arg
     */
    void LoadClosedMediations(MediatorArg arg);

    void LoadClosedMediationsWithoutPayment(MediatorArg arg);

    // Arg must be a Person* (for now at least) for processing to take place.
    /*!
     * \brief QueryMediations
     * \param arg
     */
    void QueryMediations(MediatorArg arg);

    // Arg is a ReportRequest*  !!
    /*!
     * \brief QueryResWaReport
     * \param arg
     */
    void QueryResWaReport(MediatorArg arg);

    // Arg is a ReportRequest*  !!
    /*!
     * \brief QueryMonthlyReport
     * \param arg
     */
    void QueryMonthlyReport(MediatorArg arg);


    // TEST FUNCTIONALITY!!!
    /*!
     * \brief CreateEvaluationTable
     * \param evaluationTableName
     * \return
     */
    bool CreateEvaluationTable(const QString& evaluationTableName);
    /*!
     * \brief InsertEvaluation
     * \param arg
     */
    void InsertEvaluation(MediatorArg arg);

};

#endif // DRCDB_H
