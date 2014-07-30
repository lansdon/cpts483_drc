#include "drcdb.h"
#include "drctypes.h"
#include <QtSql/QtSql>
#include "reswareport.h"
#include "reportrequest.h"
#include "monthlyreport.h"

#define db_driver "QSQLITE"

//========================================================================
//------------------------------------------------------------------------
DRCDB::DRCDB() : DB_ERROR(false)
{
    // Register to Listen for events.
    Mediator::Register(MKEY_GUI_AUTHENTICATE_USER, [this](MediatorArg arg){AuthenticateUser(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){InsertOrUpdateMediation(arg);});
    Mediator::Register(MKEY_BL_REQUEST_RECENT_MEDIATIONS_DONE, [this](MediatorArg arg){LoadRecentMediations(arg);});
    Mediator::Register(MKEY_BL_REQUEST_PENDING_MEDIATIONS_DONE, [this](MediatorArg arg){LoadPendingMediations(arg);});
    Mediator::Register(MKEY_BL_REQUEST_SCHEDULED_MEDIATIONS_DONE, [this](MediatorArg arg){LoadScheduledMediations(arg);});
    Mediator::Register(MKEY_BL_REQUEST_CLOSED_MEDIATIONS_DONE, [this](MediatorArg arg){LoadClosedMediations(arg);});
    Mediator::Register(MKEY_BL_QUERY_MEDIATION, [this](MediatorArg arg){QueryMediations(arg);});
    Mediator::Register(MKEY_DB_ADD_NEW_USER, [this](MediatorArg arg){AddNewUser(arg);});
    Mediator::Register(MKEY_DB_REMOVE_USER, [this](MediatorArg arg){RemoveUser(arg);});
    Mediator::Register(MKEY_DB_UPDATE_USER, [this](MediatorArg arg){UpdateUser(arg);});
    Mediator::Register(MKEY_DB_GET_ALL_USER, [this](MediatorArg arg) {GetAllUsers(arg);});
    Mediator::Register(MKEY_GUI_SAVE_EVALUATION, [this](MediatorArg arg) {InsertEvaluation(arg);});
    Mediator::Register(MKEY_BL_REQUEST_RESWA_REPORT, [this](MediatorArg arg) {QueryResWaReport(arg);});
    Mediator::Register(MKEY_BL_REQUEST_MONTHLY_REPORT, [this](MediatorArg arg) {QueryMonthlyReport(arg);});

}
//========================================================================

bool DRCDB::CreateEvaluationTable(const QString& evaluationTableName)
{
    QVector<QString> evaluationTableColumns;
    evaluationTableColumns.push_back(QString("Id integer primary key autoincrement null"));
    evaluationTableColumns.push_back(QString("startDate Date"));
    evaluationTableColumns.push_back(QString("endDate Date"));
    evaluationTableColumns.push_back(QString("CountyId int"));
    evaluationTableColumns.push_back(QString("FairYes int"));
    evaluationTableColumns.push_back(QString("FairNo int"));
    evaluationTableColumns.push_back(QString("FairSomewhat int"));
    evaluationTableColumns.push_back(QString("ImproveYes int"));
    evaluationTableColumns.push_back(QString("ImproveNo int"));
    evaluationTableColumns.push_back(QString("ImproveSomewhat int"));
    evaluationTableColumns.push_back(QString("CommunicateYes int"));
    evaluationTableColumns.push_back(QString("CommunicateNo int"));
    evaluationTableColumns.push_back(QString("CommunicateSomewhat int"));
    evaluationTableColumns.push_back(QString("UnderstandYes int"));
    evaluationTableColumns.push_back(QString("UnderstandNo int"));
    evaluationTableColumns.push_back(QString("UnderstandSomewhat int"));
    evaluationTableColumns.push_back(QString("RecommendYes int"));
    evaluationTableColumns.push_back(QString("RecommendNo int"));
    evaluationTableColumns.push_back(QString("RecommendSomewhat int"));
    evaluationTableColumns.push_back(QString("AgreementYes int"));
    evaluationTableColumns.push_back(QString("AgreementNo int"));
    evaluationTableColumns.push_back(QString("AgreementSomewhat int"));

    return CreateTable(evaluationTableName, evaluationTableColumns);
}

void DRCDB::InsertEvaluation(MediatorArg arg)
{
    MediationEvaluation* eval = nullptr;
    if(arg.IsSuccessful())
    {
        arg.SetSuccessful(false);

        eval = arg.getArg<MediationEvaluation*>();
        if(eval)
        {
            QSqlQuery EvalQuery(database);
            QString EvalCommandString = QString("Select * from Evaluation_table where startDate < '%1' and endDate > '%1' and CountyId = %2")
                                                .arg(eval->getMediationDate().toString("yyyy-MM-dd"))
                                                .arg(QString::number(eval->getCountyOfMediation()));
            this->ExecuteCommand(EvalCommandString, EvalQuery);
            if(!EvalQuery.next())
            {
                QSqlQuery insert(database);
                int month = eval->getMediationDate().toString("MM").toInt();
                QString start;
                QString end;
                if(month < 7)
                {
                    start = eval->getMediationDate().toString("yyyy-")+"01-01";
                    end = eval->getMediationDate().toString("yyyy-")+"06-30";
                }
                else
                {
                    start = eval->getMediationDate().toString("yyyy-")+"07-01";
                    end = eval->getMediationDate().toString("yyyy-")+"12-31";
                }
                QString Command = QString("insert into Evaluation_Table values (%1, '%2', '%3', %4)")
                                        .arg("null")
                        .arg(start)
                        .arg(end)
                        .arg(eval->Parse());
                if(!this->ExecuteCommand(Command, insert))
                {
                    qDebug()<<Command;
                    qDebug()<<this->GetLastErrors().first();
                }

                arg.SetSuccessful(true);
            }
            else
            {
                int id = EvalQuery.value(0).toInt();

                QString values = "";
                int stored = 0;
                if(eval->getQ3() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(4).toInt();
                    stored++;
                    values += QString("FairYes = %1, ").arg(stored);
                }
                else if(eval->getQ3() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(5).toInt();
                    stored++;
                    values += QString("FairNo = %1, ").arg(stored);
                }
                else if(eval->getQ3() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(6).toInt();
                    stored++;
                    values += QString("FairSomewhat = %1, ").arg(stored);
                }
                if(eval->getQ4() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(7).toInt();
                    stored++;
                    values += QString("ImproveYes = %1, ").arg(stored);
                }
                else if(eval->getQ4() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(8).toInt();
                    stored++;
                    values += QString("ImproveNo = %1, ").arg(stored);
                }
                else if(eval->getQ4() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(9).toInt();
                    stored++;
                    values += QString("ImproveSomewhat = %1, ").arg(stored);
                }
                if(eval->getQ5() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(10).toInt();
                    stored++;
                    values += QString("CommunicateYes = %1, ").arg(stored);
                }
                else if(eval->getQ5() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(11).toInt();
                    stored++;
                    values += QString("CommunicateNo = %1, ").arg(stored);
                }
                else if(eval->getQ5() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(12).toInt();
                    stored++;
                    values += QString("CommunicateSomewhat = %1, ").arg(stored);
                }
                if(eval->getQ6() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(13).toInt();
                    stored++;
                    values += QString("UnderstandYes = %1, ").arg(stored);
                }
                else if(eval->getQ6() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(14).toInt();
                    stored++;
                    values += QString("UnderstandNo = %1, ").arg(stored);
                }
                else if(eval->getQ6() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(15).toInt();
                    stored++;
                    values += QString("UnderstandSomewhat = %1, ").arg(stored);
                }
                if(eval->getQ7() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(16).toInt();
                    stored++;
                    values += QString("RecommendYes = %1, ").arg(stored);
                }
                else if(eval->getQ7() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(17).toInt();
                    stored++;
                    values += QString("RecommendNo = %1, ").arg(stored);
                }
                else if(eval->getQ7() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(18).toInt();
                    stored++;
                    values += QString("RecommendSomewhat = %1, ").arg(stored);
                }
                if(eval->getQ8() == EVALUATION_ANSWERS_YES)
                {
                    stored = EvalQuery.value(19).toInt();
                    stored++;
                    values += QString("AgreementYes = %1 ").arg(stored);
                }
                else if(eval->getQ8() == EVALUATION_ANSWERS_NO)
                {
                    stored = EvalQuery.value(20).toInt();
                    stored++;
                    values += QString("AgreementNo = %1 ").arg(stored);
                }
                else if(eval->getQ8() == EVALUATION_ANSWERS_SOMEWHAT)
                {
                    stored = EvalQuery.value(21).toInt();
                    stored++;
                    values += QString("AgreementSomewhat = %1 ").arg(stored);
                }


                QSqlQuery update(database);
                QString updatecommand = QString("update %1 set %2 where %3 = '%4'")
                                            .arg(eval->table())
                                            .arg(values)
                                            .arg(eval->GetIdRowName())
                                            .arg(id);
                this->ExecuteCommand(updatecommand, update);
            }
        }
    }
}

//========================================================================
//------------------------------------------------------------------------
bool DRCDB::CreatePersonTable(const QString& person_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> person_table_columns;
    person_table_columns.push_back(QString("Person_id integer primary key autoincrement null"));
    person_table_columns.push_back(QString("first_name char(50)"));
    person_table_columns.push_back(QString("middle_name char(50)"));
    person_table_columns.push_back(QString("last_name char(50) not null"));
    person_table_columns.push_back(QString("street_name char(50)"));
    person_table_columns.push_back(QString("unit_name char(50)"));
    person_table_columns.push_back(QString("city_name char(50)"));
    person_table_columns.push_back(QString("state_name char(50)"));
    person_table_columns.push_back(QString("zip_code char(50)"));
    person_table_columns.push_back(QString("county_name int"));
    person_table_columns.push_back(QString("primary_phone char(50)"));
    person_table_columns.push_back(QString("primary_phone_ext char(50)"));
    person_table_columns.push_back(QString("secondary_phone char(50)"));
    person_table_columns.push_back(QString("secondary_phone_ext char(50)"));
    person_table_columns.push_back(QString("email_address char(50)"));

    return CreateTable(person_table_name, person_table_columns);
}

bool DRCDB::CreateUserTable(const QString& user_table_name)
{
    QVector<QString> user_table_columns;
    user_table_columns.push_back(QString("user_id integer primary key autoincrement null"));
    user_table_columns.push_back(QString("userName char(50)"));
    user_table_columns.push_back(QString("password char(256)"));
    user_table_columns.push_back(QString("Admin bool"));

    return CreateTable(user_table_name, user_table_columns);
}

//========================================================================


void DRCDB::LoadDatabase(QString filename)
{
    OpenDatabase(filename);

    //Name of the table we're creating.
    QString person_table_name = QString("Person_Table");
    QString mediation_table_name = QString("Mediation_Table");
    QString session_table_name = QString("Session_Table");
    QString client_table_name = QString("Client_Table");
    QString notes_table_name = QString("Notes_Table");
    QString client_session_table_name = QString("Client_session_table");
    QString user_table_name = QString("User_Table");
    QString evaluationTableName = QString("Evaluation_Table");

    if (!this->DoesTableExist(person_table_name))
    {
        CreatePersonTable(person_table_name);
    }

    if (!this->DoesTableExist(mediation_table_name))
    {
        CreateMediationTable(mediation_table_name);
    }

    if (!this->DoesTableExist(session_table_name))
    {
        CreateSessionTable(session_table_name);
    }

    if (!this->DoesTableExist(client_table_name))
    {
        CreateClientTable(client_table_name);
    }

    if(!this->DoesTableExist(notes_table_name))
    {
        CreateNotesTable(notes_table_name);
    }

    if (!this->DoesTableExist(client_session_table_name))
    {
         CreateClientSessionTable(client_session_table_name);
    }

    if (!this->DoesTableExist(evaluationTableName))
    {
        CreateEvaluationTable(evaluationTableName);
    }

    if(!this->DoesTableExist(user_table_name))
    {
        CreateUserTable(user_table_name);
    }

    // To make sure there is always Admin/admin for access to application
    MediatorArg arg;
    User* adminUser = new User("Admin", "admin", USER_T_ADMIN);
    arg.SetArg(adminUser);
    AddNewUser(arg);
}

bool DRCDB::CreateMediationTable(const QString& mediation_table_name)
{
    QVector<QString> mediation_table_columns;
    mediation_table_columns.push_back(QString("Process_id integer primary key autoincrement null"));
    mediation_table_columns.push_back(QString("DisputeType integer"));
    mediation_table_columns.push_back(QString("CreationDate Date"));
    mediation_table_columns.push_back(QString("UpdatedDate Date"));
    mediation_table_columns.push_back(QString("CreationDateTime DateTime"));
    mediation_table_columns.push_back(QString("UpdatedDateTime DateTime"));
    mediation_table_columns.push_back(QString("DisputeState integer"));
    mediation_table_columns.push_back(QString("DisputeInternalState integer"));
    mediation_table_columns.push_back(QString("DisputeCounty integer"));
    mediation_table_columns.push_back(QString("ReferalSource integer"));
    mediation_table_columns.push_back(QString("InquiryType integer"));
    mediation_table_columns.push_back(QString("InfoOnly Bool"));
    mediation_table_columns.push_back(QString("IsCourtCase Bool"));
    mediation_table_columns.push_back(QString("CourtDate Date"));
    mediation_table_columns.push_back(QString("CourtCaseType integer"));
    mediation_table_columns.push_back(QString("CourtOrderType char(128)"));
    mediation_table_columns.push_back(QString("TranslatorRequired Bool"));
    mediation_table_columns.push_back(QString("SessionType integer"));
    mediation_table_columns.push_back(QString("MediationClause Bool"));

    return CreateTable(mediation_table_name, mediation_table_columns);
}

bool DRCDB::CreateClientSessionTable(const QString& client_session_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> client_session_table_columns;
    client_session_table_columns.push_back(QString("Data_id integer primary key autoincrement null"));
    client_session_table_columns.push_back(QString("Client_id integer"));
    client_session_table_columns.push_back(QString("Session_id integer"));
    client_session_table_columns.push_back(QString("income integer"));
    client_session_table_columns.push_back(QString("feesCharged integer"));
    client_session_table_columns.push_back(QString("feesPaid Bool"));
    client_session_table_columns.push_back(QString("AttorneyExpected Bool"));
    client_session_table_columns.push_back(QString("AttorneyAttended Bool"));
    client_session_table_columns.push_back(QString("Support integer"));
    client_session_table_columns.push_back(QString("ClientPhone Bool"));
    client_session_table_columns.push_back(QString("AtTable Bool"));
    client_session_table_columns.push_back(QString("foreign key(Session_id) references Session_Table(Session_id)"));

    return CreateTable(client_session_table_name, client_session_table_columns);
}

bool DRCDB::CreateClientTable(const QString& client_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> client_table_columns;
    client_table_columns.push_back(QString("Client_id integer primary key autoincrement null"));
    client_table_columns.push_back(QString("Process_id integer"));
    client_table_columns.push_back(QString("Person_id integer"));
    client_table_columns.push_back(QString("Children integer"));
    client_table_columns.push_back(QString("Adult integer"));
    client_table_columns.push_back(QString("AttorneyName char(128)"));
    client_table_columns.push_back(QString("AttorneyPhone char(128)"));
    client_table_columns.push_back(QString("AttorneyEmail char(128)"));
    client_table_columns.push_back(QString("AssistantName char(128)"));
    client_table_columns.push_back(QString("AssistantPhone char(128)"));
    client_table_columns.push_back(QString("AssistantEmail char(128)"));
    client_table_columns.push_back(QString("foreign key(Process_id) references Mediation_Table(Process_id)"));
    client_table_columns.push_back(QString("foreign key(Person_id) references person_Table(person_id)"));

    return CreateTable(client_table_name, client_table_columns);
}

bool DRCDB::CreateSessionTable(const QString& session_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> session_table_columns;
    session_table_columns.push_back(QString("Session_id integer primary key autoincrement null"));
    session_table_columns.push_back(QString("Process_id integer"));
    session_table_columns.push_back(QString("SessionStatus integer"));
    session_table_columns.push_back(QString("SessionOutcome integer"));
    session_table_columns.push_back(QString("CreatedDateTime DateTime"));
    session_table_columns.push_back(QString("UpdatedDateTime DateTime"));
    session_table_columns.push_back(QString("ScheduledTime DateTime"));
    session_table_columns.push_back(QString("Mediator1 char(128)"));
    session_table_columns.push_back(QString("Mediator2 char(128)"));
    session_table_columns.push_back(QString("Observer1 char(128)"));
    session_table_columns.push_back(QString("Observer2 char(128)"));
    session_table_columns.push_back(QString("Shuttle bool"));
    session_table_columns.push_back(QString("foreign key(Process_id) references Mediation_Table(id)"));

    return CreateTable(session_table_name, session_table_columns);
}

bool DRCDB::CreateNotesTable(const QString& Notes_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> notes_table_columns;
    notes_table_columns.push_back(QString("Note_id integer primary key autoincrement null"));
    notes_table_columns.push_back(QString("Process_id integer"));
    notes_table_columns.push_back(QString("Session_id integer"));
    notes_table_columns.push_back(QString("Note char(128)"));
    notes_table_columns.push_back(QString("CreateDate Date"));

    return CreateTable(Notes_table_name, notes_table_columns);
}

//========================================================================
//Gets the database object to return a list of all the tables currently
//residing in the database.  A table_name is passed to the .contain method
//to verify whether or not a table matching the string exists.

//--Note:   Qt::CaseSensitive is on by default, but made explicit for readability.
//          Use Qt::CaseInsensitive if desired.
//------------------------------------------------------------------------
bool DRCDB::DoesTableExist(QString table_name)
{
    QStringList database_tables = database.tables();
    return database_tables.contains(table_name, Qt::CaseSensitive);
}

//========================================================================

//========================================================================
//Method closes our database object, and returns the boolean indicating
//whether or not the database was successfully closed.
//True:     Closed
//False:    Still Open
//------------------------------------------------------------------------
bool DRCDB::CloseDatabase()
{
    QString connection_name = database.connectionName();
    database.close();

    //Resets to default connection
    database = QSqlDatabase();
    database.removeDatabase(connection_name);
    return !database.isOpen();

    // database.close();
    // return !database.isOpen();
}
//========================================================================

//========================================================================
//------------------------------------------------------------------------
DRCDB::~DRCDB()
{
    this->CloseDatabase();
}
//========================================================================

//========================================================================
                    // REPORTS !!!!
//========================================================================

// Arg is a ReportRequest*  !!
void DRCDB::QueryResWaReport(MediatorArg arg)
{
    ResWaReport* report = nullptr;
    ReportRequest* params = nullptr;
    if(arg.IsSuccessful() && (params = arg.getArg<ReportRequest*>()))
    {
        bool firstHalfOfYear = params->IsForFirstHalfOfYear();
        int year = params->GetYear();

        QDateTime start;
        QDateTime end;
        if(firstHalfOfYear)
        {
            start = QDateTime::fromString(QString("%1-01-01").arg(year),"yyyy-MM-dd");
            end = QDateTime::fromString(QString("%1-06-30").arg(year),"yyyy-MM-dd");
        }
        else
        {
            start = QDateTime::fromString(QString("%1-07-01").arg(year),"yyyy-MM-dd");
            end = QDateTime::fromString(QString("%1-12-31").arg(year),"yyyy-MM-dd");
        }

        QSqlQuery query(database);
        QString command = QString("Select * from Session_table where ScheduledTime <= '%1' and ScheduledTime >= '%2'")
                            .arg(end.toString("yyyy-MM-dd"))
                            .arg(start.toString("yyyy-MM-dd"));
        this->ExecuteCommand(command, query);

        QString mediationIdMatches = "";
        bool first = true;
        while(query.next())
        {
            if(!first)
            {
                mediationIdMatches += ", ";
            }
            mediationIdMatches += query.value(1).toString();
            first = false;
        }
        MediationProcessVector* init = LoadMediations(mediationIdMatches);

        first = true;
        mediationIdMatches = "";
        for(size_t i = 0; i < init->size(); i++)
        {
            MediationProcess* process = init->at(i);
            if(process->GetCountyId() == params->GetCounty())
            {
                if(!first)
                {
                    mediationIdMatches += ", ";
                }
                mediationIdMatches += QString::number(process->GetId());
                first = false;
            }
        }

        // Must Init the ResWaReport with MPVector (all mps in the 6 month span)
        MediationProcessVector* mpVec = LoadMediations(mediationIdMatches);
        report = new ResWaReport(mpVec);

        // For section 2 data
        QString commanda = QString("Select * from Mediation_Table where UpdatedDate <= '%1' and UpdatedDate >= '%2' and DisputeCounty = %3")
                        .arg(end.toString("yyyy-MM-dd"))
                        .arg(start.toString("yyyy-MM-dd"))
                        .arg(QString::number(params->GetCounty()));
        this->ExecuteCommand(commanda, query);

        mediationIdMatches = "";
        first = true;
        while(query.next())
        {
            if(!first)
            {
                mediationIdMatches += ", ";
            }
            mediationIdMatches += query.value(1).toString();
            first = false;
        }
        MediationProcessVector* temp = LoadMediations(mediationIdMatches);
        int callCount = 0;
        for(size_t i = 0; i < temp->size(); i++)
        {
            MediationProcess* proc = temp->at(i);
            if(((proc->GetState() == PROCESS_STATE_CLOSED_WITH_SESSION) && (proc->getMediationSessionVector()->size() == 0)) ||
                 (proc->GetState() == PROCESS_STATE_CLOSED_NO_SESSION))
            {
                callCount++;
            }
        }
        report->SetTotalCalls(callCount);

        // For section 8 data
        QSqlQuery evalQuery(database);
        QString evalCommand = QString("Select * from Evaluation_Table where startdate = '%1' and CountyId = %2")
                                .arg(start.toString("yyyy-MM-dd"))
                                .arg(QString::number(params->GetCounty()));

        this->ExecuteCommand(evalCommand,evalQuery);

        while(evalQuery.next())
        {
            // populate the evaluation totals
            report->SetQ1Yes(evalQuery.value(4).toInt());
            report->SetQ1No(evalQuery.value(5).toInt());
            report->SetQ1Somewhat(evalQuery.value(6).toInt());

            report->SetQ2Yes(evalQuery.value(7).toInt());
            report->SetQ2No(evalQuery.value(8).toInt());
            report->SetQ2Somewhat(evalQuery.value(9).toInt());

            report->SetQ3Yes(evalQuery.value(10).toInt());
            report->SetQ3No(evalQuery.value(11).toInt());
            report->SetQ3Somewhat(evalQuery.value(12).toInt());

            report->SetQ4Yes(evalQuery.value(13).toInt());
            report->SetQ4No(evalQuery.value(14).toInt());
            report->SetQ4Somewhat(evalQuery.value(15).toInt());

            report->SetQ5Yes(evalQuery.value(16).toInt());
            report->SetQ5No(evalQuery.value(17).toInt());
            report->SetQ5Somewhat(evalQuery.value(18).toInt());

            report->SetQ6Yes(evalQuery.value(19).toInt());
            report->SetQ6No(evalQuery.value(20).toInt());
            report->SetQ6Somewhat(evalQuery.value(21).toInt());
        }
    }
    Mediator::Call(MKEY_DB_REQUEST_RESWA_REPORT_DONE,  report);
}

// Arg is a ReportRequest*  !!
void DRCDB::QueryMonthlyReport(MediatorArg arg)
{
    ReportRequest* params = nullptr;
    if(arg.IsSuccessful() && (params = arg.getArg<ReportRequest*>()))
    {
        int month = params->GetMonth();
        int year = params->GetYear();
        CountyIds county = params->GetCounty();

        QDateTime start;
        QDateTime end;
        if(month != 12)
        {
            start = QDateTime::fromString(QString("%1-%2-01").arg(year).arg(month),"yyyy-MM-dd");
            end = QDateTime::fromString(QString("%1-%2-01").arg(year).arg(month+1),"yyyy-MM-dd");
        }
        else
        {

            start = QDateTime::fromString(QString("%1-%2-01").arg(year).arg(month),"yyyy-MM-dd");
            year++;
            end = QDateTime::fromString(QString("%1-%2-01").arg(year).arg(1),"yyyy-M-dd");
        }

        QSqlQuery query(database);
        QString command = QString("Select * from Session_table where ScheduledTime <= '%1' and ScheduledTime > '%2'")
                            .arg(end.toString("yyyy-MM-dd"))
                            .arg(start.toString("yyyy-MM-dd"));
        this->ExecuteCommand(command, query);

        QString mediationIdMatches = "";
        bool first = true;
        while(query.next())
        {
            if(!first)
            {
                mediationIdMatches += ", ";
            }
            mediationIdMatches += query.value(1).toString();
            first = false;
        }

        command = QString("Select * from Mediation_table where UpdatedDate <= '%1' and UpdatedDate > '%2' and DisputeState = '%3'")
                            .arg(end.toString("yyyy-MM-dd"))
                            .arg(start.toString("yyyy-MM-dd"))
                            .arg(QString::number(PROCESS_STATE_CLOSED_NO_SESSION));
        this->ExecuteCommand(command, query);


        while(query.next())
        {
            if(!first)
            {
                mediationIdMatches += ", ";
            }
            mediationIdMatches += query.value(1).toString();
            first = false;
        }

        MediationProcessVector* mpVec = LoadMediations(mediationIdMatches);

        mediationIdMatches = "";
        first = true;
        for(size_t i = 0; i < mpVec->size(); i++)
        {
            MediationProcess* process = mpVec->at(i);
            if(process->GetCountyId() == params->GetCounty())
            {
                if(!first)
                {
                    mediationIdMatches += ", ";
                }
                mediationIdMatches += QString::number(process->GetId());
                first = false;
            }
        }
        mpVec = LoadMediations(mediationIdMatches);
        monthlyreport* report = new monthlyreport();
        report->setCounty(county);
        report->setMonth(month);
        report->setYear(year);
        report->BuildReport(mpVec);

        arg.SetArg(report);
    }

    Mediator::Call(MKEY_DB_REQUEST_MONTHLY_REPORT_DONE, arg);
}
//========================================================================

MediationProcessVector* DRCDB::LoadMediations(QString processIds)
{
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = QString("Select * from Mediation_Table where process_id in (%1) order by UpdatedDateTime desc ").arg(processIds);
    bool result = false;

    result = this->ExecuteCommand(Mediation_command_string, Mediation_query);

    // Have the mediation processes now. Need to build them back up.
    QString processId;
    MediationProcessVector* processVector = new MediationProcessVector();
    while(Mediation_query.next())
    {
        MediationProcess* process = new MediationProcess();

        processId = Mediation_query.value(0).toString();

        //Rebuilds the process itself based on the database
        process->SetId(processId.toUInt());
        process->SetDisputeType((DisputeTypes)Mediation_query.value(1).toInt());
        process->SetCreatedDate(QDateTime::fromString(Mediation_query.value(4).toString(), "yyyy-MM-dd hh:mm:ss"));
        process->SetUpdatedDate(QDateTime::fromString(Mediation_query.value(5).toString(), "yyyy-MM-dd hh:mm:ss"));
        process->SetState((DisputeProcessStates)Mediation_query.value(6).toInt());
        process->SetInternalState((DisputeProcessInternalStates)Mediation_query.value(7).toInt());
        process->SetCountyId((CountyIds)Mediation_query.value(8).toInt());
        process->SetReferralType((ReferralTypes)Mediation_query.value(9).toInt());
        process->SetInquiryTypes((InquiryTypes)Mediation_query.value(10).toInt());
        process->SetInfoOnly(Mediation_query.value(11).toBool());
        process->SetIsCourtCase(Mediation_query.value(12).toBool());
        QString courtDate = Mediation_query.value(13).toString();
        if(courtDate != NULL)
        {
            process->SetCourtDate(QDate::fromString(courtDate, "yyyy-MM-dd"));
        }
        process->SetCourtType((CourtCaseTypes)Mediation_query.value(14).toInt());
        process->SetCourtOrder(Mediation_query.value(15).toString());
        process->SetRequiresSpanish(Mediation_query.value(16).toBool());
        process->SetSessionType((SessionTypes)Mediation_query.value(17).toInt());
        process->setMediationClause(Mediation_query.value(18).toBool());

        //Grab sessions based on the mediation id
        QSqlQuery sessionQuery(database);
        QString session_command_string = QString("Select * from Session_Table where process_id = %1")
                                                .arg(processId);
        this->ExecuteCommand(session_command_string, sessionQuery);

        MediationSessionVector* sessions = new MediationSessionVector();
        std::vector<int> sessionIds;
        while(sessionQuery.next())
        {
            // Rebuild sessions and add them to the process
            MediationSession* session = new MediationSession();

            session->SetId(sessionQuery.value(0).toInt());
            session->SetState((SessionStates)sessionQuery.value(2).toInt());
            session->setOutcome((SessionOutcomes)sessionQuery.value(3).toInt());

            session->setMediationTime(QDateTime::fromString(sessionQuery.value(6).toString(), "yyyy-MM-dd hh:mm:ss"));

            session->setMediator1(sessionQuery.value(7).toString());
            session->setMediator2(sessionQuery.value(8).toString());
            session->setObserver1(sessionQuery.value(9).toString());
            session->setObserver2(sessionQuery.value(10).toString());
            session->SetIsShuttle(sessionQuery.value(11).toBool());

            //Load the clientsession data, based on the session id
            QSqlQuery DataQuery(database);
            QString data_command_string = QString("Select * from Client_session_table where session_id = %1")
                                                .arg(session->GetId());
            bool dataResult = false;
            dataResult = this->ExecuteCommand(data_command_string, DataQuery);

            qDebug() << dataResult;

            while(DataQuery.next())
            {
                ClientSessionData* data = new ClientSessionData();

                data->SetId(DataQuery.value(0).toInt());
                data->setIncome(DataQuery.value(3).toString());
                data->setFee(DataQuery.value(4).toString());
                data->setPaid(DataQuery.value(5).toBool());
                data->setAttySaidAttend(DataQuery.value(6).toBool());
                data->setAttyDidAttend(DataQuery.value(7).toBool());
                data->setSupport(DataQuery.value(8).toUInt());
                data->setOnPhone(DataQuery.value(9).toBool());
                data->setAtTable(DataQuery.value(10).toBool());

                session->getClientSessionDataVector()->push_back(data);
            }

            sessions->push_back(session);
        }
        process->setMediationSessionVector(sessions);

        // Grab the notes, based on BOTH mediation id (easy) and session id (little trickier)

        QSqlQuery noteQuery(database);
        QString note_command_string = QString("Select * from Notes_Table where Process_id = %1").arg(processId);
        this->ExecuteCommand(note_command_string, noteQuery);

        while(noteQuery.next())
        {
            Note* note = new Note();
            note->SetId(noteQuery.value(0).toInt());
            note->SetMediationId(noteQuery.value(1).toInt());
            note->SetSessionId(noteQuery.value(2).toInt());
            note->SetMessage(noteQuery.value(3).toString());
            note->SetCreatedDate(QDateTime::fromString(noteQuery.value(4).toString(), "yyyy-MM-dd hh:mm:ss"));
            process->GetNotes()->push_back(note);
        }

        //Grab clients based on the mediation id
        QSqlQuery clientQuery(database);
        QString client_command_string = QString("Select * from Client_table where process_id = %1")
                                                .arg(processId);

        this->ExecuteCommand(client_command_string, clientQuery);

        QString personId;

        while(clientQuery.next())
        {
            // Rebuild clients and add them to the process... part of that is....
            Party* party = new Party();
            personId = clientQuery.value(2).toString();
            Person* primary = new Person();

            //Grab people based on the column in client
            QSqlQuery peopleQuery(database);
            QString people_command_string = QString("Select * from Person_Table where person_id = %1").arg(personId);

            this->ExecuteCommand(people_command_string, peopleQuery);
            while(peopleQuery.next())
            {
                // rebuild the primary client
                primary->SetId(personId.toUInt());
                primary->setFirstName(peopleQuery.value(1).toString());
                primary->setMiddleName(peopleQuery.value(2).toString());
                primary->setLastName(peopleQuery.value(3).toString());
                primary->setStreet(peopleQuery.value(4).toString());
                primary->setUnit(peopleQuery.value(5).toString());
                primary->setCity(peopleQuery.value(6).toString());
                primary->setState(peopleQuery.value(7).toString());
                primary->setZip(peopleQuery.value(8).toString());
                primary->setCounty((CountyIds)peopleQuery.value(9).toInt());
                primary->setPrimaryPhone(peopleQuery.value(10).toString());
                primary->setPrimaryPhoneExt(peopleQuery.value(11).toString());
                primary->setSecondaryPhone(peopleQuery.value(12).toString());
                primary->setSecondaryPhoneExt(peopleQuery.value(13).toString());
                primary->setEmail(peopleQuery.value(14).toString());
                party->SetPrimary(primary);
            }

            party->GetPrimary()->setNumberChildrenInHousehold(clientQuery.value(3).toUInt());
            party->GetPrimary()->setNumberInHousehold(clientQuery.value(4).toUInt());
            party->GetPrimary()->setAttorney(clientQuery.value(5).toString());
            party->GetPrimary()->setAttorneyPhone(clientQuery.value(6).toString());
            party->GetPrimary()->SetAttorneyEmail(clientQuery.value(7).toString());
            party->GetPrimary()->setAssistantName(clientQuery.value(8).toString());
            party->GetPrimary()->setAssistantPhone(clientQuery.value(9).toString());
            party->GetPrimary()->setAssistantEmail(clientQuery.value(10).toString());
            qDebug()<< "Assistant: " + clientQuery.value(8).toString() +
                       clientQuery.value(9).toString() +
                       clientQuery.value(10).toString();
            process->AddParty(party);
        }

        processVector->push_back(process);
    }
    return processVector;
}

//========================================================================
// Search for mediations using Person object
//------------------------------------------------------------------------
void DRCDB::QueryMediations(MediatorArg arg)
{
    Person* queryPerson = new Person();
    queryPerson = arg.getArg<Person*>();

    // first, find the people that match the arg
    QSqlQuery Find_Query(database);
    QString Find_Query_Command_string = "";
    if(queryPerson->SearchQuery() != "")
    {
        Find_Query_Command_string = QString("Select * from Person_Table where %1").arg(queryPerson->SearchQuery());
    }
    else
    {
        Find_Query_Command_string = QString("Select * from Person_Table").arg(queryPerson->SearchQuery());
    }
    qDebug() << Find_Query_Command_string;

    this->ExecuteCommand(Find_Query_Command_string, Find_Query);

    // build up a list of all the person ids that match this query
    QString personIdMatches = "";
    bool first = true;
    while(Find_Query.next())
    {
        if(!first)
        {
            personIdMatches += ", ";
        }
        personIdMatches += Find_Query.value(0).toString();
        first = false;
    }

    // Now... search the client list to get the mediations with these persons!
    Find_Query_Command_string = QString("Select * from Client_Table where Person_id in (%1)").arg(personIdMatches);

    qDebug() << Find_Query_Command_string;

    this->ExecuteCommand(Find_Query_Command_string, Find_Query);

    QString mediationIdMatches = "";
    first = true;
    while(Find_Query.next())
    {
        if(!first)
        {
            mediationIdMatches += ", ";
        }
        mediationIdMatches += Find_Query.value(1).toString();
        first = false;
    }

    MediationProcessVector* processVector = LoadMediations(mediationIdMatches);

    Mediator::Call(MKEY_DB_QUERY_MEDIATION, processVector);

}
//========================================================================



void DRCDB::LoadRecentMediations(MediatorArg arg)
{
    Q_UNUSED(arg);  // don't care about incoming arg.

    // sort by update date and return the most recent 10
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = "Select * from Mediation_Table order by UpdatedDateTime desc limit 10";
    this->ExecuteCommand(Mediation_command_string, Mediation_query);

    QString mediationIdMatches = "";
    bool first = true;
    while(Mediation_query.next())
    {
        if(!first)
        {
            mediationIdMatches += ", ";
        }
        mediationIdMatches += Mediation_query.value(0).toString();
        first = false;
    }

    MediationProcessVector* processVector = LoadMediations(mediationIdMatches);

    Mediator::Call(MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE, processVector);
}

void DRCDB::LoadPendingMediations(MediatorArg arg)
{
     Q_UNUSED(arg);  // don't care about incoming arg.
    // sort by update date and return the pending mediations
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = QString("Select * from Mediation_Table where DisputeState = %1 order by UpdatedDateTime desc")
                                        .arg(PROCESS_STATE_PENDING);
    this->ExecuteCommand(Mediation_command_string, Mediation_query);

    QString mediationIdMatches = "";
    bool first = true;
    while(Mediation_query.next())
    {
        if(!first)
        {
            mediationIdMatches += ", ";
        }
        mediationIdMatches += Mediation_query.value(0).toString();
        first = false;
    }

    MediationProcessVector* processVector = nullptr;

    if(mediationIdMatches != "");
        processVector = LoadMediations(mediationIdMatches);

    Mediator::Call(MKEY_DB_REQUEST_PENDING_MEDIATIONS_DONE, processVector);
}

void DRCDB::LoadScheduledMediations(MediatorArg arg)
{
     Q_UNUSED(arg);  // don't care about incoming arg.
    // sort by update date and return the scheduled mediations
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = QString("Select * from Mediation_Table where DisputeState = %1 order by UpdatedDateTime desc")
                                        .arg(PROCESS_STATE_SCHEDULED);
    this->ExecuteCommand(Mediation_command_string, Mediation_query);

    QString mediationIdMatches = "";
    bool first = true;
    while(Mediation_query.next())
    {
        if(!first)
        {
            mediationIdMatches += ", ";
        }
        mediationIdMatches += Mediation_query.value(0).toString();
        first = false;
    }

    MediationProcessVector* processVector = nullptr;

    if(mediationIdMatches != "");
        processVector = LoadMediations(mediationIdMatches);

    Mediator::Call(MKEY_DB_REQUEST_SCHEDULED_MEDIATIONS_DONE, processVector);
}

void DRCDB::LoadClosedMediations(MediatorArg arg)
{
     Q_UNUSED(arg);  // don't care about incoming arg.
    // sort by update date and return the closed mediations
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = QString("Select * from Mediation_Table where DisputeState in (%1, %2) order by UpdatedDateTime desc")
                                        .arg(PROCESS_STATE_CLOSED_WITH_SESSION)
                                        .arg(PROCESS_STATE_CLOSED_NO_SESSION);

    this->ExecuteCommand(Mediation_command_string, Mediation_query);

    QString mediationIdMatches = "";
    bool first = true;
    while(Mediation_query.next())
    {
        if(!first)
        {
            mediationIdMatches += ", ";
        }
        mediationIdMatches += Mediation_query.value(0).toString();
        first = false;
    }

    MediationProcessVector* processVector = nullptr;

    if(mediationIdMatches != "");
        processVector = LoadMediations(mediationIdMatches);


    Mediator::Call(MKEY_DB_REQUEST_CLOSED_MEDIATIONS_DONE, processVector);
}

void DRCDB::InsertOrUpdateMediation(MediatorArg arg)
{
    MediationProcess* process = nullptr;
    process = arg.getArg<MediationProcess*>();

    if(process->GetId() == 0)
    {
        InsertMediation(arg);
    }
    else
    {
        UpdateMediation(arg);
    }
}

void DRCDB::InsertMediation(MediatorArg arg)
{
    // Insert the mediation process as a whole (creates a new dispute)
    MediationProcess* process = nullptr;
    process = arg.getArg<MediationProcess*>();
    InsertObject(process);

    // Insert the notes.
    Note* note;
    for(size_t i = 0; i < process->GetNotes()->size(); i++)
    {
        note = process->GetNotes()->at(i);
        note->SetMediationId(process->GetId());

        InsertObject(note);
    }

    // Insert the Persons and the Clients
    Party* person = NULL;
    std::vector<int> clientIds;
    for(size_t i = 0; i < process->GetParties()->size(); i++)
    {
        // Insert each new person

        // As with above, these get passed to the join table where linkage
        // is preserved through the IDs
        person = process->GetParties()->at(i);

        if(person->GetPrimary()->getLastName() != "")
        {
            InsertObject(person->GetPrimary());
            InsertClientObject(process, person);
            clientIds.push_back((process->GetPartyAtIndex(i)->GetId()));
        }
    }
    MediationSession* session = NULL;

    for(size_t j = 0; j < process->getMediationSessionVector()->size(); j++)
    {
        // Insert each session that has been created by the dispute so far.
        // Linkage will be preserved through the id being linked
        session = process->getMediationSessionVector()->at(j);
        // Insert the sessions, linked to the process
        InsertLinkedObject(process->GetId(), session);
        for(size_t k = 0; k < clientIds.size(); k++)
        {
            // Insert Data particular to session, linked to client and session
            InsertClientSessionData(session->getClientSessionDataVectorAt(k), session->GetId(), clientIds[k]);
        }
    }
    Mediator::Call(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, arg);
}

void DRCDB::UpdateMediation(MediatorArg arg)
{
    // Insert the mediation process as a whole (creates a new dispute)
    MediationProcess* process = nullptr;
    process = arg.getArg<MediationProcess*>();
    UpdateObject(process);

    MediationSession* session = NULL;

    Note* note;

    QString note_clean_string = QString("delete from Notes_Table where process_id = %1")
                                .arg(process->GetId());
    QSqlQuery note_clean(database);

    this->ExecuteCommand(note_clean_string, note_clean);

    for(size_t i = 0; i < process->GetNotes()->size(); i++)
    {
        note = process->GetNotes()->at(i);
        {
            InsertObject(note);
        }
    }

    QString client_clean_string = QString("delete from Client_Table where process_id = %1")
                                         .arg(process->GetId());
    QSqlQuery client_clean(database);

    this->ExecuteCommand(client_clean_string, client_clean);

    Party* person = NULL;
    std::vector<int> clientIds;
    for(size_t i = 0; i < process->GetParties()->size(); i++)
    {
        // Insert each new person

        // As with above, these get passed to the join table where linkage
        // is preserved through the IDs
        person = process->GetParties()->at(i);

        if(person->GetPrimary()->GetId() == 0)
        {
            if(person->GetPrimary()->getLastName() != "")
            {
                InsertObject(person->GetPrimary());
                InsertClientObject(process, person);
            }
        }
        else
        {
            UpdateObject(person->GetPrimary());
            InsertClientObject(process, person);
        }
        clientIds.push_back(process->GetPartyAtIndex(i)->GetId());
    }

    for(size_t i = 0; i < process->getMediationSessionVector()->size(); i++)
    {
        session = process->getMediationSessionVector()->at(i);
        if(session->GetId() == 0)
        {
            // session newly created, need to insert
            InsertLinkedObject(process->GetId(), session);
        }
        else
        {
            // Session already existed, just need to update with new information
            UpdateObject(session);
        }
        //Delete old session data
        QString data_clean_string = QString("delete from Client_Session_Table where session_id = %1")
                                                 .arg(session->GetId());
        QSqlQuery data_clean(database);

        this->ExecuteCommand(data_clean_string, data_clean);
        for(size_t k = 0; k < clientIds.size(); k++)
        {
            // Insert Data particular to session, linked to client and session
            qDebug() << InsertClientSessionData(session->getClientSessionDataVectorAt(k), session->GetId(), clientIds[k]);
        }
    }

    Mediator::Call(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, arg);
}


void DRCDB::AddNewUser(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        // Set arg.IsSuccessful() to false as default
        // Will only change to true when the user has been authenticated
        arg.SetSuccessful(false);

        user = arg.getArg<User*>();
        if(user)
        {
            QSqlQuery UserQuery(database);
            QString UserCommandString = QString("Select * from User_table where userName = '%1'")
                                                .arg(user->GetName());
            this->ExecuteCommand(UserCommandString, UserQuery);
            if(!UserQuery.next())
            {
                this->InsertObject(user);
                arg.SetSuccessful(true);
            }
            else
            {
                arg.SetErrorMsg("Username already exists, please select a different one");
            }
        }
    }
    Mediator::Call(MKEY_DB_VERIFY_ADD_NEW_USER, arg);
}

