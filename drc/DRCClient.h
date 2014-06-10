#ifndef DRCCLIENT_H
#define DRCCLIENT_H

#include <QMainWindow>
#include <QString>
#include "drcbl.h"
#include "drcdb.h"
#include "fruitnameform.h"
#include "mediationprocessview.h"

namespace Ui {
class DRCClient;
}

class DRCClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit DRCClient(QWidget *parent = 0);
    ~DRCClient();

    // This will update the gui menus based on current user status.
    void CurrentUserChanged(MediatorArg arg);

private slots:

    void on_actionNew_Fruit_Submission_triggered();

    void on_actionNew_Form_triggered();

    void on_actionNew_search_form_triggered();

    void on_actionOpen_mediation_view_triggered();

    void on_actionMediation_Process_triggered();

    void on_actionFruit_Test_triggered();

private:
    Ui::DRCClient *ui;

    // Important!! These objects are automatically initialized.
    // They need to be instantiated at startup to register events properly.
    DRCBL _bl;  // Business Logic
    DRCDB _db;  // Database

    // Sub views
    //FruitNameForm* _fruitForm;

    void SetMainView(QWidget* widget);
    void SetMenusEnabled(bool enableMenus, bool showAdmin);

};

#endif // DRCClient_H
