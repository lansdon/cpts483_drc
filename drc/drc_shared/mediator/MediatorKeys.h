//
//  MediatorKeys.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 Lansdon Page. All rights reserved.
//

#ifndef mediator_test_MediatorKeys_h
#define mediator_test_MediatorKeys_h

#include <string>

//////////////////////////////////////////////////////////////////
//				EVENTS INFORMATION
// Events are chained together between the components of the system (gui, db, bl)
// They are being organized in this document by a single event, with the chain shown in order.
// Please follow this convention for clarity and ease of debugging.
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//				SUBMIT FRUIT NAME
// Test function to save a fruit in the database
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_GUI_SUBMIT_FRUIT_NAME = "MKEY_GUI_SUBMIT_FRUIT_NAME";                // Fruit*
const std::string MKEY_BL_VALIDATE_FRUITNAME_DONE = "MKEY_BL_VALIDATE_FRUITNAME_DONE";      // Fruit*
const std::string MKEY_DB_PERSIST_FRUIT_NAME_DONE = "MKEY_DB_PERSIST_FRUIT_NAME_DONE";      // Fruit

//////////////////////////////////////////////////////////////////
//				SEARCH FOR USER BY NAME ????? Test Function ???
// Test function to load test records on fruit page
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_GUI_SEARCH_FOR_USERNAME = "MKEY_GUI_SEARCH_FOR_USERNAME";            // std::string*
const std::string MKEY_BL_RETURN_SEARCH_RESULTS = "MKEY_BL_RETURN_SEARCH_RESULTS";          // class Intake*

//////////////////////////////////////////////////////////////////
//				AUTHENTICATE USER
// When the user hit's login - we must see if they entered correct username + password
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_GUI_AUTHENTICATE_USER = "MKEY_GUI_AUTHENTICATE_USER";                // User*
const std::string MKEY_BL_AUTHENTICATE_USER_DONE = "MKEY_BL_AUTHENTICATE_USER_DONE";        // User*
const std::string MKEY_DB_AUTHENTICATE_USER_DONE = "MKEY_DB_AUTHENTICATE_USER_DONE";        // std::vector<User*>*

//////////////////////////////////////////////////////////////////
//				CURRENT USER CHANGED
// This is a global event called by the Authentication Singleton
// To allow for handling when a user logs in and out. (for example gui menus on/off)
//////////////////////////////////////////////////////////////////                          ARGUMENT TYPE
const std::string MKEY_CURRENT_USER_CHANGED = "MKEY_CURRENT_USER_CHANGED";                  // User*

//////////////////////////////////////////////////////////////////
//				SAVE INTAKE FORM
// Save an intake form to the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const std::string MKEY_GUI_SUBMIT_INTAKE_FORM = "MKEY_GUI_SUBMIT_INTAKE_FORM";                          // Intake*
const std::string MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE = "MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE";    // Intake*
const std::string MKEY_DB_PERSIST_INTAKE_FORM_DONE = "MKEY_DB_PERSIST_INTAKE_FORM_DONE";                // Intake*

//////////////////////////////////////////////////////////////////
//				LOAD INTAKE FORM
// Load an intake form from the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const std::string MKEY_GUI_LOAD_INTAKE_FORM = "MKEY_GUI_LOAD_INTAKE_FORM";                              // Intake*
const std::string MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE = "MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE";   // Intake*
const std::string MKEY_DB_LOAD_INTAKE_FORM_DONE = "MKEY_DB_LOAD_INTAKE_FORM_DONE";                      // std::vector<Intake*>*

//////////////////////////////////////////////////////////////////
//				SAVE PERSON
// Save a person the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const std::string MKEY_GUI_SUBMIT_PERSON_FORM = "MKEY_GUI_SUBMIT_PERSON_FORM";                          // Person*
const std::string MKEY_BL_VALIDATE_SAVE_PERSON_FORM_DONE = "MKEY_BL_VALIDATE_SAVE_PERSON_FORM_DONE";    // Person*
const std::string MKEY_DB_PERSIST_PERSON_FORM_DONE = "MKEY_DB_PERSIST_PERSON_FORM_DONE";                // Person*

//////////////////////////////////////////////////////////////////
//				LOAD PERSON
// Load a person from the database
//////////////////////////////////////////////////////////////////                                      ARGUMENT TYPE
const std::string MKEY_GUI_LOAD_PERSON_FORM = "MKEY_GUI_LOAD_PERSON_FORM";                              // Person*
const std::string MKEY_BL_VALIDATE_LOAD_PERSON_FORM_DONE = "MKEY_BL_VALIDATE_LOAD_PERSON_FORM_DONE";    // Person*
const std::string MKEY_DB_LOAD_PERSON_FORM_DONE = "MKEY_DB_LOAD_PERSON_FORM_DONE";                      // std::vector<Person*>*

//////////////////////////////////////////////////////////////////
//				REQUEST SALT
// Request salt for a particular user
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
const std::string MKEY_BL_REQUEST_SALT = "MKEY_BL_REQUEST_SALT";                            	// std::string*
const std::string MKEY_DB_SEND_SALT = "MKEY_DB_SEND_SALT";                              		// std::string

//////////////////////////////////////////////////////////////////
//				QUERY PERSON
// Query for a list of persons based on a single input person
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
const std::string MKEY_GUI_QUERY_PERSON = "MKEY_GUI_QUERY_PERSON";                            	// std::string*
const std::string MKEY_BL_QUERY_PERSON = "MKEY_BL_QUERY_PERSON";                              		// std::string
const std::string MKEY_DB_QUERY_PERSON = "MKEY_DB_QUERY_PERSON";                              		// std::string

//////////////////////////////////////////////////////////////////
//				QUERY MEDIATION PROCESS
// Query for a list of persons based on a single input person
//////////////////////////////////////////////////////////////////                              ARGUMENT TYPE
const std::string MKEY_GUI_QUERY_MEDIATION = "MKEY_GUI_QUERY_MEDIATION";                            	// std::string*
const std::string MKEY_BL_QUERY_MEDIATION = "MKEY_BL_QUERY_MEDIATION";                              		// std::string
const std::string MKEY_DB_QUERY_MEDIATION = "MKEY_DB_QUERY_MEDIATION";                              		// std::string


#endif
