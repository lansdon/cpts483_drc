#include "drcdb.h"
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

    if (!this->DoesTableExist(person_table_name))
    {
        CreatePersonTable(person_table_name);
    }

    // Register to Listen for events.
//    Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){PersistFruit(arg);});
//    Mediator::Register(MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){LoadFruit(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){LoadIntake(arg);});
//    Mediator::Register(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, [this](MediatorArg arg){PersistIntakeForm(arg);});
}
//========================================================================



//========================================================================
//------------------------------------------------------------------------
QString DRCDB::WhatOptionsEnabled()
{
    return database.connectOptions();
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
//Returns the name of the database with which we named it.
//------------------------------------------------------------------------
QString DRCDB::WhatDatabaseName()
{
    return database.databaseName();
}

//========================================================================


//========================================================================
//------------------------------------------------------------------------
bool DRCDB::IsDatabaseOpen()
{
    return database.isOpen();
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

    QSqlQuery query_object(database);

    return this->ExecuteCommand(command_string, query_object);
}
//========================================================================



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
//    QStringList database_tables = database.tables();
//    return database_tables.size() == 0;
//}
//========================================================================
//========================================================================
//Constructor takes in a database_name, and opens it.
//--Note:  Seems largely unnecessary since we're doing things via the
//          default constructor.
//------------------------------------------------------------------------
//DRCDB::DRCDB(QString database_name) : DB_ERROR(false)
//{
//    this->OpenDatabase(database_name);
//}
//========================================================================
//========================================================================
//Currently commented out due to how we may want to handle duplicate information.
//As it stands, BL may be querying the database for duplicate information.

//Note: It seems QSqlQuery.size() is not compatible with SQLITE3, which
//      resulted in using QSqlQuery.next() instead.

//Note: Unfortunately we can't use ExecuteCommand method to prevent
//      duplicate code due to the fact that we still need the
//      query_object that goes out of scope.
//------------------------------------------------------------------------
//bool DRCDB::DuplicateInsert(const QString &duplicate_query)
//{
//    bool duplicate_exists = false;

//    QSqlQuery query_object(database);
//    if(this->ExecuteCommand(duplicate_query, query_object))
//    {
//        if (query_object.next())
//        {
//            duplicate_exists = true;
//            DB_ERROR = true;
//            ErrorMessageVec.push_back(QString("Duplicate Insert Was Attempted: %1.")
//                                 .arg(duplicate_query));
//        }
//    }

//    return duplicate_exists;
//}
//========================================================================
