#include <qstring.h>
#include <qdebug.h>

#include "drcbl.h"

#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/MediatorArg.h"
#include "drc_shared/mediator/MediatorKeys.h"

//namespace drc {
//namespace bl {


DRCBL::DRCBL()
      : _fruitNameProcessor(MKEY_GUI_SUBMIT_FRUIT_NAME, MKEY_BL_VALIDATE_FRUITNAME_DONE, "", ""),
        _intakeFormProcessor(MKEY_GUI_SUBMIT_INTAKE_FORM, MKEY_BL_VALIDATE_SAVE_INTAKE_FORM_DONE,
                             MKEY_GUI_LOAD_INTAKE_FORM, MKEY_BL_VALIDATE_LOAD_INTAKE_FORM_DONE),
        _searchUserName(MKEY_GUI_SEARCH_FOR_USERNAME, MKEY_BL_RETURN_SEARCH_RESULTS, "", ""),
        _userLoginProcessor("", "", "", "")
{
}

// end namespaces
//}
//}
