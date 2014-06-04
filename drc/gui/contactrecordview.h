#ifndef CONTACTRECORDVIEW_H
#define CONTACTRECORDVIEW_H

#include <QWidget>
#include "contactrecorddataview.h"

namespace Ui {
class ContactRecordView;
}

class ContactRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit ContactRecordView(QWidget *parent = 0);
    ~ContactRecordView();

private:
    Ui::ContactRecordView *ui;
};

#endif // CONTACTRECORDVIEW_H