void DRCDB::UpdateUser(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        // Set arg.IsSuccessful() to false as default
        // Will only change to true when the user has been authenticated
        arg.SetSuccessful(false);

        user = arg.getArg<User*>();
        if(user)
        {
            QString command_string = QString("update %1 set %2 where %3 = '%4'")
                    .arg(user->table())
                    .arg(user->UpdateParse())
                    .arg(user->GetIdRowName())
                    .arg(user->GetName());

            bool insertSuccess = false;
            QSqlQuery query_object(database);

            //Need to not immediately return so we can grab that ID that was created
            insertSuccess = this->ExecuteCommand(command_string, query_object);
            arg.SetSuccessful(insertSuccess);
            //Returning the boolean that was found before so work flow won't change
        }
    }
    Mediator::Call(MKEY_DB_VERIFY_UPDATE_USER, arg);
}

//========================================================================
//Database authentication test code.  Not really touching the database,
//mostly emulating the appropriate Mediator calls we'll be needing.
//This will be the method called when authenticating a new user login.
//========================================================================
void DRCDB::AuthenticateUser(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        // Set arg.IsSuccessful() to false as default
        // Will only change to true when the user has been authenticated
        arg.SetSuccessful(false);

        user = arg.getArg<User*>();
        if(user)
        {
            QSqlQuery UserQuery(database);
            QString UserCommandString = QString("Select * from User_table where userName = '%1' and password = '%2'")
                                            .arg(user->GetName())
                                            .arg(user->GetPass());
            this->ExecuteCommand(UserCommandString, UserQuery);

            while(UserQuery.next())
            {
                if(UserQuery.value(3).toBool() == true)
                {
                    user->SetType(USER_T_ADMIN);
                }
                arg.SetSuccessful(true);
                arg.SetArg(user);
            }
        }
    }
    else
    {

    }
    // Signal authentication has been completed

    Mediator::Call(MKEY_DB_AUTHENTICATE_USER_DONE, arg);

}

