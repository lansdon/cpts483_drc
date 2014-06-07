#ifndef DRCDB_H
#define DRCDB_H

#include <QString>
#include <QVector>
#include <QtSql/QtSql>

class DRCDB
{
private:
    QSqlDatabase database;

public:
    DRCDB();

    DRCDB(QString database_name);

    QString GetDatabaseName();

    bool OpenDatabase(QString database_name);

    QString WhatDriver();

    bool CloseDatabase();

    bool CheckTableExists(QString table_name);

    bool CreateTable(QString table_name, QVector<QString> column_data);

    QString WhatLastError();
};

//private:
//    QSqlDatabase database;

//    QString db_name;

//    bool DB_ERROR;

//    bool CreateTable(QString table_name, QString table_columns);

//public:

//    DRCDB();

//    bool OpenDatabase(QString database_name);

//    QString WhatDatabase();

//    QString WhatDriver();

//    void InsertFruit(int time, std::string name);

//    void InsertString(std::string Command);

//    std::vector<std::string> *SelectAllField();

//	bool isError();

//    bool isOpen();

//	std::string errorMessage();

//    void CloseDatabase();
#endif // DRCDB_H
