#ifndef DRCTYPES_H
#define DRCTYPES_H

#include <vector>
#include <QString>

//////////////////////////////////////////////
// This file contains commonly used enums etc
//////////////////////////////////////////////

class Person;
class MediationProcess;
class MediationSession;
class Party;
class Note;

// Typedefs
typedef std::vector<Person*> PersonVector;
typedef std::vector<MediationProcess*> MediationProcessVector;
typedef std::vector<MediationSession*> MediationSessionVector;
typedef std::vector<Party*> PartyVector;
typedef std::vector<Note*> MediationNotesVector;



// ENUMS FOREVAH

enum DisputeTypes
{
    DISPUTE_T_NONE,
    DISPUTE_T_PARENTING_PLAN,
    DISPUTE_T_DIVORCE,
    DISPUTE_T_SMALL_CLAIMS,
    DISPUTE_T_TENANT,
    DISPUTE_T_LANDLORD,
    DISPUTE_T_CONSUMER_MERCHANT,
    DISPUTE_T_WORKPLACE,
    DISPUTE_T_NEIGHBORHOOD,
    DISPUTE_T_FAMILY,
    DISPUTE_T_PROPERTY_BUSINESS,
    DISPUTE_T_PARENT_TEEN,
    DISPUTE_T_VICTIM_OFFENDER,
    DISPUTE_T_OTHER
};

enum DisputeProcessStates
{
    PROCESS_STATE_NONE,
    PROCESS_STATE_INITIATED,
    PROCESS_STATE_READY_TO_SCHEDULE,
    PROCESS_STATE_SCHEDULED,
    PROCESS_STATE_OUTCOME_REACHED,
    PROCESS_STATE_OUTCOME_NOT_REACHED
};

enum CountyIds
{
    COUNTY_NONE,
    COUNTY_BENTON,
    COUNTY_FRANLKIN,
    COUNTY_GRANT,
    COUNTY_ADAMS,
    COUNTY_OTHER
};


enum ReferralTypes
{
    REFERRAL_T_NONE,
    REFERRAL_T_FAMILY_FRIEND,
    REFERRAL_T_ATTORNEY,
    REFERRAL_T_LEGAL_SERVICES,
    REFERRAL_T_RETURN_CLIENTS,
    REFERRAL_T_PRIVATE_AGENCY,
    REFERRAL_T_COURTS,
    REFERRAL_T_COURT_SOLICITED,
    REFERRAL_T_LAW_ENFORCEMENT,
    REFERRAL_T_DCFS_JJC_GOVT_AGENCY,
    REFERRAL_T_ATTORNEY_GENERALS_OFFICE,
    REFERRAL_T_PRESENTATION_TRAINING,
    REFERRAL_T_ADVERTISING,
    REFERRAL_T_PHONEBOOK,
    REFERRAL_T_INTERNET,
    REFERRAL_T_OTHER_NONE
};

enum PartyTypes
{
    PARTY_T_NONE,
    PARTY_T_FIRST,
    PARTY_T_SECOND
};

enum UserTypes
{
    USER_T_ADMIN,
    USER_T_NORMAL
};

enum SearchTypes
{
    SEARCH_T_NONE,
    SEARCH_T_PERSON,
    SEARCH_T_MEDIATION,
    SEARCH_T_CALL_LOG
};

enum MediationTableSortTypes
{
    MEDIATION_SORT_T_NONE,
    MEDIATION_SORT_T_PENDING,
    MEDIATION_SORT_T_RECENT,
    MEDIATION_SORT_T_SCHEDULED,
    MEDIATION_SORT_T_CLOSED
};

enum SessionStates
{
    SESSION_STATE_NONE,
    SESSION_STATE_PENDING,
    SESSION_STATE_CONFIRMED,
    SESSION_STATE_CANCELLED,
    SESSION_STATE_RESCHEDULED
};

// String Helpers
QString StringForCountyIds(CountyIds id);
QString StringForDisputeProcessStates(DisputeProcessStates id);
QString StringForDisputeTypes(DisputeTypes id);
QString StringForReferralTypes(ReferralTypes id);
QString StringForPartyTypes(PartyTypes id);
QString StringForUserTypes(UserTypes id);
QString StringForSearchTypes(SearchTypes id);
QString StringForSessionStates(SessionStates id);



#endif // DRCTYPES_H
