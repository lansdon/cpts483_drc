#ifndef SESSIONOVERVIEW_H
#define SESSIONOVERVIEW_H

#include <QWidget>
#include "drctypes.h"
#include "DRCModels.h"


namespace Ui {
class SessionOverview;
}

/*!
 * \brief The SessionOverview class
 */
class SessionOverview : public QWidget
{
    Q_OBJECT

public:
    explicit SessionOverview(QWidget *parent = 0, MediationSessionVector *mediationSessionVector = nullptr);
    ~SessionOverview();
    /*!
     * \brief setNumberOfSessions
     * \param value
     */
    void setNumberOfSessions(uint value);

private slots:
    /*!
     * \brief on_pushButton_clicked
     */
    void on_pushButton_clicked();

private:
    Ui::SessionOverview *ui;
    MediationSessionVector *_mediationSessionVector;
    uint _numberOfSessions;
    /*!
     * \brief updateView
     */
    void updateView();
};

#endif // SESSIONOVERVIEW_H
