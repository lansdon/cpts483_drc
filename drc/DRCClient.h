#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include <QMainWindow>
#include <QString>
//#include "drc_shared/models//Intake.h"
#include "bl/drcbl.h"
#include "db/drcdb.h"
#include "fruitnameform.h"

namespace Ui {
class DRCClient;
}

class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

private slots:

    void on_actionNew_Fruit_Submission_triggered();

    void on_actionNew_Form_triggered();

private:
    Ui::DRCClient *ui;

    // Important!! These objects are automatically initialized.
    // They need to be instantiated at startup to register events properly.
    DRCBL _bl;  // Business Logic
    DRCDB _db;  // Database

    // Sub views
    //FruitNameForm* _fruitForm;

    void SetMainView(QWidget* widget);
};

#endif // DRCClient_H
