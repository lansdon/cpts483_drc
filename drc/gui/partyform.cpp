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
    PersonDetailsForm* personDetailsForm = new PersonDetailsForm(this, party->GetPrimary());
    connect(personDetailsForm,SIGNAL(SaveSignaled()),this,SLOT(DoSaveSignal()));
    connect(personDetailsForm,SIGNAL(EditSignaled()),this,SLOT(DoEditSignal()));
    gridLayout->addWidget(personDetailsForm);

    ui->primaryFrame->setLayout(gridLayout);

}
//void PartyForm::savePersonContactFromclose(Person *value)
//{
////    emit PassItOn(value);
//}

PartyForm::~PartyForm()
{
    delete ui;
}

void PartyForm::setParty(Party *value)
{
    _party = value;
    _personDetailsForm->SetPerson(_party->GetPrimary());
//    ConfigObserverTable();
//    PopulateObserverTable();

//    ConfigChildrenTable();
//    PopulateChildrenTable();
}

//void PartyForm::ObserverCellSelected(int nRow, int nCol)
//{
//    PersonDetailsForm* editWindow = new PersonDetailsForm(this, _party->GetObservers()[nRow], true);
//    editWindow->setWindowFlags(Qt::Popup);

//    connect(editWindow, SIGNAL(PersonDeleted(Person*)), this, SLOT(ObserverDeleted(Person*)));
//    connect(editWindow, SIGNAL(PersonSaved(Person*)), this, SLOT(ObserverChanged(Person*)));

//    editWindow->show();
//}

//void PartyForm::ChildCellSelected(int nRow, int nCol)
//{
//    PersonDetailsForm* editWindow = new PersonDetailsForm(this, _party->GetChildren()[nRow], true);
//    editWindow->setWindowFlags(Qt::Popup);

//    connect(editWindow, SIGNAL(PersonDeleted(Person*)), this, SLOT(ChildDeleted(Person*)));
//    connect(editWindow, SIGNAL(PersonSaved(Person*)), this, SLOT(ChildChanged(Person*)));

//    editWindow->show();
//}

//void PartyForm::ConfigObserverTable()
//{
//    _observerTable = ui->observerTable;
//    _observerTable->setRowCount(_party->GetObservers().size());
//    _observerTable->setColumnCount(3);
//    _observerTableHeader <<"#"<<"Name"<<"Role";
//    _observerTable->setHorizontalHeaderLabels(_observerTableHeader);
//    _observerTable->verticalHeader()->setVisible(false);
//    _observerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    _observerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    _observerTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    _observerTable->setShowGrid(false);
//    _observerTable->setStyleSheet("QTableView {selection-background-color: red;}");

//    for (int c = 0; c < _observerTable->horizontalHeader()->count(); ++c)
//    {
//        _observerTable->horizontalHeader()->setSectionResizeMode(
//            c, QHeaderView::Stretch);
//    }

//    connect( _observerTable, SIGNAL( cellDoubleClicked (int, int) ),
//             this, SLOT( ObserverCellSelected( int, int ) ) );
//}

//void PartyForm::PopulateObserverTable()
//{
//    for(int row=0; row < (int)_party->GetObservers().size(); ++row)
//    {
//        //insert data
//        Person* o = _party->GetObservers()[row];

//        _observerTable->setItem(row, OCOL_ID, new QTableWidgetItem(QString::number(row+1)));

//        _observerTable->setItem(row, OCOL_NAME, new QTableWidgetItem(o->FullName()));
//    }
//}

//void PartyForm::ConfigChildrenTable()
//{
//    _childrenTable = ui->childrenTable;
//    _childrenTable->setRowCount(_party->GetChildren().size());
//    _childrenTable->setColumnCount(3);
//    _childrenTableHeader <<"#"<<"Name"<<"Directly Involved";
//    _childrenTable->setHorizontalHeaderLabels(_childrenTableHeader);
//    _childrenTable->verticalHeader()->setVisible(false);
//    _childrenTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    _childrenTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    _childrenTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    _childrenTable->setShowGrid(false);
//    _childrenTable->setStyleSheet("QTableView {selection-background-color: red;}");

//    for (int c = 0; c < _childrenTable->horizontalHeader()->count(); ++c)
//    {
//        _childrenTable->horizontalHeader()->setSectionResizeMode(
//            c, QHeaderView::Stretch);
//    }

//    connect( _childrenTable, SIGNAL( cellDoubleClicked (int, int) ),
//             this, SLOT( ChildCellSelected( int, int ) ) );
//}

//void PartyForm::PopulateChildrenTable()
//{
//    for(int row=0; row < (int)_party->GetChildren().size(); ++row)
//    {
//        //insert data
//        Person* o = _party->GetChildren()[row];

//        _childrenTable->setItem(row, CCOL_ID, new QTableWidgetItem(QString::number(row+1)));

//        _childrenTable->setItem(row, CCOL_NAME, new QTableWidgetItem(o->FullName()));
//    }
//}

//void PartyForm::ObserverChanged(Person* p)
//{
//    PopulateObserverTable();

//    // To-do persist changes!
//}

//void PartyForm::ObserverDeleted(Person* p)
//{
//    _party->RemoveObserver(p);

//    PopulateObserverTable();

//    // To-do persist changes!
//}

//void PartyForm::ChildChanged(Person* p)
//{
//    PopulateChildrenTable();

//    // To-do persist changes!
//}

//void PartyForm::ChildDeleted(Person* p)
//{
//    qDebug() << "Child deleted callback.";

//    _party->RemoveChild(p);

//    PopulateChildrenTable();

//    // To-do persist changes!
//}
