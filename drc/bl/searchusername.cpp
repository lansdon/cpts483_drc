#include "searchusername.h"
#include "../drc_shared/mediator/Mediator.h"

#include <qstring.h>
#include <qdebug.h>

SearchUserName::SearchUserName(std::string regProcess="", std::string sendProcess="",
                           std::string regLoad="", std::string sendLoad="")
              : _regProcess(regProcess), _sendProcess(sendProcess),
                _regLoad(regLoad), _sendLoad(sendLoad)
{
    if (_regProcess != "")    Mediator::Register(_regProcess, [this](MediatorArg arg){ Process(arg); });
    if (_regProcess != "")   Mediator::Register(_regLoad, [this](MediatorArg arg){ Load(arg); });
}

void SearchUserName::Process(MediatorArg arg)
{

}

void SearchUserName::Load(MediatorArg arg)
{

}
