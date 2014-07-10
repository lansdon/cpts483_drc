//
//  MediatorKeys.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//

#ifndef mediator_test_MediatorKeys_h
#define mediator_test_MediatorKeys_h

#include <QString>

//////////////////////////////////////////////////////////////////
//				EVENTS INFORMATION
// Events are chained together between the components of the system (gui, db, bl)
// They are being organized in this document by a single event, with the chain shown in order.
// Please follow this convention for clarity and ease of debugging.
//////////////////////////////////////////////////////////////////


//// >>>>>>>>>>>>>>>>> OBSOLETE ITEMS!!!! THESE ARE GOING TO BE DELETED!! <<<<<<<<<<<<<<<<<<<
////////////////////////////////////////////////////////////////////
////				SUBMIT FRUIT NAME
//// Test function to save a fruit in the database
////////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
//const QString MKEY_GUI_SUBMIT_FRUIT_NAME = "MKEY_GUI_SUBMIT_FRUIT_NAME";                // Fruit*
//const QString MKEY_BL_VALIDATE_FRUITNAME_DONE = "MKEY_BL_VALIDATE_FRUITNAME_DONE";      // Fruit*
//const QString MKEY_DB_PERSIST_FRUIT_NAME_DONE = "MKEY_DB_PERSIST_FRUIT_NAME_DONE";      // Fruit

//// >>>>>>>>>>>>>>>>> OBSOLETE ITEMS!!!! THESE ARE GOING TO BE DELETED!! <<<<<<<<<<<<<<<<<<<
////////////////////////////////////////////////////////////////////
////				SEARCH FOR USER BY NAME ????? Test Function ???
//// Test function to load test records on fruit page
////////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
//const QString MKEY_GUI_SEARCH_FOR_USERNAME = "MKEY_GUI_SEARCH_FOR_USERNAME";            // QString*
//const QString MKEY_BL_RETURN_SEARCH_RESULTS = "MKEY_BL_RETURN_SEARCH_RESULTS";          // class Intake*

//////////////////////////////////////////////////////////////////
//				AUTHENTICATE USER
// When the user hit's login - we must see if they entered correct username + password
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const QString MKEY_GUI_AUTHENTICATE_USER = "MKEY_GUI_AUTHENTICATE_USER";                // User*
const QString MKEY_BL_AUTHENTICATE_USER_DONE = "MKEY_BL_AUTHENTICATE_USER_DONE";        // User*
const QString MKEY_DB_AUTHENTICATE_USER_DONE = "MKEY_DB_AUTHENTICATE_USER_DONE";        // std::vector<User*>*
const QString MKEY_GUI_ENABLE_MENUS = "MKEY_GUI_ENABLE_MENUS";                          // None
const QString MKEY_GUI_DISABLE_MENUS = "MKEY_GUI_DISABLE_MENUS";                        // None
const QString MKEY_GUI_SHOW_ADMIN = "MKEY_GUI_SHOW_ADMIN";                              // None
const QString MKEY_GUI_HIDE_ADMIN = "MKEY_GUI_HIDE_ADMIN";                              // None

//////////////////////////////////////////////////////////////////
//              MANAGE USERS
// Keys to add/remove users.  Nothing special
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const QString MKEY_DB_ADD_NEW_USER = "MKEY_DB_ADD_NEW_USER";                            // User*
const QString MKEY_DB_REMOVE_USER = "MKEY_DB_REMOVE_USER";                              // User*
const QString MKEY_DB_VERIFY_REMOVE_USER = "MKEY_DB_VERIFY_REMOVE_USER";                // arg.isSuccessful()
const QString MKEY_DB_VERIFY_UPDATE_USER = "MKEY_DB_VERIFY_UPDATE_USER";                // arg.isSuccessful()
const QString MKEY_DB_VERIFY_ADD_USER = "MKEY_DB_ADD_UPDATE_USER";                      // arg.isSuccessful()
const QString MKEY_DB_UPDATE_USER = "MKEY_DB_UPDATE_USER";                              // User*
const QString MKEY_DB_GET_ALL_USER = "MKEY_DB_GET_ALL_USER";                            // User*
const QString MKEY_DB_RETURN_ALL_USER = "MKEY_DB_RETURN_ALL_USER";                      // QVector<User*>*

//////////////////////////////////////////////////////////////////
//				CURRENT USER CHANGED
// This is a global event called by the Authentication Singleton
// To allow for handling when a user logs in and out. (for example gui menus on/off)
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const QString MKEY_CURRENT_USER_CHANGED = "MKEY_CURRENT_USER_CHANGED";                  	// User*

//////////////////////////////////////////////////////////////////
//				SAVE MEDIATION PROCESS
// Save mediation process form to the database
//////////////////////////////////////////////////////////////////                                                              ARGUMENT TYPE
const QString MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM = "MKEY_GUI_SUBMIT_MEDIATION_PROCESS_FORM";                          // MediationProcess*
const QString MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE = "MKEY_BL_VALIDATE_SAVE_MEDIATION_PROCESS_FORM_DONE";    // MediationProcess*
const QString MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE = "MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE";                // MediationProcess*

