#include "personprocessor.h"
#include "personvalidator.h"
#include "Mediator.h"

#include <QDebug>
#include <QString>

PersonProcessor::PersonProcessor(std::string regProcess, std::string sendProcess,
                std::string regLoad, std::string sendLoad)
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
    std::string errorMessage = arg.ErrorMessage();

    Person* person = nullptr;
    if (success)
    {
        person = arg.getArg<Person*>();
        PersonValidator pVal;
        success = pVal.Validate(person, errorMessage);
    }

    qDebug() << "BL -> "+ QString::fromStdString(_regProcess) +" Complete";
    Mediator::Call(_sendProcess, person, success, errorMessage);
}

void PersonProcessor::Load(MediatorArg arg)
{
    qDebug() << "BL -> Loading Person.";
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Person* person = nullptr;
    if (success)
    {
        person = arg.getArg<Person*>();
        PersonValidator pVal;
        success = pVal.Validate(person, errorMessage);
    }

    qDebug() << "BL -> "+ QString::fromStdString(_regLoad) +" Complete";
    Mediator::Call(_sendLoad, person, success, errorMessage);
}
