#include "drcdb.h"
#include <QtSql/QtSql>
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorKeys.h"
#include "drc_shared/models/DRCModels.h"
#include "drc_shared/models/Fruit.h"    // temp.. not sure why it's having circular dependency.

using std::string;
using std::vector;


DRCDB::DRCDB() : DB_ERROR(false)
{
    OpenDatabase("drc_db.db3");

    // Register to Listen for events.
    Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){PersistFruit(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){LoadIntake(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, [this](MediatorArg arg){PersistIntakeForm(arg);});
}


DRCDB::DRCDB(string database_name) : DB_ERROR(false)
{
    OpenDatabase(database_name);
}

void DRCDB::OpenDatabase(string database_name)
{
    database =  QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString::fromStdString(database_name));
    DB_ERROR = database.open();

    // !!!! Sorry for molesting your code!! Forgive me.  -LP


//    //sqlite3_open both creates and/or opens a database.
//    int sql_result = sqlite3_open(database_name.c_str(), &database);

//    if (sql_result)     //If result != 0, then database didn't open.
//        DB_ERROR = true;
//    else                //If result == 0, then database opened.
//        DB_ERROR = false;
}

bool DRCDB::isError()
{
    return DB_ERROR;
}

string DRCDB::errorMessage()
{
//    return string(sqlite3_errmsg(database));
    return database.lastError().text().toStdString();
}

void DRCDB::CreateTable(string table_name)
{

}

void DRCDB::AddColumn(string column_name, string column_type, string column_required, bool primary_key)
{

}

void DRCDB::InsertField(string fruit_name, string time_stamp)
{

}

vector<string> DRCDB::SelectAllField()
{
    vector<string> empty;
    return empty;

}

void DRCDB::PersistIntakeForm(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;       // Unpackaged argument
    if (success)
    {
        intake = arg.getArg<Intake*>();

        // SUCCESS!! INSERT CODE HERE
    }

    qDebug() << "DB -> PersistIntakeForm Complete";
    Mediator::Call(MKEY_DB_PERSIST_INTAKE_FORM_DONE, intake, success, errorMessage);
}

void DRCDB::PersistFruit(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Fruit* fruit = nullptr;       // Unpackaged argument
    if (success)
    {
        fruit = arg.getArg<Fruit*>();

        // SUCCESS!! INSERT CODE HERE
    }

    qDebug() << "DB -> PersistFruit Complete";
    Mediator::Call(MKEY_DB_PERSIST_FRUIT_NAME_DONE, fruit, success, errorMessage);
}

void DRCDB::LoadIntake(MediatorArg arg) const
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;       // Unpackaged argument
    if (success)
    {
        // Returning a test object... This should be deleted!!!
        intake = new Intake();
        intake->addClaimant("CLAIMENT DB TEST");
        intake->addRespondents("Respondent1");
        intake->addRespondents("Respondent2");
        intake->addRespondents("Respondent3");

        // SUCCESS!! INSERT CODE HERE
    }

    qDebug() << "DB -> PersistIntakeForm Complete";
    Mediator::Call(MKEY_DB_LOAD_INTAKE_FORM_DONE, intake, success, errorMessage);
}
