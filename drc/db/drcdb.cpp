#include "drcdb.h"
#include "drctypes.h"
#include <QtSql/QtSql>
//#include "Mediator.h"
//#include "MediatorKeys.h"
//#include "DRCModels.h"
//#include "Fruit.h"    // temp.. not sure why it's having circular dependency.

#define db_driver "QSQLITE"

//========================================================================
//------------------------------------------------------------------------
DRCDB::DRCDB() : DB_ERROR(false)
{
    OpenDatabase("drc_db.db3");

    //Name of the table we're creating.
    QString person_table_name = QString("Person_Table");
    QString mediation_table_name = QString("Mediation_Table");
    QString session_table_name = QString("Session_Table");
    QString client_table_name = QString("Client_Table");
    QString notes_table_name = QString("Notes_Table");

    bool result = false;

    if (!this->DoesTableExist(person_table_name))
    {
        result = CreatePersonTable(person_table_name);
    }

    result = false;

    if (!this->DoesTableExist(mediation_table_name))
    {
        result = CreateMediationTable(mediation_table_name);
    }

    result = false;

    if (!this->DoesTableExist(session_table_name))
    {
        result = CreateSessionTable(session_table_name);
    }

    result = false;

    if (!this->DoesTableExist(client_table_name))
    {
        result = CreateClientTable(client_table_name);
    }

    result = false;

    if(!this->DoesTableExist(notes_table_name))
    {
        result = CreateNotesTable(notes_table_name);
    }

    result = false;

    if (!this->DoesTableExist(mediation_table_name))
    {
         result = CreatePersonTable(mediation_table_name);
    }

    // Populate our fake user list.  Delete this later!!
    UserMap["Admin"] = sha256("adminpassword", "");
    UserMap["Normal"] = sha256("normalpassword", "");
    UserMap[""] = sha256("", "");

    // Register to Listen for events.
    Mediator::Register(MKEY_GUI_AUTHENTICATE_USER, [this](MediatorArg arg){AuthenticateUser(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){InsertMediation(arg);});
    Mediator::Register(MKEY_BL_REQUEST_RECENT_MEDIATIONS_DONE, [this](MediatorArg arg){LoadRecentMediations(arg);});

    //Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){PersistFruit(arg);});
    //Mediator::Register(MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){LoadFruit(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){LoadIntake(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, [this](MediatorArg arg){PersistIntakeForm(arg);});
}
//========================================================================







//========================================================================
//------------------------------------------------------------------------
bool DRCDB::CreatePersonTable(const QString& person_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> person_table_columns;
    person_table_columns.push_back(QString("person_id integer primary key autoincrement null"));
    person_table_columns.push_back(QString("first_name char(50)"));
    person_table_columns.push_back(QString("middle_name char(50)"));
    person_table_columns.push_back(QString("last_name char(50) not null"));
    person_table_columns.push_back(QString("street_name char(50)"));
    person_table_columns.push_back(QString("unit_name char(50)"));
    person_table_columns.push_back(QString("city_name char(50)"));
    person_table_columns.push_back(QString("state_name char(50)"));
    person_table_columns.push_back(QString("zip_code char(50)"));
    person_table_columns.push_back(QString("county_name char(50)"));
    person_table_columns.push_back(QString("primary_phone char(50)"));  //Confirm Phone Format
    person_table_columns.push_back(QString("secondary_phone char(50)"));
    person_table_columns.push_back(QString("assistance_phone char(50)"));
    person_table_columns.push_back(QString("email_address char(50)"));
    person_table_columns.push_back(QString("number_in_house int"));
    person_table_columns.push_back(QString("attorney_name char(50)"));

    return CreateTable(person_table_name, person_table_columns);
}

//========================================================================

bool DRCDB::CreateMediationTable(const QString& mediation_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> mediation_table_columns;
    mediation_table_columns.push_back(QString("Process_id integer primary key autoincrement null"));
    mediation_table_columns.push_back(QString("DisputeType integer"));
    mediation_table_columns.push_back(QString("CreationDate Date"));
    mediation_table_columns.push_back(QString("UpdatedDate Date"));
    mediation_table_columns.push_back(QString("DisputeState integer"));
    mediation_table_columns.push_back(QString("DisputeCounty integer"));
    mediation_table_columns.push_back(QString("DisputeNotes char(128)"));
    mediation_table_columns.push_back(QString("ReferalSource integer"));
    mediation_table_columns.push_back(QString("TranslatorRequired Bool"));

    return CreateTable(mediation_table_name, mediation_table_columns);
}

bool DRCDB::CreateClientTable(const QString& client_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> client_table_columns;
    client_table_columns.push_back(QString("Client_id integer primary key autoincrement null"));
    client_table_columns.push_back(QString("Process_id integer"));
    client_table_columns.push_back(QString("Person_id integer"));
    client_table_columns.push_back(QString("Children integer"));
    client_table_columns.push_back(QString("Observers char(128)"));
    client_table_columns.push_back(QString("Attorney char(128)"));
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
    session_table_columns.push_back(QString("Fee1Paid integer"));
    session_table_columns.push_back(QString("Fee2Paid integer"));
    session_table_columns.push_back(QString("FeeFamilyPaid integer"));
    session_table_columns.push_back(QString("Fee1OtherPaid integer"));
    session_table_columns.push_back(QString("Fee1 integer"));
    session_table_columns.push_back(QString("Fee2 integer"));
    session_table_columns.push_back(QString("FeeFamily integer"));
    session_table_columns.push_back(QString("FeeOther integer"));
    session_table_columns.push_back(QString("IncomeFee1 integer"));
    session_table_columns.push_back(QString("IncomeFee2 integer"));
    session_table_columns.push_back(QString("IncomeFeeFamily integer"));
    session_table_columns.push_back(QString("IncomeFeeOther integer"));
    session_table_columns.push_back(QString("Mediator1 char(128)"));
    session_table_columns.push_back(QString("Mediator2 char(128)"));
    session_table_columns.push_back(QString("Observer1 char(128)"));
    session_table_columns.push_back(QString("Observer2 char(128)"));
    session_table_columns.push_back(QString("foreign key(Process_id) references Mediation_Table(Process_id)"));

    return CreateTable(session_table_name, session_table_columns);
}

bool DRCDB::CreateNotesTable(const QString& Notes_table_name)
{
    //Name and Datatypes of all Table columns
    QVector<QString> notes_table_columns;
    notes_table_columns.push_back(QString("Note_id integer primary key autoincrement null"));
    notes_table_columns.push_back(QString("Process_id integer"));
    //notes_table_columns.push_back(QString("Session_id integer")); // TO BE ADDED when notes model updated by gui
    notes_table_columns.push_back(QString("Note char(128)"));
    notes_table_columns.push_back(QString("CreateDate Date"));
    notes_table_columns.push_back(QString("foreign key(Process_id) references Mediation_Table(Process_id)"));
    //notes_table_columns.push_back(QString("foreign key(Session_id) references Session_Table(Session_id)"));

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
    database.close();
    return !database.isOpen();
}
//========================================================================



//========================================================================
//------------------------------------------------------------------------
DRCDB::~DRCDB()
{
    this->CloseDatabase();
}
//========================================================================

void DRCDB::LoadRecentMediations(MediatorArg arg)
{
    // sort by update date and return the most recent 10
    QSqlQuery Mediation_query(database);
    QString Mediation_command_string = "Select * from Mediation_Table order by UpdatedDate desc limit 10";
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
        process->SetCreatedDate(QDateTime::fromString(Mediation_query.value(2).toString()));
        process->SetUpdatedDate(QDateTime::fromString(Mediation_query.value(3).toString()));
        process->SetProcessState((DisputeProcessStates)Mediation_query.value(4).toInt());
        process->SetCountyId((CountyIds)Mediation_query.value(5).toInt());
        process->AddNote(Mediation_query.value(6).toString());
        process->SetReferralType((ReferralTypes)Mediation_query.value(7).toInt());
        process->SetRequiresSpanish(Mediation_query.value(8).toBool());

        //Grab sessions based on the mediation id
        QSqlQuery sessionQuery(database);
        QString session_command_string = QString("Select * from Session_Table where process_id = %1")
                                                .arg(processId);
        bool sessionResult = false;
        sessionResult = this->ExecuteCommand(session_command_string, sessionQuery);

        MediationSessionVector* sessions = new MediationSessionVector();
        while(sessionQuery.next())
        {
            // Rebuild sessions and add them to the process
            MediationSession* session = new MediationSession();

            //session->SetState((SessionStates)sessionQuery.value(2).toInt());

            session->setFee1Paid(sessionQuery.value(3).toBool());
            session->setFee2Paid(sessionQuery.value(4).toBool());
            session->setFeeFamilyPaid(sessionQuery.value(5).toBool());
            session->setFeeOtherPaid(sessionQuery.value(6).toBool());

            session->setFee1(sessionQuery.value(7).toString());
            session->setFee2(sessionQuery.value(8).toString());
            session->setFeeFamily(sessionQuery.value(9).toString());
            session->setFeeOther(sessionQuery.value(10).toString());
            session->setIncomeFee1(sessionQuery.value(11).toString());
            session->setIncomeFee2(sessionQuery.value(12).toString());
            session->setIncomeFeeFamily(sessionQuery.value(13).toString());
            session->setIncomeFeeOther(sessionQuery.value(14).toString());

            //TODO: Make these into just needing names... they're not "client" type people
            //session->setMediator1(sessionQuery.value(15).toString());
            //session->setMediator2(sessionQuery.value(16).toString());
            //session->setObserver1(sessionQuery.value(17).toString());
            //session->setObserver2(sessionQuery.value(18).toString());

            sessions->push_back(session);
        }
        process->setMediationSessionVector(sessions);

        //Grab clients based on the mediation id
        QSqlQuery clientQuery(database);
        QString client_command_string = QString("Select * from Client_table where process_id = %1")
                                                .arg(processId);

        bool clientResult = false;
        clientResult = this->ExecuteCommand(client_command_string, clientQuery);

        QString personId;

        while(clientQuery.next())
        {
            // Rebuild clients and add them to the process... part of that is....
            Party* party = new Party();
            personId = clientQuery.value(2).toString();
            Person* primary = new Person();// = nullptr;
            //Grab people based on the column in client
            QSqlQuery peopleQuery(database);
            QString people_command_string = QString("Select * from Person_Table where person_id = %1").arg(personId);

            bool personResult = false;
            personResult = this->ExecuteCommand(people_command_string, peopleQuery);
            while(peopleQuery.next())
            {
                // rebuild the primary client
                primary->setFirstName(peopleQuery.value(1).toString());
                primary->setMiddleName(peopleQuery.value(2).toString());
                primary->setLastName(peopleQuery.value(3).toString());
                primary->setStreet(peopleQuery.value(4).toString());
                primary->setUnit(peopleQuery.value(5).toString());
                primary->setCity(peopleQuery.value(6).toString());
                primary->setState(peopleQuery.value(7).toString());
                primary->setZip(peopleQuery.value(8).toString());
                primary->setCounty(peopleQuery.value(9).toString());
                primary->setPrimaryPhone(peopleQuery.value(10).toString());
                primary->setSecondaryPhone(peopleQuery.value(11).toString());
                primary->setAssistantPhone(peopleQuery.value(12).toString());
                primary->setEmail(peopleQuery.value(13).toString());
                primary->setNumberInHousehold(peopleQuery.value(14).toUInt());
                primary->setAttorney(peopleQuery.value(15).toString());
                party->SetPrimary(primary);
                qDebug() << "DB: Adding primary to party - " << primary->FullName();
            }

            // NOT FULLY IMPLEMENTED YET! these members of party have to change

            // TODO: Children in a party should be just a number
            // TODO: Observers in a party should be just a name
            // TODO: Attorney... This data needs to be more robust in the database.
            //       Translation: Degan - redo that insertjoinobject method for that.
            //
            // party->SetChildren(clientQuery.value(3).toUInt());
            // party->SetObservers(clientQuery.value(4).toString());
            // party->SetAttorney(clientQuery.value(5).toString());
            process->AddParty(party);
        }

        processVector->push_back(process);
    }
    Mediator::Call(MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE, processVector);
}

