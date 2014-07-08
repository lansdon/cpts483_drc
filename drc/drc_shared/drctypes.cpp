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
    case COUNTY_NONE: result = "None"; break;
    case COUNTY_OTHER: result = "Other"; break;
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForDisputeProcessStates(DisputeProcessStates id)
{
    QString result;
    switch(id)
    {
    case PROCESS_STATE_NONE: result = "None"; break;
    case PROCESS_STATE_PENDING: result = "Pending"; break;
    case PROCESS_STATE_SCHEDULED: result = "Scheduled"; break;
    case PROCESS_STATE_CLOSED: result = "Closed"; break;
    default: result = "<error>"; break;
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
    case DISPUTE_T_NEIGHBORHOOD: result = "Neighborhood"; break;
    case DISPUTE_T_NONE: result = "None"; break;
    case DISPUTE_T_OTHER: result = "Other"; break;
    case DISPUTE_T_PARENTING_PLAN: result = "Parenting Plan"; break;
    case DISPUTE_T_PARENT_TEEN: result = "Parent/Teen"; break;
    case DISPUTE_T_PROPERTY_BUSINESS: result = "Property/Business";
    case DISPUTE_T_SMALL_CLAIMS: result = "Small Claims"; break;
    case DISPUTE_T_TENANT: result = "Tenant"; break;
    case DISPUTE_T_VICTIM_OFFENDER: result = "Victim/Offender"; break;
    case DISPUTE_T_WORKPLACE: result = "Workplace"; break;
    default: result = "<error>"; break;
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
    case REFERRAL_T_NONE: result = "None"; break;
    case REFERRAL_T_OTHER_NONE: result = "Other"; break;
    case REFERRAL_T_PHONEBOOK: result = "Phonebook"; break;
    case REFERRAL_T_PRESENTATION_TRAINING: result = "Presentation/Training"; break;
    case REFERRAL_T_PRIVATE_AGENCY: result = "Private Agency"; break;
    case REFERRAL_T_RETURN_CLIENTS: result = "Return Client"; break;
    default: result = "<error>"; break;
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
    default: result = "<error>"; break;
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
    default: result = "<error>"; break;
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
    case SEARCH_T_NONE: result = "None"; break;
    case SEARCH_T_PERSON: result = "Person"; break;
    default: result = "<error>"; break;
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
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForInquiryTypes(InquiryTypes id)
{
    QString result;
    switch(id)
    {
    case INQUIRY_T_EMAIL: result = "Email"; break;
    case INQUIRY_T_NONE: result = "None"; break;
    case INQUIRY_T_PHONE: result = "Phone"; break;
    case INQUIRY_T_REFERRAL: result = "Referral"; break;
    case INQUIRY_T_WALKIN: result = "Walk-in"; break;
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForCourtTypes(CourtCaseTypes id)
{
    QString result;
    switch(id)
    {
    case COURT_T_JUVENILE: result = "Juvenile"; break;
    case COURT_T_NONE: result = "None"; break;
    case COURT_T_OTHER: result = "Other"; break;
    case COURT_T_SMALL_CLAIMS: result = "Small Claims"; break;
    case COURT_T_SUPERIOR: result = "Superior"; break;
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForCourtOrderTypes(CourtOrderTypes id)
{
    QString result;
    switch(id)
    {
    case COURT_ORDER_T_NONE: result = "None"; break;
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForSessionOutcomes(SessionOutcomes id)
{
    QString result;
    switch (id) {
    case SESSION_OUTCOME_NONE: result = "None"; break;
    case SESSION_OUTCOME_FIRST_PARTY_WITHDREW: result = "First Party Wtihdrew"; break;
    case SESSION_OUTCOME_SECOND_PARTY_DECLINES: result = "Second Party Declined"; break;
    case SESSION_OUTCOME_AGREEMENT: result = "Agreement"; break;
    case SESSION_OUTCOME_NO_AGREEMENT: result = "No Agreement"; break;
    case SESSION_OUTCOME_PROBLEM_SOLVING: result = "Problem Solbing"; break;
    case SESSION_OUTCOME_REFERRED_OUT: result = "Referred Out"; break;
    case SESSION_OUTCOME_CANNOT_REACH_PARTIES: result = "Cannot Reach Either Client"; break;
    case SESSION_OUTCOME_SELF_RESOLVED: result = "Self Resolved"; break;
    default: result = "<error>"; break;
    }
    return result;
}

QString StringForEvaluationAnswers(EvaluationAnswers id)
{
    QString result;
    switch(id){
    case EVALUATION_ANSWERS_NO_ANSWER: result = "No Answer"; break;
    case EVALUATION_ANSWERS_YES: result = "Yes"; break;
    case EVALUATION_ANSWERS_NO: result = "No"; break;
    case EVALUATION_ANSWERS_SOMEWHAT: result = "Somewhat"; break;
    default: result = "<error>"; break;
    }
    return result;
}
