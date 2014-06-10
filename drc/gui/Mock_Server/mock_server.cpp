#include "mock_server.h"
#include <ctime>

Mock_Server::Mock_Server()
{
    Mediator::Register(MKEY_GUI_SEARCH_FOR_USERNAME, [this](MediatorArg arg){SendResults(arg); });
}
void Mock_Server::PrintPerson(Person *input, std::fstream &file)
{
    time_t tm = std::time(0);
    //std::time(&tm);
    file.open("test.out",std::fstream::out | std::fstream::app);
    if(file.is_open())
    {
        file << std::ctime(&tm) << std::endl;
        file << input->FullName().toUtf8().constData() <<std::endl;
        file << input->getState()<<std::endl<<std::endl;
        file << "------------------------------------------------------------------"<<std::endl<<std::endl;
        file.close();
    }
}

void Mock_Server::SendResults(MediatorArg Myarg)
{
    Person *recieved = Myarg.getArg<Person *>();
    std::fstream infile;
    PrintPerson(recieved, infile);
    for(int i = 0; i < 20; i++)
    {
        Person *temp = Person::SampleData();
        _personVector.push_back(temp);
    }
    Mediator::Call(MKEY_BL_RETURN_SEARCH_RESULTS,&_personVector);
}
