#include "clientsessiondata.h"

ClientSessionData::ClientSessionData()
{
    paid = attyDidAttend = attySaidAttend = false;
    support = 0;
}

QString ClientSessionData::Parse()
{
#warning TODO - Parse() UNIMPLEMENTED!!!!
    return "";
}

QString ClientSessionData::UpdateParse()
{
#warning TODO - UpdateParse() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
    return "";

}

QString ClientSessionData::GetIdRowName()
{
#warning TODO - GetIdRowName() UNIMPLEMENTED!!!!
    return "";

}

void ClientSessionData::on_atty_will_attend(bool value)
{
    setAttySaidAttend(value);
}

void ClientSessionData::on_atty_did_attend(bool value)
{
    setAttyDidAttend(value);
}

void ClientSessionData::on_support(uint value)
{
    setSupport(value);
}
