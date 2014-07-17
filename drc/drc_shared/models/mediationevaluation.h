#ifndef MEDIATIONEVALUATION_H
#define MEDIATIONEVALUATION_H
#include "drctypes.h"
#include "DBBaseObject.h"


class MediationEvaluation : public DBBaseObject
{
public:
    MediationEvaluation();

    //getters
    QDate getMediationDate() const { return _mediationDate; }
    QString getMediators() const { return _mediators; }
    QString getComments() const { return _comments; }
    QString getName() const {return _name; }
    QString getEmail() const { return _email; }
    QString getDayPhone() const { return _dayPhone; }
    QString getEveningPhone() const { return _eveningPhone; }
    int getQ1() const { return _q1; }
    EvaluationAnswers getQ2() const { return _q2; }
    EvaluationAnswers getQ3() const { return _q3; }
    EvaluationAnswers getQ4() const { return _q4; }
    EvaluationAnswers getQ5() const { return _q5; }
    EvaluationAnswers getQ6() const { return _q6; }
    EvaluationAnswers getQ7() const { return _q7; }
    EvaluationAnswers getQ8() const { return _q8; }
    EvaluationAnswers getCallBackPermission() const { return _callBackPermissions; }
    EvaluationAnswers getPromoPermissions() const { return _promoPermissions; }
    CountyIds getCountyOfMediation() const { return _countyOfMediation; }

    //setters
    void setMediationDate(QDate value) { _mediationDate = value; }
    void setMediators(QString value) { _mediators = value; }
    void setComments(QString value) { _comments = value; }
    void setName(QString value) { _name = value; }
    void setEmail(QString value) { _email = value; }
    void setDayPhone(QString value) { _dayPhone = value; }
    void setEveningPhone(QString value) { _eveningPhone = value; }
    void setQ1(int value) { _q1 = value; }
    void setQ2(EvaluationAnswers value) { _q2 = value; }
    void setQ3(EvaluationAnswers value) { _q3 = value; }
    void setQ4(EvaluationAnswers value) { _q4 = value; }
    void setQ5(EvaluationAnswers value) { _q5 = value; }
    void setQ6(EvaluationAnswers value) { _q6 = value; }
    void setQ7(EvaluationAnswers value) { _q7 = value; }
    void setQ8(EvaluationAnswers value) { _q8 = value; }
    void setCallBackPermissions(EvaluationAnswers value) { _callBackPermissions = value; }
    void setPromoPermissions(EvaluationAnswers value) { _promoPermissions = value; }
    void setCountyOfMediation(CountyIds value) { _countyOfMediation = value; }

    // Required Overrides
    QString Parse();
    QString UpdateParse();
    QString table();
    QString DuplicateQuery();
    QString SearchQuery();
    QString GetIdRowName();


private:
    QDate _mediationDate;
    QString _mediators, _comments, _name, _email, _dayPhone, _eveningPhone;
    int _q1;
    EvaluationAnswers _q2, _q3, _q4, _q5, _q6, _q7, _q8, _callBackPermissions, _promoPermissions;
    CountyIds _countyOfMediation;

};

#endif // MEDIATIONEVALUATION_H
