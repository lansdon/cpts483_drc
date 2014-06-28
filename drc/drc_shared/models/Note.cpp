#include "Note.h"

Note::Note(QString message)
: DBBaseObject()
, _message(message)
, _sessionId(-1)
, _mediationId(-1)
{

}

void Note::SetMessage(QString message)
{
    _message = message;
}

void Note::SetSessionId(int sessionId)
{
    _sessionId = sessionId;
}

void Note::SetMediationId(int mediationId)
{
    _mediationId = mediationId;
}

QString Note::GetMessage()
{
    return _message;
}

int Note::GetmediationId()
{
    return _mediationId;
}

int Note::GetSessionId()
{
    return _sessionId;
}

// Abstract Overrides
QString Note::Parse()
{
#warning TODO - PARSE UNIMPLEMENTED!!!!

}

QString Note::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!

}

QString Note::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!

}

QString Note::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!
}
