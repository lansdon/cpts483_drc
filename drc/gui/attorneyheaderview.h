#ifndef ATTORNEYHEADERVIEW_H
#define ATTORNEYHEADERVIEW_H

#include <QWidget>

namespace Ui {
class AttorneyHeaderView;
}

/*!
 * \brief The AttorneyHeaderView class
 */
class AttorneyHeaderView : public QWidget
{
    Q_OBJECT

public:
    explicit AttorneyHeaderView(QWidget *parent = 0);
    ~AttorneyHeaderView();

private:
    Ui::AttorneyHeaderView *ui;
};

#endif // ATTORNEYHEADERVIEW_H
