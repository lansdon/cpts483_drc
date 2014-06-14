#include "drcdb.h"
#include <QtSql/QtSql>
#include "Mediator.h"
#include "MediatorKeys.h"
#include "DRCModels.h"
#include "Fruit.h"    // temp.. not sure why it's having circular dependency.

using std::string;
using std::vector;


DRCDB::DRCDB() : DB_ERROR(false)
{
    OpenDatabase("../drc/drc_db.db3");

    CreateTable("Albertsons", "TIME_STAMP integer PRIMARY KEY NOT NULL, FRUIT_NAME varchar(50)");

    // Register to Listen for events.
    Mediator::Register(MKEY_BL_VALIDATE_FRUITNAME_DONE, [this](MediatorArg arg){PersistFruit(arg);});
    Mediator::Register(MKEY_DB_PERSIST_FRUIT_NAME_DONE, [this](MediatorArg arg){LoadFruit(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){LoadIntake(arg);});
    Mediator::Register(MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE, [this](MediatorArg arg){PersistIntakeForm(arg);});
}

void DRCDB::OpenDatabase(string database_name)
{
    database =  QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString::fromStdString(database_name));
    DB_ERROR = database.open();
    if(!DB_ERROR)
    {
        //Success
        qDebug()<<"Database creation success";
    }
    else qDebug() << "Database creation FAILBOT";

}

bool DRCDB::isError()
{
    return DB_ERROR;
}

string DRCDB::errorMessage()
{
    return database.lastError().text().toStdString();
}

bool DRCDB::CreateTable(QString table_name, QString table_columns)
{
    bool create_success = false;

    if (database.isOpen())
    {
        QSqlQuery query_object;
        create_success = query_object.exec(QString("CREATE TABLE %1 (%2)").arg(table_name).arg(table_columns));
    }

    return create_success;
}

void DRCDB::InsertObject(DBBaseObject* db_object)
{
    bool insertSuccess;
    if(database.isOpen())
    {
        QSqlQuery qObject;

        QString cmd("insert into Albertsons");
        cmd += db_object->Parse();

        insertSuccess = qObject.exec(cmd);
    }
}

void DRCDB::InsertFruit(int time, string name)
{
    QSqlQuery qObject;
    bool insertSuccess = false;
    QString qName = QString::fromUtf8(name.c_str());
    if(database.isOpen())
    {
        insertSuccess = qObject.exec(QString("insert into Albertsons values(%1, '%2')").arg(time).arg(qName));
    }
}

void DRCDB::InsertString(string Command)
{
    QSqlQuery qObject;
    bool insertSuccess = false;

    if(database.isOpen())
    {
        QString qCmd, data;

        string cmd = "insert into Albertsons ";
        cmd = cmd + Command;

        qCmd.fromStdString(cmd);

        insertSuccess = qObject.exec(qCmd);
    }
}

vector<string>* DRCDB::SelectAllField()
{
    vector<string>* empty = new vector<string>();

    QSqlQuery query;
    bool searchSuccess;

    if(database.isOpen())
    {
        searchSuccess = query.exec("select * from Albertsons");
    }
    while(query.next())
    {
        string name(query.value(1).toString().toStdString());
        string time(query.value(0).toString().toStdString());
        empty->push_back(name);
        empty->push_back(time);
    }


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

void DRCDB::PersistFruit(MediatorArg arg)
{
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Fruit* fruit = nullptr;       // Unpackaged argument
    if (success)
    {
        fruit = arg.getArg<Fruit*>();

        InsertObject(fruit);
    }

    qDebug() << "DB -> PersistFruit Complete";
    Mediator::Call(MKEY_DB_PERSIST_FRUIT_NAME_DONE, fruit, success, errorMessage);
}

void DRCDB::LoadFruit(MediatorArg arg)
{
    vector<string>* results = new vector<string>();
    results = SelectAllField();
    qDebug() << "Data stored in database; name then timestamp\n";
    for(int i = 0; i < results->size(); i++)
    {
        qDebug() << results->at(i).c_str() << endl;
    }
    qDebug() << "DB -> LoadFruit Complete";
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
        intake->addClaimant(Person("CLAIMENT DB TEST"));
        intake->addRespondents(Person("Respondent1"));
        intake->addRespondents(Person("Respondent2"));
        intake->addRespondents(Person("Respondent3"));

        // SUCCESS!! INSERT CODE HERE
    }

    qDebug() << "DB -> PersistIntakeForm Complete";
    Mediator::Call(MKEY_DB_LOAD_INTAKE_FORM_DONE, intake, success, errorMessage);
}
