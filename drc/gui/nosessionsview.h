#ifndef NOSESSIONSVIEW_H
#define NOSESSIONSVIEW_H

#include <QWidget>

namespace Ui {
class NoSessionsView;
}

/*!
 * \brief The NoSessionsView class
 */
class NoSessionsView : public QWidget
{
    Q_OBJECT

public:
    explicit NoSessionsView(QWidget *parent = 0);
    ~NoSessionsView();

private slots:
    /*!
     * \brief on_clickToAddSessionPushButton_clicked
     */
    void on_clickToAddSessionPushButton_clicked();

private:
    Ui::NoSessionsView *ui;
signals:
    /*!
     * \brief sendAddNewSession
     */
    void sendAddNewSession();
};

#endif // NOSESSIONSVIEW_H
