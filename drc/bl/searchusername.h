#ifndef PROCESSLOGIN_H
#define PROCESSLOGIN_H

#include <string>
#include "Processor.h"

class SearchUserName : public Processor
{
public:
    SearchUserName(std::string regProcess, std::string sendProcess,
                   std::string regLoad,    std::string sendLoad);
    void Process(MediatorArg arg);
    void Load(MediatorArg arg);
private:
    std::string _regProcess;
    std::string _sendProcess;
    std::string _regLoad;
    std::string _sendLoad;
};

#endif // PROCESSLOGIN_H
