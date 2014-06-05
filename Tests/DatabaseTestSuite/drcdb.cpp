#include "drcdb.h"
#include <QtSql/QtSql>
#include "Fruit.h"    // temp.. not sure why it's having circular dependency.

using std::string;
using std::vector;


DRCDB::DRCDB() : DB_ERROR(false)
{
}

bool DRCDB::OpenDatabase(QString database_name)
{
    bool open_success = false;
    if (this->WhatDriver() == QString(""))
    {
        database =  QSqlDatabase::addDatabase("QSQLITE");
    }
    database.setDatabaseName(database_name);
    if (database.open())
        open_success = true;

    return open_success;
}

void DRCDB::CloseDatabase()
{
    database.close();
}

QString DRCDB::WhatDriver()
{
    return database.driverName();
}

QString DRCDB::WhatDatabase()
{
    return QString("Albertsons");
}

bool DRCDB::isError()
{
    return DB_ERROR;
}

bool DRCDB::isOpen()
{
    return database.isOpen();
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

void DRCDB::InsertFruit(int time, string name)
{
    bool insertSuccess = false;

    QString qName = QString::fromUtf8(name.c_str());

    if(database.isOpen())
    {
        QSqlQuery qObject;
        insertSuccess = qObject.exec(QString("insert into Albertsons values(%1, '%2')").arg(time).arg(qName));
    }
}

void DRCDB::InsertString(string Command)
{
    bool insertSuccess = false;

    if(database.isOpen())
    {
        QSqlQuery qObject;

        QString qCmd, data;

        string cmd = "insert into Albertsons ";
        cmd = cmd + Command;

        qCmd.fromStdString(cmd);

        insertSuccess = qObject.exec(qCmd);
        //insertSuccess = qObject.exec("insert into Albertsons values(100, 'apple')");
    }
}

vector<string>* DRCDB::SelectAllField()
{
    vector<string>* empty = new vector<string>();

    if(database.isOpen())
    {
        QSqlQuery query;
        query.exec("select * from Albertsons");

        while(query.next())
        {
            string name(query.value(1).toString().toStdString());
            string time(query.value(0).toString().toStdString());
            empty->push_back(name);
            empty->push_back(time);
        }
    }


    return empty;

}
