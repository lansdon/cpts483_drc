#ifndef MOCK_SERVER_H
#define MOCK_SERVER_H

#include "Person.h"
#include "mediator/AsyncMediatorCall.h"
#include "mediator/Mediator.h"
#include "mediationprocess.h"
#include <fstream>
#include <vector>

/*!
 * \brief The Mock_Server class
 */
class Mock_Server
{
private:
    std::vector<Person *> _personVector;
    std::vector<MediationProcess *> _mediationProcessVector;
    /*!
     * \brief SendResults
     * \param Myarg
     */
    void SendResults(MediatorArg Myarg);
    /*!
     * \brief PrintPerson
     * \param input
     * \param file
     */
    void PrintPerson(Person *input, std::fstream &file);
    /*!
     * \brief PrintMediationProcess
     * \param input
     * \param file
     */
    void PrintMediationProcess(MediationProcess *input, std::fstream &file);
    /*!
     * \brief SendResultsMediation
     * \param arg
     */
    void SendResultsMediation(MediatorArg arg);
    MediatorId _unregQueryPersonCall;
public:
    Mock_Server();
    ~Mock_Server();
};

#endif // MOCK_SERVER_H
