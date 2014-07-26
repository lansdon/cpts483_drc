#ifndef ATTORNEYSUPPORTVIEW_H
#define ATTORNEYSUPPORTVIEW_H

#include <QWidget>

namespace Ui {
class AttorneySupportView;
}

/*!
 * \brief The AttorneySupportView class
 */
class AttorneySupportView : public QWidget
{
    Q_OBJECT

public:
    explicit AttorneySupportView(QWidget *parent = 0);
    ~AttorneySupportView();

private:
    Ui::AttorneySupportView *ui;
};

#endif // ATTORNEYSUPPORTVIEW_H
