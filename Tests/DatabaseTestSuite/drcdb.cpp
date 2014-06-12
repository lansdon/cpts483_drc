#include "drcdb.h"
#include <QtSql/QtSql>
#include <QDebug>

using std::string;
using std::vector;

#define db_driver "QSQLITE"

DRCDB::DRCDB()
{

}

//========================================================================
//Constructor takes in a database_name, and opens it.
//------------------------------------------------------------------------
DRCDB::DRCDB(QString database_name)
{
    this->OpenDatabase(database_name);
}
//========================================================================



//========================================================================
//It first sets the driver that our database will be using (in this case,
//"QSQLITE", which is the driver for sqlite3.  It'll then set the name of
//the database file to the QString that was passed to this method.

//Lastly, after everything has been set on the database object, we attempt
//to open a database; the result of that will be returned as a boolean.
//True:     Open
//False:    Failed to Open
//------------------------------------------------------------------------
bool DRCDB::OpenDatabase(QString database_name)
{
    database = QSqlDatabase::addDatabase(db_driver);
    database.setDatabaseName(database_name);

    this->DebugDisplay(QString("Database Name: %1\nDatabase Driver: %2")
                       .arg(database_name)
                       .arg(this->WhatDriver()));

    return database.open();
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
//Consolidates a command_string with all the individual elements from the
//QVector that will make up the columns of this new table.

//Lastly we use the ExecuteCommand method of our database class to generate
//the tables, and returns a boolean indicating whether or not it was successful.
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

    return this->ExecuteCommand(command_string);
}
//========================================================================



//========================================================================
//Takes a generic Database object, and parses a valid command_string.
//This string is then sent to our ExecuteCommand method of our database
//class to insert the values of the object.
//------------------------------------------------------------------------
bool DRCDB::InsertObject(DBBaseObject* db_object)
{
    bool insert_success = false;

    if (!this->DuplicateInsert(db_object))
    {
        QString command_string = QString("insert into %1 values ( %2 , %3 )")
                .arg(db_object->table())
                .arg("null")
                .arg(db_object->Parse());
        insert_success = this->ExecuteCommand(command_string);
    }

    return insert_success;

}
//========================================================================



//========================================================================
//A simple query to determine whether or not a similar name already exists
//inside the database.

//Note: It seems QSqlQuery.size() is not compatible with SQLITE3, which
//      resulted in my using QSqlQuery.next() instead.

//Note: Focused on getting this damn thing to work, so it's sloppy.

//Note: This method has no extensibility whatsoever.  The moment even
//      "one" thing changes, we're doomed.  That's it.  Done.  Kaput.
//------------------------------------------------------------------------
bool DRCDB::DuplicateInsert(DBBaseObject* db_object)
{
    bool duplicate_exists = false;

    QSqlQuery query_object(database);
    query_object.prepare(QString("select count(1) from %1 where fruit_name = \'%2\'")
                         .arg(db_object->table()).arg(db_object->GetName()));
    query_object.exec();

    //Lazy implementation.
    if (query_object.next() && query_object.value(0).toInt() == 1)
    {
        duplicate_exists = true;
    }

    return duplicate_exists;
}

//========================================================================

//========================================================================
//Query object can be implicitly initialized without passing
//the QSQLDatabase object to the constructor.  However, it is
//slightly more obvious as to where it's getting its information.

//Prepare checks the potential SQL command for validity.  While it seems
//tedious, it apparently is more efficient than letting an erroneous
//command be executed directly.
//------------------------------------------------------------------------
bool DRCDB::ExecuteCommand(QString command_string)
{
    QSqlQuery query_object(database);

    this->DebugDisplay(command_string);

    if (!query_object.prepare(command_string))
        this->WhatLastError(query_object);

    return query_object.exec();
}
//========================================================================



//========================================================================
//A simple query that returns all values currently contained within the
//table indicated.

//Unlike previous database methods, this method is unable to use the
//ExecuteCommand method due to the fact that it needs to return an object
//as opposed to a simple boolean.  In this case, an empty object represents
//a failed attempt to return anything from the database.
//QVector.count > 0:        Success
//QVector.count == 0:       Failure
//------------------------------------------------------------------------
QVector<QString> DRCDB::SelectAllFields(QString table_name)
{
    QVector<QString> return_vec;

    QString command_string = QString("select * from %1")
            .arg(table_name);

    QSqlQuery query_object(database);
    query_object.prepare(command_string);
    query_object.exec();

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
//Methods below this line are necessarily vital, but are helpful for testing.
//========================================================================

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
//bool DRCDB::CheckTableExists(QString table_name)
//{
//    QStringList table_list = database.tables();

//    return table_list.contains(table_name);
//}

void DRCDB::WhatLastError(const QSqlQuery &query_object)
{
    qDebug() << "\n" << query_object.lastError();
}
