#include "drcdb.h"
#include <QtSql/QtSql>
#include "Fruit.h"    // temp.. not sure why it's having circular dependency.

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


QString DRCDB::GetDatabaseName()
{
    return database.databaseName();
}

bool DRCDB::OpenDatabase(QString database_name)
{
    database = QSqlDatabase::addDatabase(db_driver);
    database.setDatabaseName(database_name);
    return database.open();
}

QString DRCDB::WhatDriver()
{
    return database.driverName();
}

bool DRCDB::CloseDatabase()
{
    database.close();
    return database.isOpen();
}


//DRCDB::DRCDB(QString database_name) : db_name(database_name), DB_ERROR(false)
//{
//}

//bool DRCDB::OpenDatabase()
//{
//    bool open_success = false;
//    if (this->WhatDriver() == QString(""))
//    {
//        database =  QSqlDatabase::addDatabase("QSQLITE");
//    }
//    database.setDatabaseName(db_name);
//    if (database.open())
//        open_success = true;

//    return open_success;
//}

//void DRCDB::CloseDatabase()
//{
//    database.close();
//    database.removeDatabase(QString());
//}

//QString DRCDB::WhatDriver()
//{
//    return database.driverName();
//}

//QString DRCDB::WhatDatabase()
//{
//    return QSqlDatabase::databaseName();
//}

//bool DRCDB::isError()
//{
//    return database.isOpenError();
//}

//bool DRCDB::isOpen()
//{
//    return database.isOpen();
//}

//string DRCDB::errorMessage()
//{
//    return database.lastError().text().toStdString();
//}

//bool DRCDB::CreateTable(QString table_name, QString table_columns)
//{
//    bool create_success = false;

//    if (database.isOpen())
//    {
//        QSqlQuery query_object;
//        create_success = query_object.exec(QString("CREATE TABLE %1 (%2)").arg(table_name).arg(table_columns));
//    }

//    return create_success;
//}

//void DRCDB::InsertObject(DBBaseObject* db_object)
//{
//    if(database.isOpen())
//    {
//        QSqlQuery qObject;

//        QString qCmd;
//        string cmd("insert into Albertsons");
//        cmd += db_object->Parse();
//        qCmd.fromStdString(cmd);

//        qObject.exec(qCmd);
//    }
//}

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
