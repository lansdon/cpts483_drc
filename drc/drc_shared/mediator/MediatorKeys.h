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
const std::string MKEY_GUI_SEND_FRUIT_NAME = "MKEY_GUI_SEND_FRUIT_NAME";

//////////////////////////////////////////////////////////////////
//				BUSINESS LOGIC EVENTS							//
//	- Everyting in this section is called by the BUSINESS LOGIC //
//  - For example, when the user submits a name which			//
//  - the BL will register to recieve those events.				//
//////////////////////////////////////////////////////////////////
const std::string MKEY_BL_SEND_FRUIT_NAME_RESULT = "MKEY_BL_SEND_FRUIT_NAME_RESULT";


//////////////////////////////////////////////////////////////////
//				DB EVENTS										//
//	- Everyting in this section is called by the  DB			//
//  - For example, when the user submits a name which			//
//  - the BL will register to recieve those events.				//
//////////////////////////////////////////////////////////////////



//////////////// Temp Testing -- Delete this! ///////////////////
const std::string MKEY_PRINT_STRING			= "MKEY_PRINT_STRING";
const std::string MKEY_PRINT_DOG			= "MKEY_PRINT_DOG";
const std::string MKEY_PRINT_INT			= "MKEY_PRINT_INT";


#endif