void DRCDB::RemoveUser(MediatorArg arg)
{
    User* user = nullptr;
    if(arg.IsSuccessful())
    {
        // Set arg.IsSuccessful() to false as default
        // Will only change to true when the user has been authenticated
        arg.SetSuccessful(false);

        user = arg.getArg<User*>();
        if(user)
        {
            QSqlQuery UserQuery(database);
            QString UserCommandString = QString("select * from User_table where userName = '%1' and Admin = '0'").arg(user->GetName());

            this->ExecuteCommand(UserCommandString, UserQuery);
            if(UserQuery.next())
            {
                arg.SetSuccessful(true);
            }
            UserCommandString = QString("delete from User_table where userName = '%1' and Admin = '0'")
                                            .arg(user->GetName());
            this->ExecuteCommand(UserCommandString, UserQuery);
        }
    }
    Mediator::Call(MKEY_DB_VERIFY_REMOVE_USER, arg);
}

void DRCDB::GetAllUsers(MediatorArg arg)
{
     Q_UNUSED(arg);  // don't care about incoming arg.
    QVector<User*>* users = new QVector<User*>();


    QSqlQuery UserQuery(database);
    QString UserCommandString = QString("Select * from User_table");

    this->ExecuteCommand(UserCommandString, UserQuery);

    while(UserQuery.next())
    {
        User* user = new User();
        user->SetName(UserQuery.value(1).toString());
        user->SetPassword(UserQuery.value(2).toString());
        user->SetType((UserTypes)UserQuery.value(3).toInt());
        users->push_back(user);
    }

    Mediator::Call(MKEY_DB_RETURN_ALL_USER, users);
}

