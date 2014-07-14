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
class ClientSessionData;
class MediationEvaluation;

// Typedefs
typedef std::vector<Person*> PersonVector;
typedef std::vector<MediationProcess*> MediationProcessVector;
typedef std::vector<MediationSession*> MediationSessionVector;
typedef std::vector<Party*> PartyVector;
typedef std::vector<Note*> MediationNotesVector;
typedef std::vector<ClientSessionData*> ClientSessionDataVector;
typedef std::vector<MediationEvaluation*> MediationEvaluationVector;


// ENUMS FOREVAH

enum EvaluationAnswers
{
    EVALUATION_ANSWERS_NO_ANSWER,
    EVALUATION_ANSWERS_YES,
    EVALUATION_ANSWERS_NO,
    EVALUATION_ANSWERS_SOMEWHAT
};

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

enum DisputeProcessInternalStates
{
    PROCESS_INTERNAL_STATE_NONE,
    PROCESS_INTERNAL_STATE_INITIATED,
    PROCESS_INTERNAL_STATE_READY_TO_SCHEDULE,
    PROCESS_INTERNAL_STATE_SCHEDULED,
    PROCESS_INTERNAL_STATE_MEDIATION_COMPLETED,
    PROCESS_INTERNAL_STATE_OUTCOME_REACHED,
    PROCESS_INTERNAL_STATE_OUTCOME_NOT_REACHED
};

enum DisputeProcessStates
{
    PROCESS_STATE_NONE,
    PROCESS_STATE_PENDING,
    PROCESS_STATE_SCHEDULED,
    PROCESS_STATE_CLOSED_WITH_SESSION,
    PROCESS_STATE_CLOSED_NO_SESSION
};

enum InquiryTypes
{
    INQUIRY_T_NONE,
    INQUIRY_T_PHONE,
    INQUIRY_T_EMAIL,
    INQUIRY_T_WALKIN,
    INQUIRY_T_REFERRAL
};

enum SessionOutcomes
{
    SESSION_OUTCOME_NONE,
    SESSION_OUTCOME_FIRST_PARTY_WITHDREW,
    SESSION_OUTCOME_SECOND_PARTY_DECLINES,
    SESSION_OUTCOME_AGREEMENT,
    SESSION_OUTCOME_NO_AGREEMENT,
    SESSION_OUTCOME_PROBLEM_SOLVING,
    SESSION_OUTCOME_REFERRED_OUT,
    SESSION_OUTCOME_CANNOT_REACH_PARTIES,
    SESSION_OUTCOME_SELF_RESOLVED,
};

enum CountyIds
{
    COUNTY_NONE,
    COUNTY_BENTON,
    COUNTY_FRANLKIN,
    COUNTY_GRANT,
    COUNTY_ADAMS,
    COUNTY_OTHER,
    COUNTY_WALLAWALLA
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
    USER_T_NORMAL,
    USER_T_ADMIN
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

enum CourtCaseTypes
{
    COURT_T_NONE,
    COURT_T_SUPERIOR,
    COURT_T_JUVENILE,
    COURT_T_SMALL_CLAIMS,
    COURT_T_OTHER
};

enum CourtOrderTypes
{
    COURT_ORDER_T_NONE
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
QString StringForInquiryTypes(InquiryTypes id);
QString StringForCourtTypes(CourtCaseTypes id);
QString StringForCourtOrderTypes(CourtOrderTypes id);
QString StringForSessionOutcomes(SessionOutcomes id);
QString StringForEvaluationAnswers(EvaluationAnswers id);



#endif // DRCTYPES_H
