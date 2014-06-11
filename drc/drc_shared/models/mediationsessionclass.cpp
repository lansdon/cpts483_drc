#include "mediationsessionclass.h"

MediationSessionClass::MediationSessionClass()
{
    _mediationTime = QDateTime::currentDateTime();
    _pendingRB = true;
    _cancelledRB = _rescheduledRB = _confirmedRB = _fee1Paid = _fee2Paid = _feeFamilyPaid = _feeOtherPaid = false;
}
