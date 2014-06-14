#include "intakeformprocessor.h"
#include "../drc_shared/mediator/Mediator.h"

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
        success = ValidateIntakeForm(*intake, errorMessage);
    }

    qDebug() << "BL -> ValidateSaveIntakeRequest Complete";
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
        success = ValidateIntakeForm(*intake, errorMessage);
    }

    qDebug() << "BL -> ValidateLoadIntakeRequest Complete";
    Mediator::Call(_sendLoad, intake, success, errorMessage);
}

bool IntakeFormProcessor::ValidateIntakeForm(const Intake& intake, std::string& errorMessage) const
{
    qDebug() << "BL -> Validate Intake Form";
    bool success = true;
    auto persons = intake.getParties();
    auto claimant = intake.getClaimant();
    auto time = intake.getTime();
    success &= ValidatePerson(claimant, errorMessage);
    for (unsigned int i = 0; i < persons.size(); i++)
    {
        success &= ValidatePerson(*persons[i], errorMessage);
        if (!success) break;
    }
    success &= ValidateTime(time, errorMessage);
    return success;
}

bool IntakeFormProcessor::ValidatePerson(const Person& person, std::string& errorMessage) const
{
    qDebug() << "BL -> Validate Person "+ person.getFirstName();
    bool success = true;
    std::string pattern = "^[a-zA-Z]+$";
    auto name = person.getFirstName();
//    success = std::regex_match(name, std::regex(pattern));
    if (name.size() == 0)
    {
        success = false;
        errorMessage = "Empty person name.";
    }
    for (unsigned int i = 0; i < name.size(); i++)
    {
        if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || (name[i] == ' ')))
        {
            success = false;
            errorMessage = "Invalid character in person name.";
            break;
        }
    }
    if (!success)
    {
        errorMessage = "Person name contains invalid characters.";
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