void DRCDB::InsertMediation(MediatorArg arg)
{
    // Insert the mediation process as a whole (creates a new dispute)
    MediationProcess* process = nullptr;
    process = arg.getArg<MediationProcess*>();
    InsertObject(process);

    MediationSession* session = NULL;

    for(int i = 0; i < process->getMediationSessionVector()->size(); i++)
    {
        // Insert each session that has been created by the dispute so far.
        // Linkage will be preserved through the id being linked
        session = process->getMediationSessionVector()->at(i);

        InsertLinkedObject(process->GetId(), session);

    }
    Party* person = NULL;
    for(int i = 0; i < process->GetParties()->size(); i++)
    {
        // Insert each new person
        // TODO: Add a check to prevent adding duplicate people

        // As with above, these get passed to the join table where linkage
        // is preserved through the IDs
        person = process->GetParties()->at(i);

        InsertObject(person->GetPrimary());
        InsertJoinObject(process, person);
    }
    Mediator::Call(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, arg);
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
            // arg value type was a User
            if (UserMap.find(user->GetName()) != UserMap.end())
            {
                // Username found in UserMap
                if (user->GetPass() == UserMap[user->GetName()])
                {
                    // Set arg.IsSuccessful() to true
                    arg.SetSuccessful(true);
                    if (user->GetName() == "Admin")
                    {
                        user->SetType(USER_T_ADMIN);
                    }

                    // Reset arg value to the user.
                    // Assume the user object has been modified as needed
                    arg.SetArg(user);
                }
            }
        }
    }
    else
    {
        // Set the error label.
        //ui->statusLabel->setText(arg.ErrorMessage());
    }
    // Signal authentication has been completed
    Mediator::Call(MKEY_DB_AUTHENTICATE_USER_DONE, arg);
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
    database = QSqlDatabase::addDatabase(db_driver);
    database.setDatabaseName(database_name);
    database.setConnectOptions(QString("foreign_keys = ON"));
    database.open();

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

    if(database.isOpenError())
        this->ExtractError(database.lastError());

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
    QString command_string = QString("insert into %1 values ( %2, %3 )")
            .arg(db_object->table())
            .arg("null")
            .arg(db_object->Parse());

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    //Need to not immediately return so we can grab that ID that was created
    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
        db_object->SetId(id);
    }

    //Returning the boolean that was found before so work flow won't change
    return insertSuccess;
}
//========================================================================


