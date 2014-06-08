#ifndef DRCTYPES_H
#define DRCTYPES_H

#include <vector>

//////////////////////////////////////////////
// This file contains commonly used enums etc
//////////////////////////////////////////////

class Person;
typedef std::vector<Person*> PersonVector;

enum DisputeTypes
{
    DISPUTE_TYPE_NONE

    // TO DO FILL THIS IN!!!!
};

enum DisputeProcessStates
{
    PROCESS_STATE_NONE

    // TO DO - FILL THIS IN!!!
};

enum CountyIds
{
    COUNTY_NONE,
    COUNTY_BENTON,
    COUNTY_FRANLKIN
};

enum ReferralTypes
{
    REFERRAL_TYPE_NONE

    // TO DO - FILL THIS IN
};

enum PartyTypes
{
    PARTY_TYPE_NONE,
    PARTY_TYPE_FIRST,
    PARTY_TYPE_SECOND
};


#endif // DRCTYPES_H
