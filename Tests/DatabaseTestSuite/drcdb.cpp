#include "drcdb.h"
#include <QtSql/QtSql>
#include <QDebug>

using std::string;
using std::vector;

#define db_driver "QSQLITE"

DRCDB::DRCDB()
{
}

DRCDB::DRCDB(QString database_name)
{
    this->OpenDatabase(database_name);
}

bool DRCDB::OpenDatabase(QString database_name)
{
    database = QSqlDatabase::addDatabase(db_driver);
    database.setDatabaseName(database_name);

    this->DebugDisplay(QString("Database Name: %1\nDatabase Driver: %2")
                       .arg(database_name)
                       .arg(this->WhatDriver()));

    return database.open();
}

bool DRCDB::CloseDatabase()
{
    database.close();
    return database.isOpen();
}

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

    return this->ExecuteCommand(command_string);
}


bool DRCDB::InsertObject(DBBaseObject* db_object)
{
    QString command_string = QString("insert into %1 values ( %2 , %3 )")
            .arg(db_object->table())
            .arg(db_object->Parse())
            .arg("null");

    return this->ExecuteCommand(command_string);
}

bool DRCDB::ExecuteCommand(QString command_string)
{
    QSqlQuery query_object(database);

    this->DebugDisplay(command_string);

    if (!query_object.prepare(command_string))

        this->WhatLastError(query_object);
    return query_object.exec();
}

//Methods below this line are necessarily vital, but are helpful for testing.
//=======================================================================================================

void DRCDB::DebugDisplay(QString error_message, bool active)
{
    if (active)
    {
        qDebug() << "\n" << error_message;
    }
}

QString DRCDB::GetDatabaseName()
{
    return database.databaseName();
}

//The driver is the SQL driver being used by the program.
//In our case, the driver we're using is called "QSQLITE",
//which is the sqlite3 driver for Qt.
QString DRCDB::WhatDriver()
{
    return database.driverName();
}

//Code could be written in one line; however, the return value isn't
//what you'd expect these kind of methods to return.  By explictly
//stating the return type, those who read this code later will have
//a better idea of what's going on as opposed to spending time sifting
//through additional documentation.
bool DRCDB::CheckTableExists(QString table_name)
{
    QStringList table_list = database.tables();

    return table_list.contains(table_name);
}

void DRCDB::WhatLastError(const QSqlQuery &query_object)
{
    qDebug() << "\n" << query_object.lastError();
}

//Query object can be implicitly initialized without passing
//the QSQLDatabase object to the constructor.  However, it is
//slightly more obvious as to where it's getting its information.

//Prepare checks the potential SQL command for validity.  While it seems
//tedious, it apparently is more efficient than letting an erroneous
//command be executed directly.


//vector<string>* DRCDB::SelectAllField()
//{
//    vector<string>* empty = new vector<string>();

//    if(database.isOpen())
//    {
//        QSqlQuery query;
//        query.exec("select * from Albertsons");

//        while(query.next())
//        {
//            string name(query.value(1).toString().toStdString());
//            string time(query.value(0).toString().toStdString());
//            empty->push_back(name);
//            empty->push_back(time);
//        }
//    }


//    return empty;

//}
