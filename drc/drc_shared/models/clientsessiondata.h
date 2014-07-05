#ifndef CLIENTSESSIONDATA_H
#define CLIENTSESSIONDATA_H

#include <QString>

#include "DBBaseObject.h"

class ClientSessionData : public DBBaseObject
{
public:
    ClientSessionData();

    // getters
    QString getIncome() const { return income; }
    QString getFee() const { return fee; }
    bool getPaid() const { return paid; }
    bool getAttySaidAttend() const { return attySaidAttend; }
    bool getAttyDidAttend() const { return attyDidAttend; }

    // setters
    void setIncome(QString value) { income = value; }
    void setFee(QString value) { fee = value; }
    void setPaid(bool value) { paid = value; }
    void setAttySaidAttend(bool value) { attySaidAttend = value; }
    void setAttyDidAttend(bool value) { attyDidAttend = value; }

    //Virtual overrides
    QString Parse();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();

    QString GetIdRowName();
private:
    QString income, fee;
    bool paid, attySaidAttend, attyDidAttend;
};

#endif // CLIENTSESSIONDATA_H
