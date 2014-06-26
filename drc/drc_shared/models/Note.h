#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <iostream>
#include <stdio.h>
#include <string>

#include "DBBaseObject.h"

class Note: public DBBaseObject
{
private:
    QString _message;
    int _sessionId;
    int _mediationId ;
public:
    void SetMessage(QString message);
    void SetSessionId(int sessionId);
    void SetMediationId(int mediationId);

    QString GetMessage();
    int GetSessionId();
    int GetmediationId();
};

#endif // NOTEFORM_H
