#include "intakeformprocessor.h"
#include "Mediator.h"
#include "personvalidator.h"


#include <qstring.h>
#include <qdebug.h>

#include <regex>

IntakeFormProcessor::IntakeFormProcessor(std::string regProcess, std::string sendProcess,
                    std::string regLoad,    std::string sendLoad)
                    : _regProcess(regProcess), _sendProcess(sendProcess),
                      _regLoad(regLoad), _sendLoad(sendLoad)
{
      if (_regProcess != "")    Mediator::Register(_regProcess, [this](MediatorArg arg){ Process(arg); });
      if (_regProcess != "")    Mediator::Register(_regLoad, [this](MediatorArg arg){ Load(arg); });
}

void IntakeFormProcessor::Process(MediatorArg arg)
{
    qDebug() << "BL -> Processing Intake Form.";
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;
    if (success)
    {
        intake = arg.getArg<Intake*>();
        success = ValidateIntakeForm(intake, errorMessage);
    }

    qDebug() << "BL -> "+ QString::fromStdString(_regProcess) +" Complete";
    Mediator::Call(_sendProcess, intake, success, errorMessage);
}

void IntakeFormProcessor::Load(MediatorArg arg)
{
    qDebug() << "BL -> Loading Intake Form.";
    bool success = arg.IsSuccessful();
    std::string errorMessage = arg.ErrorMessage();

    Intake* intake = nullptr;
    if (success)
    {
        intake = arg.getArg<Intake*>();
        success = ValidateIntakeForm(intake, errorMessage);
    }

    qDebug() << "BL -> "+ QString::fromStdString(_regLoad) +" Complete";
    Mediator::Call(_sendLoad, intake, success, errorMessage);
}

bool IntakeFormProcessor::ValidateIntakeForm(Intake* intake, std::string& errorMessage) const
{
    qDebug() << "BL -> Validate Intake Form";
    bool success = true;
    if (intake)
    {
        auto persons = intake->getParties();
        auto time = intake->getTime();
        PersonValidator pVal;
        for (unsigned int i = 0; i < persons.size(); i++)
        {
            success &= pVal.Validate(persons[i], errorMessage);
            if (!success) break;
        }
        success &= ValidateTime(time, errorMessage);
    }
    else
    {
        errorMessage = "Null intake form received.";
        success = false;
    }
    return success;
}

bool IntakeFormProcessor::ValidateTime(time_t time, std::string& errorMessage) const
{
    qDebug() << "BL -> Validate time";
    bool success = true;
    if (time < 0)
    {
        errorMessage = "Invalid time. Time must be positive.";
        success = false;
    }
    return success;
}
