#include "intakeform.h"
#include "ui_intakeform.h"

// Qt
#include <QDebug>

// DRC
#include "drc_shared/mediator/Mediator.h"
#include "drc_shared/mediator/AsyncMediatorCall.h"
#include "drc_shared/models/DRCModels.h"

IntakeForm::IntakeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntakeForm)
{
    ui->setupUi(this);

    // One time setup of async handlers.
    _asyncLoadIntake = new AsyncMediatorCall(MKEY_GUI_LOAD_INTAKE_FORM, MKEY_DB_LOAD_INTAKE_FORM_DONE, [this](MediatorArg arg){ Recieve_LoadIntakeForm(arg); }, nullptr, true);
    _asyncSaveIntake = new AsyncMediatorCall(MKEY_GUI_SUBMIT_INTAKE_FORM, MKEY_DB_PERSIST_INTAKE_FORM_DONE, [this](MediatorArg arg){ Recieve_SaveIntakeForm(arg); }, nullptr, true);

}

IntakeForm::~IntakeForm()
{
    delete ui;
}

void IntakeForm::on_saveButton_clicked()
{
    // SAVE
    qDebug() << "Gui -> SAVE INTAKE FORM PRESSED";
    _asyncSaveIntake->GetMediatorArg().SetArg(&_currentIntake);
    _asyncSaveIntake->Send();
}

void IntakeForm::on_loadButton_clicked()
{
    qDebug() << "gui -> LOAD INTAKE FORM PRESSED";
    _asyncLoadIntake->GetMediatorArg().SetArg(&_currentIntake);
    _asyncLoadIntake->Send();
}

void IntakeForm::on_clearButton_clicked()
{
    qDebug() << "gui -> CLEAR INTAKE FORM PRESSED";

}

// Save Intake Form Callback (result)
void IntakeForm::Recieve_SaveIntakeForm(MediatorArg arg)
{

}

// Load Intake Form Callback (result)
void IntakeForm::Recieve_LoadIntakeForm(MediatorArg arg)
{

}
