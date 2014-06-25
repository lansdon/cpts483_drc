#include "drctypes.h"




// String Helpers
QString StringForCountyIds(CountyIds id)
{
    QString result;
    switch(id)
    {
    case COUNTY_ADAMS: result = "Adams County"; break;
    case COUNTY_BENTON: result = "Benton County"; break;
    case COUNTY_FRANLKIN: result = "Franklin County"; break;
    case COUNTY_GRANT: result = "Grant County"; break;
    case COUNTY_OTHER: result = "Other"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForDisputeProcessStates(DisputeProcessStates id)
{
    QString result;
    switch(id)
    {
    case PROCESS_STATE_INITIATED: result = "Initiated"; break;
    case PROCESS_STATE_NONE: result = "None"; break;
    case PROCESS_STATE_OUTCOME_NOT_REACHED: result = "Outcome Not Reached"; break;
    case PROCESS_STATE_OUTCOME_REACHED: result = "Outcome Reached"; break;
    case PROCESS_STATE_SCHEDULED: result = "Scheduled"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForDisputeTypes(DisputeTypes id)
{
    QString result;
    switch(id)
    {
    case DISPUTE_T_CONSUMER_MERCHANT: result = "Consumer/Merchant"; break;
    case DISPUTE_T_DIVORCE: result = "Divorce"; break;
    case DISPUTE_T_FAMILY: result = "Family"; break;
    case DISPUTE_T_LANDLORD: result = "Landlord"; break;
    case DISPUTE_T_NONE: result = "None"; break;
    case DISPUTE_T_NEIGHBORHOOD: result = "Neighborhood"; break;
    case DISPUTE_T_OTHER: result = "Other"; break;
    case DISPUTE_T_PARENTING_PLAN: result = "Parenting Plan"; break;
    case DISPUTE_T_PARENT_TEEN: result = "Parent/Teen"; break;
    case DISPUTE_T_SMALL_CLAIMS: result = "Small Claims"; break;
    case DISPUTE_T_TENANT: result = "Tenant"; break;
    case DISPUTE_T_VICTIM_OFFENDER: result = "Victim/Offender"; break;
    case DISPUTE_T_WORKPLACE: result = "Workplace"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForReferralTypes(ReferralTypes id)
{
    QString result;
    switch(id)
    {
    case REFERRAL_T_ADVERTISING: result = "Advertising"; break;
    case REFERRAL_T_ATTORNEY: result = "Attorney"; break;
    case REFERRAL_T_ATTORNEY_GENERALS_OFFICE: result = "Attorney General"; break;
    case REFERRAL_T_COURTS: result = "Courts"; break;
    case REFERRAL_T_COURT_SOLICITED: result = "Court Solicited"; break;
    case REFERRAL_T_DCFS_JJC_GOVT_AGENCY: result = "Govt Agency"; break;
    case REFERRAL_T_FAMILY_FRIEND: result = "Family/Friend"; break;
    case REFERRAL_T_INTERNET: result = "Internet"; break;
    case REFERRAL_T_LAW_ENFORCEMENT: result = "Law Enforcement"; break;
    case REFERRAL_T_LEGAL_SERVICES: result = "Legal Services"; break;
    case REFERRAL_T_OTHER_NONE: result = "Other"; break;
    case REFERRAL_T_PHONEBOOK: result = "Phonebook"; break;
    case REFERRAL_T_PRESENTATION_TRAINING: result = "Presentation/Training"; break;
    case REFERRAL_T_PRIVATE_AGENCY: result = "Private Agency"; break;
    case REFERRAL_T_RETURN_CLIENTS: result = "Return Client"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForPartyTypes(PartyTypes id)
{
    QString result;
    switch(id)
    {
    case PARTY_T_FIRST: result = "Party 1"; break;
    case PARTY_T_SECOND: result = "Party 2"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForUserTypes(UserTypes id)
{
    QString result;
    switch(id)
    {
    case USER_T_ADMIN: result = "Administrator"; break;
    case USER_T_NORMAL: result = "Normal"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForSearchTypes(SearchTypes id)
{
    QString result;
    switch(id)
    {
    case SEARCH_T_CALL_LOG: result = "Call Log"; break;
    case SEARCH_T_MEDIATION: result = "Mediation"; break;
    case SEARCH_T_PERSON: result = "Person"; break;
    default: result = "None Selected"; break;
    }
    return result;
}

QString StringForSessionStates(SessionStates id)
{
    QString result;
    switch(id)
    {
    case SESSION_STATE_CANCELLED: result = "Cancelled"; break;
    case SESSION_STATE_CONFIRMED: result = "Confirmed"; break;
    case SESSION_STATE_NONE: result = "None"; break;
    case SESSION_STATE_PENDING: result = "Pending"; break;
    case SESSION_STATE_RESCHEDULED: result = "Rescheduled"; break;
    default: result = "Invalid"; break;
    }
    return result;
}