//========================================================================

//========================================================================
//It first sets the driver that our database will be using (in this case,
//"QSQLITE", which is the driver for sqlite3.  It'll then set the name of
//the database file to the QString that was passed to this method.

//After everything has been set on the database object, we attempt
//to open a database; we check if an error has occurred in the process of
//opening the database.  If an error had occurred, then we pass a
//QSqlError object to the GetError method.

//--Note:   I don't know how to create a scenario where a database can
//          fail to open.  As such, the error mechanism currently isn't
//          tested against that.

//Return Values
//True:     Successfully Opened
//False:    Failed to Open
//------------------------------------------------------------------------
bool DRCDB::OpenDatabase(QString database_name)
{
    database = QSqlDatabase::addDatabase(db_driver, QString("Current_Connection"));
    database.setDatabaseName(database_name);
    database.setConnectOptions(QString("foreign_keys = ON"));
    database.open();

    // QSqlQuery query;
    // query.exec("PRAGMA foreign_keys = ON;");

    if(database.isOpenError())
        this->ExtractError(database.lastError(), QString("Database Failed to Open."));

    return database.isOpen();
}
//========================================================================

//========================================================================
//Consolidates a command_string with all the individual elements from the
//QVector that will make up the columns of this new table.

//Lastly we use the ExecuteCommand method of our database class to generate
//the tables, and returns a boolean indicating whether or not it was successful.

