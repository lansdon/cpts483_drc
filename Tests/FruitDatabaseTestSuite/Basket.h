#ifndef BASKET_H
#define BASKET_H

#include "DBBaseObject.h"

class Basket : public DBBaseObject
{
private:
    int m_id;

    QString m_name;

public:

    Basket();

    Basket(QString name);

    Basket(QString *name);

    void SetID(int id);

    int GetID(void);

    void SetName(QString name);

    QString GetName(void);

    QString BreakApart(void);

    QString Parse(void);

    QString table(void);

    QString DuplicateQuery(void);

    QString SearchQuery(void);

};

#endif // BASKET_H
