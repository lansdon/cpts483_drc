#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include "Person.h"
#include "mediator/AsyncMediatorCall.h"
#include "mediator/Mediator.h"
#include <fstream>
#include <vector>

class Mock_Server
{
private:
    std::vector<Person *> _personVector;
    void SendResults(MediatorArg Myarg);
    void PrintPerson(Person *input, std::fstream &file);
public:
    Mock_Server();
};

#endif // MOCK_SERVER_H
