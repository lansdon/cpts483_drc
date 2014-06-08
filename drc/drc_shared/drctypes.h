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
    DISPUTE_T_NONE

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
    REFERRAL_T_NONE

    // TO DO - FILL THIS IN
};

enum PartyTypes
{
    PARTY_T_NONE,
    PARTY_T_FIRST,
    PARTY_T_SECOND
};

enum UserTypes
{
    USER_T_NONE,        // 0
    USER_T_SUPER_USER,
    USER_T_ADMIN,
    USER_T_NORMAL
};

#endif // DRCTYPES_H