// For inserting objects which link only one direction (such as dispute having many sessions)
bool DRCDB::InsertLinkedObject(int linkedID, DBBaseObject* db_object)
{
    //if (!this->DuplicateInsert(db_object->DuplicateQuery()))
    QString command_string = QString("insert into %1 values ( %2, %3, %4 )")
            .arg(db_object->table())
            .arg("null")
            .arg(linkedID)
            .arg(db_object->Parse());

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    //Need to not immediately return so we can grab that ID that was created
    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
        db_object->SetId(id);
    }

    //Returning the boolean that was found before so work flow won't change
    return insertSuccess;
}


/*
// For inserting into the many-to-many table... might not be able to template.
// Keeping this here incase we think of a way we can
bool DRCDB::InsertJoinObject(DBBaseObject* db_object1, DBBaseObject* db_object2)
{
    //if (!this->DuplicateInsert(db_object->DuplicateQuery()))
    QString command_string = QString("insert into %1 values ( %2, %3 )")
            .arg("ARGLEBARGLECHANGEME")
            .arg("null")
            .arg(db_object1->Parse()); // NOT CHANGED! THIS WILL NOT WORK

    bool insertSuccess = false;
    QSqlQuery query_object(database);

    //Need to not immediately return so we can grab that ID that was created
    insertSuccess = this->ExecuteCommand(command_string, query_object);

    if(insertSuccess)
    {
        int id = query_object.lastInsertId().toInt();
    }

    //Returning the boolean that was found before so work flow won't change
    return insertSuccess;
}
*/


