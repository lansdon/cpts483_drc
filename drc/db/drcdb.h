#ifndef DRCDB_H
#define DRCDB_H
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QFile>

class DRCDB
{
private:
    QSqlDatabase db;
public:
    DRCDB(QObject *parent = 0);
    ~DRCDB();
public:
    bool openDB();
    bool deleteDB();
    QSqlError lastError();
};

#endif // DRCDB_H
