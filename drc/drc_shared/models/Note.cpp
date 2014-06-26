#include "Note.h"

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