// Method to link a dispute and a party(really a person) through the client table
bool DRCDB::InsertJoinObject(MediationProcess* dispute_object, Party* party_object)
{
    //if (!this->DuplicateInsert(db_object->DuplicateQuery()))

    QString observerString;
    for(int i = 0; i < party_object->GetObservers().size(); i++)
    {
        Person* temp = party_object->GetObservers().at(i);
        observerString += temp->FullName();
    }

    QString value_string = QString("%1, %2, %3, '%4', '%5'")
            .arg(dispute_object->GetId())
            .arg(party_object->GetPrimary()->GetId())
            .arg(party_object->GetChildren().size())
            .arg(observerString)
            .arg(party_object->GetAttorney().FullName());

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
        //db_object->SetId(id);
    }

    //Returning the boolean that was found before so work flow won't change
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
        this->ExtractError(query_object.lastError());

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
QVector<QString> DRCDB::SelectAllFields(QString table_name)
{
    QVector<QString> return_vec;

    QString command_string = QString("select * from %1")
            .arg(table_name);

    QSqlQuery query_object(database);
    this->ExecuteCommand(command_string, query_object);

    while(query_object.next())
    {
        QString time(query_object.value(0).toString());
        QString name(query_object.value(1).toString());
        QString id(query_object.value(2).toString());
        return_vec.push_back(time);
        return_vec.push_back(name);
        return_vec.push_back(id);
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
bool DRCDB::ExtractError(const QSqlError &error_object)
{
    DB_ERROR = error_object.isValid();

    if (DB_ERROR)
        ErrorMessageVec.push_back(error_object.text());

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
bool DRCDB::DoesColumnExist(QString column_name, QString table_name)
{
    QSqlRecord column_list = database.record(table_name);
    return column_list.contains(column_name);
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

//void DRCDB::PersistIntakeForm(MediatorArg arg) const
//{
//    bool success = arg.IsSuccessful();
//    QString errorMessage = arg.ErrorMessage();

//    Intake* intake = nullptr;       // Unpackaged argument
//    if (success)
//    {
//        intake = arg.getArg<Intake*>();

//        // SUCCESS!! INSERT CODE HERE
//    }
/*
 * if db_error = true
 * {
 * arg.issuccessful = false
 * arg.errormessage = db_error_message
 *
 *
 *
 * */

//    qDebug() << "DB -> PersistIntakeForm Complete";
//    Mediator::Call(MKEY_DB_PERSIST_INTAKE_FORM_DONE, intake, success, errorMessage);
//}

//void DRCDB::PersistFruit(MediatorArg arg)
//{
//    bool success = arg.IsSuccessful();
//    QString errorMessage = arg.ErrorMessage();

//    Fruit* fruit = nullptr;       // Unpackaged argument
//    if (success)
//    {
//        fruit = arg.getArg<Fruit*>();

//        InsertObject(fruit);
//    }

//    qDebug() << "DB -> PersistFruit Complete";
//    Mediator::Call(MKEY_DB_PERSIST_FRUIT_NAME_DONE, fruit, success, errorMessage);
//}

//void DRCDB::LoadFruit(MediatorArg arg)
//{
//    QVector<QString> results = SelectAllFields(QString("Albertsons"));
//    qDebug() << "Data stored in database; name then timestamp\n";
//    for(int i = 0; i < results.size(); i++)
//    {
//        qDebug() << results.at(i) << endl;
//    }
//    qDebug() << "DB -> LoadFruit Complete";
//}

//void DRCDB::LoadIntake(MediatorArg arg) const
//{
//    bool success = arg.IsSuccessful();
//    QString errorMessage = arg.ErrorMessage();

//    Intake* intake = nullptr;       // Unpackaged argument
//    if (success)
//    {
//        // Returning a test object... This should be deleted!!!
//        intake = new Intake();
//        intake->addClaimant(Person("CLAIMENT DB TEST"));
//        intake->addRespondents(Person("Respondent1"));
//        intake->addRespondents(Person("Respondent2"));
//        intake->addRespondents(Person("Respondent3"));

//        // SUCCESS!! INSERT CODE HERE
//    }

//    qDebug() << "DB -> PersistIntakeForm Complete";
//    Mediator::Call(MKEY_DB_LOAD_INTAKE_FORM_DONE, intake, success, errorMessage);
//}

//********************************Deprecated Methods********************************
//========================================================================
//A method that is ultimately unnecessary because of another
//table checking method.
//Verifies whether or not a database contains tables.
//------------------------------------------------------------------------
//bool DRCDB::IsDatabaseEmpty()
//{
// QStringList database_tables = database.tables();
// return database_tables.size() == 0;
//}
//========================================================================
//========================================================================
//Constructor takes in a database_name, and opens it.
//--Note: Seems largely unnecessary since we're doing things via the
// default constructor.
//------------------------------------------------------------------------
//DRCDB::DRCDB(QString database_name) : DB_ERROR(false)
//{
// this->OpenDatabase(database_name);
//}
//========================================================================
//========================================================================
//Currently commented out due to how we may want to handle duplicate information.
//As it stands, BL may be querying the database for duplicate information.

//Note: It seems QSqlQuery.size() is not compatible with SQLITE3, which
// resulted in using QSqlQuery.next() instead.

//Note: Unfortunately we can't use ExecuteCommand method to prevent
// duplicate code due to the fact that we still need the
// query_object that goes out of scope.
//------------------------------------------------------------------------
//bool DRCDB::DuplicateInsert(const QString &duplicate_query)
//{
// bool duplicate_exists = false;

// QSqlQuery query_object(database);
// if(this->ExecuteCommand(duplicate_query, query_object))
// {
// if (query_object.next())
// {
// duplicate_exists = true;
// DB_ERROR = true;
// ErrorMessageVec.push_back(QString("Duplicate Insert Was Attempted: %1.")
// .arg(duplicate_query));
// }
// }

// return duplicate_exists;
//}
//========================================================================
//********************************Deprecated Methods********************************
