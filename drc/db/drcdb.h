#ifndef DRCDB_H
#define DRCDB_H
#include "Mediator.h"

//#include "sqlite3.h"

#include "DBBaseObject.h"
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
	
	void OpenDatabase(std::string database_name);

    void InsertObject(DBBaseObject* db_object);
	
    void InsertFruit(int time, std::string name);

    void InsertString(std::string Command);

    std::vector<std::string> *SelectAllField();

	bool isError();

	std::string errorMessage();


    // Incoming Events
    void PersistIntakeForm(MediatorArg arg) const;

    void PersistFruit(MediatorArg arg);

    void LoadIntake(MediatorArg arg) const;

    void LoadFruit(MediatorArg arg);

};

#endif // DRCDB_H
