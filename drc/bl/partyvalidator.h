#ifndef PARTYVALIDATOR_H
#define PARTYVALIDATOR_H

#include <QString>
#include "party.h"

class partyvalidator
{
public:
    partyvalidator();
    bool Validate(Party* party, std::string& errorMessage) const;

private:
    bool _validate;
};

#endif // PARTYVALIDATOR_H
