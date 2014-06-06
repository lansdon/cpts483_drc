#ifndef CHILDRENVIEW_H
#define CHILDRENVIEW_H

#include <QWidget>

namespace Ui {
class ChildrenView;
}

class ChildrenView : public QWidget
{
    Q_OBJECT

public:
    explicit ChildrenView(QWidget *parent = 0);
    ~ChildrenView();

private:
    Ui::ChildrenView *ui;
};

#endif // CHILDRENVIEW_H