//--Note:   This method doesn't check for duplicate tables.  That bit of
//          functionality will be located in the DRCDB constructor.

//True:     Command Executed
//False:    Command Failed to Execute
//------------------------------------------------------------------------
bool DRCDB::CreateTable(QString table_name, QVector<QString> column_data)
{
    QString command_string = QString("create table %1 ").arg(table_name);

    command_string += "(";

    for (auto index = column_data.begin() ; index < column_data.end() ; ++index)
    {
        if (index != column_data.begin())
            command_string += ", ";

        command_string += *index;
    }

    command_string += ")";

    QSqlQuery query_object(database);
    return this->ExecuteCommand(command_string, query_object);
}
//========================================================================

//========================================================================
//Takes a generic Database object, and parses a valid command_string.
//The generic database object will insert 3 string values:

//      1.  The name of the table to be inserted into.
//      2.  A string "null" to activate the auto-incrementor of the database.
//          This "null" is positioned at the 1st column of the table where
//          unique ids are typically positioned in the table schema.
//      3.  The values contained within the database object.

//Note:     This method does not handle duplicate inserts; Business Logic
//          will have a better vantage in regards to determining whether
//          or not something is a duplicate.
//------------------------------------------------------------------------
bool DRCDB::InsertObject(DBBaseObject* db_object)
{
    //if (!this->DuplicateInsert(db_object->DuplicateQuery()))
    QString command_string = QString("insert into %1 %2 VALUES(%3)")
            .arg(db_object->table())
            .arg(db_object->ColumnNames())
            .arg(db_object->Parse());

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
        db_object->SetId(id);
    }
    else
    {
        qDebug()<<this->GetLastErrors();
    }

    return insertSuccess;
}

