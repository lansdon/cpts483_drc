#ifndef MEDIATIONEVALUATION_H
#define MEDIATIONEVALUATION_H
#include "drctypes.h"
#include "DBBaseObject.h"

/*!
 * \brief The MediationEvaluation class
 */
class MediationEvaluation : public DBBaseObject
{
public:
    MediationEvaluation();

    //getters
    /*!
     * \brief getMediationDate
     * \return
     */
    QDate getMediationDate() const { return _mediationDate; }
    /*!
     * \brief getMediators
     * \return
     */
    QString getMediators() const { return _mediators; }
    /*!
     * \brief getComments
     * \return
     */
    QString getComments() const { return _comments; }
    /*!
     * \brief getName
     * \return
     */
    QString getName() const {return _name; }
    /*!
     * \brief getEmail
     * \return
     */
    QString getEmail() const { return _email; }
    /*!
     * \brief getDayPhone
     * \return
     */
    QString getDayPhone() const { return _dayPhone; }
    /*!
     * \brief getEveningPhone
     * \return
     */
    QString getEveningPhone() const { return _eveningPhone; }
    /*!
     * \brief getQ1
     * \return
     */
    int getQ1() const { return _q1; }
    /*!
     * \brief getQ2
     * \return
     */
    EvaluationAnswers getQ2() const { return _q2; }
    /*!
     * \brief getQ3
     * \return
     */
    EvaluationAnswers getQ3() const { return _q3; }
    /*!
     * \brief getQ4
     * \return
     */
    EvaluationAnswers getQ4() const { return _q4; }
    /*!
     * \brief getQ5
     * \return
     */
    EvaluationAnswers getQ5() const { return _q5; }
    /*!
     * \brief getQ6
     * \return
     */
    EvaluationAnswers getQ6() const { return _q6; }
    /*!
     * \brief getQ7
     * \return
     */
    EvaluationAnswers getQ7() const { return _q7; }
    /*!
     * \brief getQ8
     * \return
     */
    EvaluationAnswers getQ8() const { return _q8; }
    /*!
     * \brief getCallBackPermission
     * \return
     */
    EvaluationAnswers getCallBackPermission() const { return _callBackPermissions; }
    /*!
     * \brief getPromoPermissions
     * \return
     */
    EvaluationAnswers getPromoPermissions() const { return _promoPermissions; }
    /*!
     * \brief getCountyOfMediation
     * \return
     */
    CountyIds getCountyOfMediation() const { return _countyOfMediation; }

    //setters
    /*!
     * \brief setMediationDate
     * \param value
     */
    void setMediationDate(QDate value) { _mediationDate = value; }
    /*!
     * \brief setMediators
     * \param value
     */
    void setMediators(QString value) { _mediators = value; }
    /*!
     * \brief setComments
     * \param value
     */
    void setComments(QString value) { _comments = value; }
    /*!
     * \brief setName
     * \param value
     */
    void setName(QString value) { _name = value; }
    /*!
     * \brief setEmail
     * \param value
     */
    void setEmail(QString value) { _email = value; }
    /*!
     * \brief setDayPhone
     * \param value
     */
    void setDayPhone(QString value) { _dayPhone = value; }
    /*!
     * \brief setEveningPhone
     * \param value
     */
    void setEveningPhone(QString value) { _eveningPhone = value; }
    /*!
     * \brief setQ1
     * \param value
     */
    void setQ1(int value) { _q1 = value; }
    /*!
     * \brief setQ2
     * \param value
     */
    void setQ2(EvaluationAnswers value) { _q2 = value; }
    /*!
     * \brief setQ3
     * \param value
     */
    void setQ3(EvaluationAnswers value) { _q3 = value; }
    /*!
     * \brief setQ4
     * \param value
     */
    void setQ4(EvaluationAnswers value) { _q4 = value; }
    /*!
     * \brief setQ5
     * \param value
     */
    void setQ5(EvaluationAnswers value) { _q5 = value; }
    /*!
     * \brief setQ6
     * \param value
     */
    void setQ6(EvaluationAnswers value) { _q6 = value; }
    /*!
     * \brief setQ7
     * \param value
     */
    void setQ7(EvaluationAnswers value) { _q7 = value; }
    /*!
     * \brief setQ8
     * \param value
     */
    void setQ8(EvaluationAnswers value) { _q8 = value; }
    /*!
     * \brief setCallBackPermissions
     * \param value
     */
    void setCallBackPermissions(EvaluationAnswers value) { _callBackPermissions = value; }
    /*!
     * \brief setPromoPermissions
     * \param value
     */
    void setPromoPermissions(EvaluationAnswers value) { _promoPermissions = value; }
    /*!
     * \brief setCountyOfMediation
     * \param value
     */
    void setCountyOfMediation(CountyIds value) { _countyOfMediation = value; }

    // Required Overrides
    /*!
     * \brief Parse
     * \return
     */
    QString Parse();
    /*!
     * \brief UpdateParse
     * \return
     */
    QString UpdateParse();
    /*!
     * \brief table
     * \return
     */
    QString table();
    /*!
     * \brief DuplicateQuery
     * \return
     */
    QString DuplicateQuery();
    /*!
     * \brief SearchQuery
     * \return
     */
    QString SearchQuery();
    /*!
     * \brief GetIdRowName
     * \return
     */
    QString GetIdRowName();

private:
    QDate _mediationDate;
    QString _mediators, _comments, _name, _email, _dayPhone, _eveningPhone;
    int _q1;
    EvaluationAnswers _q2, _q3, _q4, _q5, _q6, _q7, _q8, _callBackPermissions, _promoPermissions;
    CountyIds _countyOfMediation;

};

#endif // MEDIATIONEVALUATION_H
