#ifndef SESSIONCELL_H
#define SESSIONCELL_H

#include <QWidget>
#include "DRCModels.h"

namespace Ui {
class SessionCell;
}

/*!
 * \brief The SessionCell class
 */
class SessionCell : public QWidget
{
    Q_OBJECT

public:
    explicit SessionCell(QWidget *parent = 0, MediationSession* session = nullptr);
    ~SessionCell();

    /*!
     * \brief SetSession
     * \param session
     */
    void SetSession(MediationSession* session) { _session = session; Populate(); }
    /*!
     * \brief GetSession
     * \return
     */
    MediationSession* GetSession() { return _session; }
private:
    Ui::SessionCell *ui;
    MediationSession *_session;
    /*!
     * \brief Populate
     */
    void Populate();

};

#endif // SESSIONCELL_H
