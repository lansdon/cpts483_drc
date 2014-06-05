#ifndef DRCDB_H
#define DRCDB_H

#include <string>
#include <vector>
#include <QtSql/QtSql>

class DRCDB
{
private:
    QSqlDatabase database;

    bool DB_ERROR;

    bool CreateTable(QString table_name, QString table_columns);

public:

    DRCDB();
	
    bool OpenDatabase(QString database_name);

    QString WhatDatabase();

    QString WhatDriver();
	
    void InsertFruit(int time, std::string name);

    void InsertString(std::string Command);

    std::vector<std::string> *SelectAllField();

	bool isError();

    bool isOpen();

	std::string errorMessage();

    void CloseDatabase();

};

#endif // DRCDB_H