bool DRCDB::UpdateObject(DBBaseObject* db_object)
{
    QString command_string = QString("update %1 set %2 where %3 = %4")
            .arg(db_object->table())
            .arg(db_object->UpdateParse())
            .arg(db_object->GetIdRowName())
            .arg(db_object->GetId());

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(!insertSuccess)

    {
        qDebug() << command_string;
        qDebug() << this->ErrorMessageVec.last();
    }
    return insertSuccess;
}

//========================================================================


// For inserting objects which link only one direction (such as dispute having many sessions)
bool DRCDB::InsertLinkedObject(int linkedID, DBBaseObject* db_object)
{
    QString command_string = QString("insert into %1 %2 values ( %3, %4, %5 )")
            .arg(db_object->table())
            .arg(db_object->ColumnNames())
            .arg("null")
            .arg(linkedID)
            .arg(db_object->Parse());
//qDebug() << command_string;
    bool insertSuccess = false;
    QSqlQuery query_object(database);

    //Need to not immediately return so we can grab that ID that was created
    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
        db_object->SetId(id);
    }
    else
    {
        qDebug() << GetLastErrors().first();
    }

    return insertSuccess;
}

// Method to link a dispute and a party(really a person) through the client table
bool DRCDB::InsertClientObject(MediationProcess* dispute_object, Party* party_object)
{
    QString observerString;
    for(size_t i = 0; i < party_object->GetObservers().size(); i++)
    {
        Person* temp = party_object->GetObservers().at(i);
        observerString += temp->FullName();
    }

    QString value_string = QString("%1, %2, %3, %4, '%5', '%6', '%7', '%8', '%9', '%10'")
            .arg(dispute_object->GetId())
            .arg(party_object->GetPrimary()->GetId())
            .arg(party_object->GetPrimary()->getNumberChildrenInHousehold())
            .arg(party_object->GetPrimary()->getNumberInHousehold())
            .arg(party_object->GetPrimary()->getAttorney().replace("'","''"))
            .arg(party_object->GetPrimary()->getAttorneyPhone().replace("'","''"))
            .arg(party_object->GetPrimary()->getAttorneyEmail().replace("'","''"))
            .arg(party_object->GetPrimary()->getAssistantName().replace("'","''"))
            .arg(party_object->GetPrimary()->getAssistantPhone().replace("'","''"))
            .arg(party_object->GetPrimary()->getAssistantEmail().replace("'","''"));
            //Needs the assistant information as well!!!

    QString command_string = QString("insert into %1 values ( %2, %3 )")
            .arg("Client_Table")
            .arg("null")
            .arg(value_string);

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    //Need to not immediately return so we can grab that ID that was created
    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
        party_object->SetId(id);
    }
    else
    {
        qDebug()<<this->GetLastErrors();
    }

    return insertSuccess;
}

