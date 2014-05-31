#include "mainmenutabwidget.h"
#include "ui_mainmenutabwidget.h"
//#include "drc_shared/models/Intake.h"
#include "fruitnameform.h"
#include "intakeform.h"

MainMenuTabWidget::MainMenuTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::MainMenuTabWidget)
{
    ui->setupUi(this);

    // Setup the Tabs
    clear();
    addTab(new FruitNameForm(), "Fruit1");
    addTab(new IntakeForm(), "Intake Form");

}

MainMenuTabWidget::~MainMenuTabWidget()
{
    delete ui;
}