//////////////////////////////////////////////////////////////////
//				LOAD MEDIATION PROCESS
// Load an mediation process from the database
//////////////////////////////////////////////////////////////////                                                              ARGUMENT TYPE
const QString MKEY_GUI_LOAD_MEDIATION_PROCESS_FORM = "MKEY_GUI_LOAD_MEDIATION_PROCESS_FORM";                              // MediationProcess*
const QString MKEY_BL_VALIDATE_LOAD_MEDIATION_PROCESS_FORM_DONE = "MKEY_BL_VALIDATE_LOAD_MEDIATION_PROCESS_FORM_DONE";    // MediationProcess*
const QString MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE = "MKEY_DB_LOAD_MEDIATION_PROCESS_FORM_DONE";                      // MediationProcess*

//////////////////////////////////////////////////////////////////
//				LOAD RECENT MEDIATIONS VECTOR
// Loads to 10 most recently updated mediations
//////////////////////////////////////////////////////////////////                                                              ARGUMENT TYPE
const QString MKEY_DOCK_REQUEST_RECENT_MEDIATIONS = "MKEY_DOCK_REQUEST_RECENT_MEDIATIONS";                                      // nullptr
const QString MKEY_BL_REQUEST_RECENT_MEDIATIONS_DONE = "MKEY_BL_REQUEST_RECENT_MEDIATIONS_DONE";                                // nullptr
const QString MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE = "MKEY_DB_REQUEST_RECENT_MEDIATIONS_DONE";                                // MediationProcessVector*

///
// LOAD PENDING MEDIATIONS VECTOR
//
///
const QString MKEY_DOCK_REQUEST_PENDING_MEDIATIONS = "MKEY_DOCK_REQUEST_PENDING_MEDIATIONS";
const QString MKEY_BL_REQUEST_PENDING_MEDIATIONS_DONE = "MKEY_BL_REQUEST_PENDING_MEDIATIONS_DONE";
const QString MKEY_DB_REQUEST_PENDING_MEDIATIONS_DONE = "MKEY_DB_REQUEST_PENDING_MEDIATIONS_DONE";

///
// LOAD SCHEDULED MEDIATIONS VECTOR
//
///
const QString MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS = "MKEY_DOCK_REQUEST_SCHEDULED_MEDIATIONS";
const QString MKEY_BL_REQUEST_SCHEDULED_MEDIATIONS_DONE = "MKEY_BL_REQUEST_SCHEDULED_MEDIATIONS_DONE";
const QString MKEY_DB_REQUEST_SCHEDULED_MEDIATIONS_DONE = "MKEY_DB_REQUEST_SCHEDULED_MEDIATIONS_DONE";

///
// LOAD CLOSED MEDIATIONS VECTOR
//
///
const QString MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS = "MKEY_DOCK_REQUEST_CLOSED_MEDIATIONS";
const QString MKEY_BL_REQUEST_CLOSED_MEDIATIONS_DONE = "MKEY_BL_REQUEST_CLOSED_MEDIATIONS_DONE";
const QString MKEY_DB_REQUEST_CLOSED_MEDIATIONS_DONE = "MKEY_DB_REQUEST_CLOSED_MEDIATIONS_DONE";




//////////////////////////////////////////////////////////////////
//				SAVE PERSON
// Save a person the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const QString MKEY_GUI_SUBMIT_PERSON_FORM = "MKEY_GUI_SUBMIT_PERSON_FORM";                          // Person*
const QString MKEY_BL_VALIDATE_SAVE_PERSON_FORM_DONE = "MKEY_BL_VALIDATE_SAVE_PERSON_FORM_DONE";    // Person*
const QString MKEY_DB_PERSIST_PERSON_FORM_DONE = "MKEY_DB_PERSIST_PERSON_FORM_DONE";                // Person*

//////////////////////////////////////////////////////////////////
//				LOAD PERSON
// Load a person from the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const QString MKEY_GUI_LOAD_PERSON_FORM = "MKEY_GUI_LOAD_PERSON_FORM";                              // Person*
const QString MKEY_BL_VALIDATE_LOAD_PERSON_FORM_DONE = "MKEY_BL_VALIDATE_LOAD_PERSON_FORM_DONE";    // Person*
const QString MKEY_DB_LOAD_PERSON_FORM_DONE = "MKEY_DB_LOAD_PERSON_FORM_DONE";                      // PersonVector* (see drctypes.h)

//////////////////////////////////////////////////////////////////
//				REQUEST SALT
// Request salt for a particular user
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
//const QString MKEY_BL_REQUEST_SALT = "MKEY_BL_REQUEST_SALT";                            		// QString*
//const QString MKEY_DB_SEND_SALT = "MKEY_DB_SEND_SALT";                              			// QString*

//////////////////////////////////////////////////////////////////
//				QUERY PERSON
// Query for a list of persons based on a single input person
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
const QString MKEY_GUI_QUERY_PERSON = "MKEY_GUI_QUERY_PERSON";                            		// QString*
const QString MKEY_BL_QUERY_PERSON = "MKEY_BL_QUERY_PERSON";                              		// QString*
const QString MKEY_DB_QUERY_PERSON = "MKEY_DB_QUERY_PERSON";                              		// PersonVector* (see drctypes.h)

