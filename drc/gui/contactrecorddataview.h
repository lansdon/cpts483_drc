#ifndef CONTACTRECORDDATAVIEW_H
#define CONTACTRECORDDATAVIEW_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class ContactRecordDataView;
}

/*!
 * \brief The ContactRecordDataView class
 */
class ContactRecordDataView : public QWidget
{
    Q_OBJECT

public:
    explicit ContactRecordDataView(QWidget *parent = 0);
    ~ContactRecordDataView();

private:
    Ui::ContactRecordDataView *ui;
};

#endif // CONTACTRECORDDATAVIEW_H
