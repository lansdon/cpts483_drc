#ifndef DRCDB_H
#define DRCDB_H
#include "drc_shared/mediator/Mediator.h"

#include "sqlite3.h"
#include <string>
#include <vector>
#include <QtSql/QtSql>

//This is a rough draft of all the methods we may need for our database
//in the scope of the Fruit basket.  If you feel there are additions or
//revisions to be made, feel free to do so, but becareful of multiple
//hands digging into the same pie.
class DRCDB
{
private:
//	sqlite3 *database;
    QSqlDatabase database;
	bool DB_ERROR;

public:

    DRCDB();
    DRCDB(std::string database_name);
	
	void OpenDatabase(std::string database_name);
	
	void CreateTable(std::string table_name);
	
	//I believe there are commands to add columns to an existing
	//table which may help make the code cleaner.
	void AddColumn(std::string column_name, std::string column_type, std::string column_required, bool primary_key);
	

	void InsertField(std::string fruit_name, std::string time_stamp);


	std::vector<std::string> SelectAllField();


	bool isError();
	std::string errorMessage();


    // Incoming Events
    void PersistIntakeForm(MediatorArg arg) const;

    void PersistFruit(MediatorArg arg) const;

    void LoadIntake(MediatorArg arg) const;

};

#endif // DRCDB_H
