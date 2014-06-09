#include "searchwizardresults.h"

#include <QVBoxLayout>
#include <QTableWidget>
#include "searchwizard.h"
#include <QHeaderView>
#include <persondetailsform.h>


SearchWizardResults::SearchWizardResults(QWidget *parent)
{
    setTitle("Search Results");
//    setSubTitle("Enter fields to search with. More parameters will result in fewer results.");


}


void SearchWizardResults::initializePage()
{
    _searchType = field(FIELD_SEARCH_TYPE).toInt();

    QVBoxLayout* layout = new QVBoxLayout();
    ConfigResultsTable();
    layout->addWidget(_resultTable);
    setLayout(layout);
}

void SearchWizardResults::ConfigResultsTable()
{
    _resultTable = new QTableWidget();
    switch(_searchType)
    {
    case SEARCH_T_CALL_LOG:
        _resultTableHeader <<"#"<<"Date"<<"Caller"<<"Operator"<<"Phone #"<<"Reason"<<"Message";
  //      _resultTable->setRowCount(10);
        _resultTable->setColumnCount(7);
        break;

    case SEARCH_T_MEDIATION:
        _resultTableHeader <<"#"<<"Party 1"<<"Party 2"<<"Status"<<"Next Date"<<"Creation Date"<<"Outcome";
//        _resultTable->setRowCount(10);
        _resultTable->setColumnCount(7);
        break;

    case SEARCH_T_PERSON:
        _resultTableHeader <<"#"<<"Name"<<"Phone"<<"Email"<<"Address"<<"County"<<"Attorney";
//        _resultTable->setRowCount(10);
        _resultTable->setColumnCount(7);
        break;

    default:
        break;
    }

//    _resultTable = ui->childrenTable;
    _resultTable->setHorizontalHeaderLabels(_resultTableHeader);
    _resultTable->verticalHeader()->setVisible(false);
//    _resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _resultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _resultTable->setSelectionMode(QAbstractItemView::SingleSelection);
    _resultTable->setShowGrid(false);
    _resultTable->setStyleSheet("QTableView {selection-background-color: red;}");

    for (int c = 0; c < _resultTable->horizontalHeader()->count(); ++c)
    {
        _resultTable->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    connect( _resultTable, SIGNAL( cellDoubleClicked (int, int) ),
             this, SLOT( ResultCellSelected( int, int ) ) );
}

void SearchWizardResults::PopulateResultsTable()
{
//    for(int row=0; row < (int)_party->GetChildren().size(); ++row)
//    {
//        //insert data
//        Person* o = _party->GetChildren()[row];

//        _childrenTable->setItem(row, CCOL_ID, new QTableWidgetItem(QString::number(row+1)));

//        _childrenTable->setItem(row, CCOL_NAME, new QTableWidgetItem(o->FullName()));
//    }
}

void SearchWizardResults::ResultCellSelected(int nRow, int nCol)
{
//    PersonDetailsForm* editWindow = new PersonDetailsForm(this, _party->GetChildren()[nRow], true);
//    editWindow->setWindowFlags(Qt::Popup);

//    connect(editWindow, SIGNAL(PersonDeleted(Person*)), this, SLOT(ChildDeleted(Person*)));
//    connect(editWindow, SIGNAL(PersonSaved(Person*)), this, SLOT(ChildChanged(Person*)));

//    editWindow->show();
}
