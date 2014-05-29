#include "drcdb.h"
using std::string;
using std::vector;

DATABASE::DATABASE() : DB_ERROR(false)
{
    OpenDatabase("");
}


DATABASE::DATABASE(string database_name) : DB_ERROR(false)
{
    OpenDatabase(database_name);
}

void DATABASE::OpenDatabase(string database_name)
{
    //sqlite3_open both creates and/or opens a database.
    int sql_result = sqlite3_open(database_name.c_str(), &database);

    if (sql_result)     //If result != 0, then database didn't open.
        DB_ERROR = true;
    else                //If result == 0, then database opened.
        DB_ERROR = false;
}

bool DATABASE::isError()
{
    return DB_ERROR;
}

string DATABASE::errorMessage()
{
    return string(sqlite3_errmsg(database));
}

void CreateTable(string table_name)
{

}

void AddColumn(string column_name, string column_type, string column_required, bool primary_key)
{

}

void InsertField(string fruit_name, string time_stamp)
{

}

vector<string> SelectAllField()
{
    return vector<string> empty;
}