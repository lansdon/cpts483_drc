#ifndef CLIENTSESSIONDATA_H
#define CLIENTSESSIONDATA_H

#include <QString>

#include "DBBaseObject.h"

class ClientSessionData : public QObject, public DBBaseObject
{
public:
    ClientSessionData();

    // getters
    QString getIncome() const { return income; }
    QString getFee() const { return fee; }
    bool getPaid() const { return paid; }
    bool getAttySaidAttend() const { return attySaidAttend; }
    bool getAttyDidAttend() const { return attyDidAttend; }
    uint getSupport() const { return support; }

    // setters
    void setIncome(QString value) { income = value; }
    void setFee(QString value) { fee = value; }
    void setPaid(bool value) { paid = value; }
    void setAttySaidAttend(bool value) { attySaidAttend = value; }
    void setAttyDidAttend(bool value) { attyDidAttend = value; }
    void setSupport(uint value) { support = value; }

    //Virtual overrides
    QString Parse();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();
    QString GetIdRowName();

    //helpers
    bool isPaid() const;
    bool isNoFee() const;

public slots:
    void on_atty_will_attend(bool value);
    void on_atty_did_attend(bool value);
    void on_support(uint value);
private:
    QString income, fee;
    bool paid, attySaidAttend, attyDidAttend;
    uint support;
};

#endif // CLIENTSESSIONDATA_H
