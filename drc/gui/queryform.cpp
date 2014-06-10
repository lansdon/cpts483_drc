#include "queryform.h"
#include "ui_queryform.h"
#include <QDebug>
#include <QVBoxLayout>
#include "mediationprocessview.h"
#include "persondetailsform.h"
#include "drctypes.h"
#include "Mediator.h"
#include "AsyncMediatorCall.h"
#include "MediatorKeys.h"
#include "MediatorArg.h"

enum PersonTableColumns
{
    PCOL_ID = 0,
    PCOL_NAME,
    PCOL_PHONE,
    PCOL_EMAIL,
    PCOL_ADDRESS,
    PCOL_COUNTY,
    PCOL_ATTORNEY

};

enum MediationTableColumns
{
    OCOL_ID = 0,
    OCOL_NAME,
    OCOL_ROLE
};


QueryForm::QueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryForm),
    _currentInputForm(nullptr),
    _resultsTable(nullptr)
{
    ui->setupUi(this);

    ui->parametersGroupBox->setLayout(new QVBoxLayout(ui->parametersGroupBox));

    ui->resultsTable->setLayout(new QVBoxLayout(ui->resultsTable));


    _asyncQueryPerson = new AsyncMediatorCall(MKEY_GUI_QUERY_PERSON, MKEY_DB_QUERY_PERSON, [this](MediatorArg arg){RecievedPersonResult(arg);}, nullptr, true);

}

QueryForm::~QueryForm()
{
    delete ui;
}

void QueryForm::on_comboBox_currentIndexChanged(const QString &arg1)
{
    // Set the search type (for convenience...)
    if(arg1 == "Mediation")
    {
        _searchType = SEARCH_T_MEDIATION;
     }
    else if(arg1 == "Person")
    {
        _searchType = SEARCH_T_PERSON;
    }
    else if(arg1 == "Call Log")
    {
        _searchType = SEARCH_T_CALL_LOG;
    }

    ConfigureInputForm();
    ConfigResultsTable();
}

void QueryForm::on_searchButton_clicked()
{
    if(_searchType == SEARCH_T_PERSON)
    {
        qDebug() << "Searching Person";
        PersonDetailsForm* f = (PersonDetailsForm*)_currentInputForm;
        f->SetEditMode(false); // causes save
        f->SetEditMode(true);

        _asyncQueryPerson->GetMediatorArg().SetArg(f->GetPerson());
        _asyncQueryPerson->Send();
    }
}

void QueryForm::ConfigureInputForm()
{
    // Delete the old
    if(_currentInputForm)
    {
        delete _currentInputForm;
        _currentInputForm = nullptr;
    }

    // Set the new form
    switch(_searchType)
    {
    case SEARCH_T_CALL_LOG:
        break;

    case SEARCH_T_MEDIATION:
        _currentInputForm = new MediationProcessView(ui->parametersGroupBox);
        break;

    case SEARCH_T_PERSON:
        _currentInputForm = new PersonDetailsForm(ui->parametersGroupBox);
        break;

    default:
        break;
    }

    // Add the new
    if(_currentInputForm)
    {
        ui->parametersGroupBox->layout()->addWidget(_currentInputForm);
    }

}

////////////////////////////////////////////////////////
//          Results - Table View
///////////////////////////////////////////////////////
void QueryForm::ConfigResultsTable()
{
    if(_resultsTable)
    {
        delete _resultsTable;
        _resultsTable = nullptr;
    }

    _resultsTable = new QTableWidget();
    _resultsTableHeader.clear();
    switch(_searchType)
    {
    case SEARCH_T_CALL_LOG:
        _resultsTableHeader <<"#"<<"Date"<<"Caller"<<"Operator"<<"Phone #"<<"Reason"<<"Message";
        _resultsTable->setColumnCount(7);
        break;

    case SEARCH_T_MEDIATION:
        _resultsTableHeader <<"#"<<"Party 1"<<"Party 2"<<"Status"<<"Next Date"<<"Creation Date"<<"Outcome";
        _resultsTable->setColumnCount(7);
        break;

    case SEARCH_T_PERSON:
        _resultsTableHeader <<"#"<<"Name"<<"Phone"<<"Email"<<"Address"<<"County"<<"Attorney";
        _resultsTable->setColumnCount(7);
        break;

    default:
        break;
    }

    _resultsTable->setHorizontalHeaderLabels(_resultsTableHeader);
    _resultsTable->verticalHeader()->setVisible(false);
//    _resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _resultsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _resultsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _resultsTable->setShowGrid(false);
    _resultsTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _resultsTable->horizontalHeader()->count(); ++c)
    {
        _resultsTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    connect( _resultsTable, SIGNAL( cellDoubleClicked (int, int) ),
             this, SLOT( ResultCellSelected( int, int ) ) );

    ui->resultsTable->layout()->addWidget(_resultsTable);
}

void QueryForm::PopulateResultsTable()
{
    if(_searchType == SEARCH_T_PERSON)
    {
        qDebug() << "Person result size=" << _personResults->size();
        _resultsTable->setRowCount(_personResults->size());
        for(int row=0; row < (int)_personResults->size(); ++row)
        {
            //insert data
            Person* o = (*_personResults)[row];
            qDebug() << "Person name=" << o->FullName();
            _resultsTable->setItem(row, PCOL_ID, new QTableWidgetItem(QString::number(row+1)));
            _resultsTable->setItem(row, PCOL_NAME, new QTableWidgetItem(o->FullName()));
            _resultsTable->setItem(row, PCOL_ADDRESS, new QTableWidgetItem(QString::fromStdString(o->getStreet())));
            _resultsTable->setItem(row, PCOL_ATTORNEY, new QTableWidgetItem(QString::fromStdString(o->getAttorney())));
            _resultsTable->setItem(row, PCOL_COUNTY, new QTableWidgetItem(QString::fromStdString(o->getCounty())));
            _resultsTable->setItem(row, PCOL_EMAIL, new QTableWidgetItem(QString::fromStdString(o->getEmail())));
            _resultsTable->setItem(row, PCOL_PHONE, new QTableWidgetItem(QString::fromStdString(o->getPrimaryPhone())));
        }
    }

}

void QueryForm::ResultCellSelected(int nRow, int nCol)
{
//    PersonDetailsForm* editWindow = new PersonDetailsForm(this, _party->GetChildren()[nRow], true);
//    editWindow->setWindowFlags(Qt::Popup);

//    connect(editWindow, SIGNAL(PersonDeleted(Person*)), this, SLOT(ChildDeleted(Person*)));
//    connect(editWindow, SIGNAL(PersonSaved(Person*)), this, SLOT(ChildChanged(Person*)));

//    editWindow->show();
}

void QueryForm::RecievedPersonResult(MediatorArg arg)
{
    qDebug() << "Person Results recieved!";

    if(arg.IsSuccessful())
    {
        PersonVector* result = arg.getArg<PersonVector*>();
        if(result)
        {
            _personResults = new PersonVector(*result);
            PopulateResultsTable();
        }
        else
        {
            qDebug() << "Query person - invalid results";
        }
    }
    else
    {
        qDebug() << "Person Results error:" <<  QString::fromStdString( arg.ErrorMessage() );
    }
}