bool DRCDB::InsertClientSessionData(ClientSessionData* data, int sessionId, int clientId)
{
    QString value_string = QString("%1, %2, '%3', '%4', '%5', '%6', '%7', %8, '%9', '%10'")
                                .arg(clientId)
                                .arg(sessionId)
                                .arg(data->getIncome())
                                .arg(data->getFee())
                                .arg(data->getPaid())
                                .arg(data->getAttySaidAttend())
                                .arg(data->getAttyDidAttend())
                                .arg(data->getSupport())
                                .arg(data->getOnPhone())
                                .arg(data->getAtTable());

    QString command_string = QString("insert into %1 values (%2, %3)")
                                .arg("Client_Session_Table")
                                .arg("null")
                                .arg(value_string);

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(!insertSuccess)
    {
        qDebug()<<this->GetLastErrors();
    }

    return insertSuccess;
}

//========================================================================
//Prepare checks the potential SQL command for validity.  While it seems
//tedious, it apparently is more efficient than letting an erroneous
//command be executed directly.

//If command_string is invalid, an error message is extracted from the
//QSqlQuery object, and pushed into ErrorMessageVec.

//--Note:   This method is only ever used internally by the class itself.
//          After testing is finished, should be made private.

//--Note:   The reason I decided to pass a QSqlQuery object by reference is
//          because all SQL "select" commands use the QSqlQuery object to
//          return the valid fields found after a search.

