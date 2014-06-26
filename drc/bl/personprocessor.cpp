#include "personprocessor.h"
#include "personvalidator.h"
#include "Mediator.h"

#include <QDebug>
#include <QString>

PersonProcessor::PersonProcessor(QString regProcess, QString sendProcess,
                QString regLoad, QString sendLoad)
                : _regProcess(regProcess), _sendProcess(sendProcess), _regLoad(regLoad),
                  _sendLoad(sendLoad)
{
    if (_regProcess != "")    Mediator::Register(_regProcess, [this](MediatorArg arg){ Process(arg); });
    if (_regProcess != "")    Mediator::Register(_regLoad, [this](MediatorArg arg){ Load(arg); });
}

void PersonProcessor::Process(MediatorArg arg)
{
    qDebug() << "BL -> Processing Person.";
    bool success = arg.IsSuccessful();
    QString errorMessage = arg.ErrorMessage();

    Person* person = nullptr;
    if (success)
    {
        person = arg.getArg<Person*>();
        PersonValidator pVal;
        success = pVal.Validate(person, errorMessage);
    }

    qDebug() << "BL -> "+ _regProcess +" Complete";
    Mediator::Call(_sendProcess, person, success, errorMessage);
}

void PersonProcessor::Load(MediatorArg arg)
{
    qDebug() << "BL -> Loading Person.";
    bool success = arg.IsSuccessful();
    QString errorMessage = arg.ErrorMessage();

    Person* person = nullptr;
    if (success)
    {
        person = arg.getArg<Person*>();
        PersonValidator pVal;
        success = pVal.Validate(person, errorMessage);
    }

    qDebug() << "BL -> "+ _regLoad +" Complete";
    Mediator::Call(_sendLoad, person, success, errorMessage);
}
