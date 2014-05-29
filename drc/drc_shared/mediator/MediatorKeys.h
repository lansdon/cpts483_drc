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
//				GUI EVENTS										//
//	- Everyting in this section is called by the GUI			//
//  - For example, when the user submits a name which			//
//  - the BL will register to recieve those events.				//
//////////////////////////////////////////////////////////////////
const std::string MKEY_GUI_SUBMIT_FRUIT_NAME = "MKEY_GUI_SUBMIT_FRUIT_NAME";                // std::string*

//////////////////////////////////////////////////////////////////
//				BUSINESS LOGIC EVENTS							//
//	- Everyting in this section is called by the BUSINESS LOGIC //
//  - For example, when the user submits a name which			//
//  - the BL will register to recieve those events.				//
//////////////////////////////////////////////////////////////////
const std::string MKEY_BL_VALIDATE_FRUITNAME_DONE = "MKEY_BL_VALIDATE_FRUITNAME_DONE";       // std::string*


//////////////////////////////////////////////////////////////////
//				DB EVENTS										//
//	- Everyting in this section is called by the  DB			//
//  - For example, when the user submits a name which			//
//  - the BL will register to recieve those events.				//
//////////////////////////////////////////////////////////////////
const std::string MKEY_DB_PERSIST_FRUIT_NAME_DONE = "MKEY_DB_PERSIST_FRUIT_NAME_DONE";       // nil



//////////////// Temp Testing -- Delete this! ///////////////////
const std::string MKEY_PRINT_STRING			= "MKEY_PRINT_STRING";
const std::string MKEY_PRINT_DOG			= "MKEY_PRINT_DOG";
const std::string MKEY_PRINT_INT			= "MKEY_PRINT_INT";


#endif