//          While the trade-off is that every method that requires a QSqlQuery
//          object must instantiate one, it allows us to save on three lines
//          of code for every time we implement a new Select method.

//Return Values:
//True:     Command Executed Successfully
//False:    Command Failed to Execute
//------------------------------------------------------------------------
bool DRCDB::ExecuteCommand(QString command_string, QSqlQuery &query_object)
{
    if(!query_object.prepare(command_string))
        this->ExtractError(query_object.lastError(), command_string);

    return query_object.exec();
}
//========================================================================


//========================================================================
//Initial attempt at a generic search function for the Person Table.
//May not even be relevant depending on the way the DB tables change.

//--Note:   Untested.
//------------------------------------------------------------------------
//QVector<QString> DRCDB::SelectField(Filter filter_object)
QVector<QString> DRCDB::SelectPersonField(QString column_name, QString table_name, QString comparison_symbol, QString find_value)
{
    QVector<QString> return_vec;

    QString command_string = QString("select %1 from %2 where %3%4'%5'")
            .arg(column_name)
            .arg(table_name)
            .arg(column_name)
            .arg(comparison_symbol)
            .arg(find_value);

    QSqlQuery query_object(database);
    this->ExecuteCommand(command_string, query_object);

    while(query_object.next())
    {
        return_vec.push_back(query_object.value(0).toString());
    }

    return return_vec;
}
//========================================================================



//========================================================================
//A simple query that returns all values currently contained within the
//table indicated.

//QVector.count > 0:        Success
//QVector.count == 0:       Failure
//------------------------------------------------------------------------
QVector<QString> DRCDB::SelectOneFields(QString table_name, QString id_name, int id)
{
    QVector<QString> return_vec;

    if (this->DoesTableExist(table_name))
    {
        QString command_string = QString("select * from %1 where %2 = %3")
                .arg(table_name)
                .arg(id_name)
                .arg(QString::number(id));

        QSqlQuery query_object(database);
        this->ExecuteCommand(command_string, query_object);

        while(query_object.next())
        {
            QSqlRecord temp = query_object.record();
            for (int index = 0 ; index < temp.count() ; ++index)
                return_vec.push_back(query_object.value(index).toString());
        }
    }

    return return_vec;
}
//========================================================================



//========================================================================
//Takes a QSqlError object that is returned by a QSqlQuery object that fails
//to execute its given command.  It checks to make sure an error has been set
//in the error_object before the error string is appended to the LastError
//vector.

//--Note:  This method is only ever used internally by the class itself.
//         After testing is finished, should be made private.

//Return Values
//True:     Error Occurred
//False:    No Error Occurred / Detected
//------------------------------------------------------------------------
bool DRCDB::ExtractError(const QSqlError &error_object, QString command_string)
{
    DB_ERROR = error_object.isValid();

    if (DB_ERROR)
    {
        qDebug() << command_string;
        qDebug() << error_object.databaseText();
        qDebug() << error_object.driverText();

        ErrorMessageVec.push_back(command_string);
        ErrorMessageVec.push_back(error_object.databaseText());
        ErrorMessageVec.push_back(error_object.driverText());
    }

    return DB_ERROR;
}
//========================================================================



//========================================================================
//Return Values
//True:     Error has occurred
//False:    Error has not occurred
//------------------------------------------------------------------------
bool DRCDB::DidErrorOccur()
{
    return DB_ERROR;
}
//========================================================================



//========================================================================
//Returns a vector containing all the errors that has occurred since its
//last call.

//      Whenever this method is called:
//      1.  DB_ERROR will be set with a fresh boolean value
//      2.  Error messages currently inside ErrorMessageVec will be
//          transferred to a return variable.
//      3.  Error messages inside ErrorMessageVec will be clared.
//      4.  Error messages will be returned.

//Note:     The reason DB_ERROR is set by whether or not the database
//          opened with an error is because if an error originated
//          from a Query object, then that error is automatically resolved
//          when that Query object goes out of scope.  However, an
//          error to open a database is a far more permenant issue.
//------------------------------------------------------------------------
QVector<QString> DRCDB::GetLastErrors()
{
    DB_ERROR = database.isOpenError();

    QVector<QString> retVec = this->ErrorMessageVec;
    this->ErrorMessageVec.clear();

    return retVec;
}
//========================================================================


//********************************Test Methods********************************
//========================================================================
//------------------------------------------------------------------------
bool DRCDB::IsDatabaseOpen()
{
    return database.isOpen();
}
//========================================================================

//========================================================================
//Returns the name of the database with which we named it.
//------------------------------------------------------------------------
QString DRCDB::WhatDatabaseName()
{
    return database.databaseName();
}
//========================================================================

//========================================================================
//A way to programmically verify that a column within a table exists.
//------------------------------------------------------------------------
QVector<QString> DRCDB::GetColumnsList(QString table_name)
{
    QSqlRecord column_list = database.record(table_name);

    QVector<QString> columns_vector;

    for (int index = 0 ; index < column_list.count() ; ++index)
        columns_vector.push_back(column_list.fieldName(index));

    return columns_vector;
    //return column_list.contains(column_name);
}
//========================================================================

//========================================================================
//------------------------------------------------------------------------
QString DRCDB::WhatOptionsEnabled()
{
    return database.connectOptions();
}
//========================================================================
//********************************Test Methods********************************