//////////////////////////////////////////////////////////////////
//				QUERY MEDIATION PROCESS
// Query for a list of mediation processes based on a single mediation process
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
const QString MKEY_GUI_QUERY_MEDIATION = "MKEY_GUI_QUERY_MEDIATION";                            // QString*
const QString MKEY_BL_QUERY_MEDIATION = "MKEY_BL_QUERY_MEDIATION";                              // QString
const QString MKEY_DB_QUERY_MEDIATION = "MKEY_DB_QUERY_MEDIATION";                              // MediationProcessVector* (see drctypes.h)


//////////////////////////////////////////////////////////////////
//				DOCK WIDGET
//  ** These are one-shot events. (not chains of events)
//////////////////////////////////////////////////////////////////
//	toggle MPToolbox Dock Widget
const QString MKEY_GUI_SHOW_MEDIATION_BROWSER = "MKEY_GUI_SHOW_MEDIATION_BROWSER";              // null
// Set Sessions for Session Browser
const QString MKEY_DOCK_SET_MEDIATIONS = "MKEY_DOCK_SET_MEDIATIONS";                                // MediationProcessVector*
// Refresh Mediations Browser
const QString MKEY_DOCK_REFRESH_MEDIATIONS = "MKEY_DOCK_REFRESH_MEDIATIONS";
// Set Sessions for Session Browser
const QString MKEY_DOCK_SET_SESSIONS = "MKEY_DOCK_SET_SESSIONS";                                // MediationSessionsVector*
// Session Table - selected a session
const QString MKEY_DOCK_SESSION_CHANGED = "MKEY_DOCK_SESSION_CHANGED";                          // MediationSessionsVector*
// Session Table - show dock
const QString MKEY_GUI_SHOW_SESSIONS_BROWSER = "MKEY_GUI_SHOW_SESSIONS_BROWSER";                // MediationSessionsVector*
// Notes Table - show dock
const QString MKEY_GUI_SHOW_NOTES_BROWSER = "MKEY_GUI_SHOW_NOTES_BROWSER";                // MediationSessionsVector*
// Set Notes for Notes Browser
const QString MKEY_DOCK_SET_NOTES = "MKEY_DOCK_SET_NOTES";                                // MediationSessionsVector*


//////////////////////////////////////////////////////////////////
//				MEDIATION PROCESS - (GUI INTERNAL)
// Internal MP events to signal changes from children forms.
//  ** These are one-shot events. (not chains of events)
//////////////////////////////////////////////////////////////////                         ARGUMENT TYPE
const QString MKEY_GUI_MP_SAVE_PENDING = "MKEY_GUI_MP_SAVE_PENDING";                        // nullptr
const QString MKEY_GUI_MP_POPULATE = "MKEY_GUI_MP_POPULATE";                                // nullptr
const QString MKEY_GUI_MP_SHOULD_SAVE = "MKEY_GUI_MP_SHOULD_SAVE";                          // nullptr
const QString MKEY_GUI_MP_NEW_FORM = "MKEY_GUI_MP_NEW_FORM";                                // nullptr


//////////////////////////////////////////////////////////////////
//				MEDIATION EVALUATION
//////////////////////////////////////////////////////////////////
const QString MKEY_GUI_SAVE_EVALUATION = "MKEY_GUI_SAVE_EVALUATION";                        // MediationEvaluation*
const QString MKEY_BL_SAVE_EVALUATION = "MKEY_BL_SAVE_EVALUATION";                          // MediationEvaluation*
const QString MKEY_DB_SAVE_EVALUATION = "MKEY_DB_SAVE_EVALUATION";                          // MediationEvaluation*

//////////////////////////////////////////////////////////////////
//				DRCClient - (GUI INTERNAL)
// Internal events for main window
//  ** These are one-shot events. (not chains of events)
//////////////////////////////////////////////////////////////////                         ARGUMENT TYPE
const QString MKEY_GUI_SHOW_EVALUATION = "MKEY_GUI_SHOW_EVALUATION";                                // nullptr
const QString MKEY_GUI_SHOW_MONTHLY_REPORT = "MKEY_GUI_SHOW_MONTHLY_REPORT";                          // nullptr
const QString MKEY_GUI_SHOW_RESWA_REPORT = "MKEY_GUI_SHOW_RESWA_REPORT";                                // nullptr


//////////////////////////////////////////////////////////////////
//				RESWA REPORTS - REQUEST
// GUI requesting a reswa report for given year and semi-annual period
//////////////////////////////////////////////////////////////////                         ARGUMENT TYPE
const QString MKEY_GUI_REQUEST_RESWA_REPORT = "MKEY_GUI_REQUEST_RESWA_REPORT";             // ReportRequest*
const QString MKEY_BL_REQUEST_RESWA_REPORT = "MKEY_BL_REQUEST_RESWA_REPORT";              // ReportRequest*
const QString MKEY_DB_REQUEST_RESWA_REPORT_DONE = "MKEY_DB_REQUEST_RESWA_REPORT_DONE";    // ResWaReport*

#endif
