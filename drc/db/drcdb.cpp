#include "drcdb.h"
using std::string;

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

    if (result)     //If result != 0, then database didn't open.
        DB_ERROR = true;
    else            //If result == 0, then database opened.
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