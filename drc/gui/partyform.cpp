#include "partyform.h"
#include "ui_partyform.h"
#include "party.h"
#include "persondetailsform.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>


PartyForm::PartyForm(QWidget *parent, Party* party) :
    QWidget(parent),
    ui(new Ui::PartyForm),
    _party(party ? party : new Party())
{
    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout();
//    PersonDetailsForm* primaryForm = new PersonDetailsForm(this);
    gridLayout->addWidget(new PersonDetailsForm(ui->primaryFrame, &(_party->GetPrimary())));
    ui->primaryFrame->setLayout(gridLayout);

    ConfigObserverTable();
    PopulateObserverTable();

    ConfigChildrenTable();
    PopulateChildrenTable();

}

PartyForm::~PartyForm()
{
    delete ui;
}



void PartyForm::ObserverCellSelected(int nRow, int nCol)
{
    PersonDetailsForm* editWindow = new PersonDetailsForm(this, _party->GetObservers()[nRow], true);
    editWindow->setWindowFlags(Qt::Popup);

    connect(editWindow, SIGNAL(PersonDeleted(Person*)), this, SLOT(ObserverDeleted(Person*)));
    connect(editWindow, SIGNAL(PersonSaved(Person*)), this, SLOT(ObserverChanged(Person*)));

    editWindow->show();

//    QMessageBox::information(this, "",
//                            "Observer cell at row "+QString::number(nRow)+
//                             " column "+QString::number(nCol)+
//                             " was double clicked.");
}

void PartyForm::ChildCellSelected(int nRow, int nCol)
{
    QMessageBox::information(this, "",
                            "Child cell at row "+QString::number(nRow)+
                             " column "+QString::number(nCol)+
                             " was double clicked.");
}

void PartyForm::ConfigObserverTable()
{
    _observerTable = ui->observerTable;
    _observerTable->setRowCount(10);
    _observerTable->setColumnCount(3);
    _observerTableHeader <<"#"<<"Name"<<"Role";
    _observerTable->setHorizontalHeaderLabels(_observerTableHeader);
    _observerTable->verticalHeader()->setVisible(false);
    _observerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _observerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _observerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _observerTable->setShowGrid(false);
    _observerTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _observerTable->horizontalHeader()->count(); ++c)
    {
        _observerTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    connect( _observerTable, SIGNAL( cellDoubleClicked (int, int) ),
             this, SLOT( ObserverCellSelected( int, int ) ) );
}

void PartyForm::PopulateObserverTable()
{
    for(int row=0; row < (int)_party->GetObservers().size(); ++row)
    {
        //insert data
        Person* o = _party->GetObservers()[row];

        _observerTable->setItem(row, OCOL_ID, new QTableWidgetItem(QString::number(row+1)));

        _observerTable->setItem(row, OCOL_NAME, new QTableWidgetItem(o->FullName()));
    }
}

void PartyForm::ConfigChildrenTable()
{
    _childrenTable = ui->childrenTable;
    _childrenTable->setRowCount(10);
    _childrenTable->setColumnCount(3);
    _childrenTableHeader <<"#"<<"Name"<<"Directly Involved";
    _childrenTable->setHorizontalHeaderLabels(_childrenTableHeader);
    _childrenTable->verticalHeader()->setVisible(false);
    _childrenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _childrenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _childrenTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _childrenTable->setShowGrid(false);
    _childrenTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _childrenTable->horizontalHeader()->count(); ++c)
    {
        _childrenTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    connect( _childrenTable, SIGNAL( cellDoubleClicked (int, int) ),
             this, SLOT( ChildCellSelected( int, int ) ) );
}

void PartyForm::PopulateChildrenTable()
{
    for(int row=0; row < (int)_party->GetChildren().size(); ++row)
    {
        //insert data
        Person* o = _party->GetChildren()[row];

        _childrenTable->setItem(row, CCOL_ID, new QTableWidgetItem(QString::number(row+1)));

        _childrenTable->setItem(row, CCOL_NAME, new QTableWidgetItem(o->FullName()));
    }
}

void PartyForm::ObserverChanged(Person* p)
{
    PopulateObserverTable();

    // To-do persist changes!
}

void PartyForm::ObserverDeleted(Person* p)
{
    qDebug() << "Observer deleted callback.";

    _party->RemoveObserver(p);

    PopulateObserverTable();

    // To-do persist changes!
}
