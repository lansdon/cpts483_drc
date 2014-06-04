#ifndef QUERYFORM_H
#define QUERYFORM_H

#include <QWidget>
#include "partydetailsform.h"

namespace Ui {
class QueryForm;
}

class QueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryForm(QWidget *parent = 0);
    ~QueryForm();

private:
    Ui::QueryForm *ui;
};

#endif // QUERYFORM_H
