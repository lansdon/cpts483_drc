#ifndef ATTORNEYANDSUPPORTFORMEDIATIONSESSIONVIEW_H
#define ATTORNEYANDSUPPORTFORMEDIATIONSESSIONVIEW_H

#include <QWidget>

namespace Ui {
class AttorneyAndSupportForMediationSessionView;
}

class AttorneyAndSupportForMediationSessionView : public QWidget
{
    Q_OBJECT

public:
    explicit AttorneyAndSupportForMediationSessionView(QWidget *parent = 0);
    ~AttorneyAndSupportForMediationSessionView();
    void setAttorney(QString input);
    void setSupport(QString input);
    std::string getAttorney();
    std::string getSupport();

private slots:
    void on_attorneyLineEdit_textChanged(const QString &arg1);

private:
    Ui::AttorneyAndSupportForMediationSessionView *ui;
    bool _attorneyFieldEdited;
};

#endif // ATTORNEYANDSUPPORTFORMEDIATIONSESSIONVIEW_H
