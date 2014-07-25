#include "manageusers.h"
#include "ui_manageusers.h"

// Temp
#include <iostream>

ManageUsers::ManageUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageUsers)
{
    ui->setupUi(this);

    _admin = false;
    _passwordMatch = false;
    _selectedUser = nullptr;

    //configure look of group boxes
    ui->groupBox->setStyleSheet("QGroupBox {\
                                border: 2px solid gray;\
                                border-radius: 5px;\
                                margin-top: 10px;\
                                } QGroupBox::title { subcontrol-origin: margin;\
                                subcontrol-position: top left;\
                                padding:0 3px;\
                                }");

    // Make it so the passwords entered can't be seen.
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->reenterpasswordLineEdit->setEchoMode(QLineEdit::Password);

    // Mediator method registers
    _mediatorId_GetAllUsers = Mediator::Register(MKEY_DB_RETURN_ALL_USER, [this](MediatorArg arg){GetAllUsers(arg);});
    _mediatorId_VerifyRemoveUser = Mediator::Register(MKEY_DB_VERIFY_REMOVE_USER, [this](MediatorArg arg) {VerifyDeleteUser(arg);});
    _mediatorId_VerifyAddUser = Mediator::Register(MKEY_DB_VERIFY_ADD_NEW_USER, [this](MediatorArg arg) {VerifyAddNewUser(arg);});
    _mediatorId_VerifyUpdateUser = Mediator::Register(MKEY_DB_VERIFY_UPDATE_USER, [this](MediatorArg arg) {VerifyUpdateUser(arg);});
    Mediator::Call(MKEY_DB_GET_ALL_USER);

    //  Configure and populate our user table
    ConfigureUserTableView();
    PopulateUserTableView();
}

ManageUsers::~ManageUsers()
{
    //  Delete our UI interface
    delete ui;

    //  Unregister all of our registered mediator callback functions
    Mediator::Unregister(MKEY_DB_RETURN_ALL_USER, _mediatorId_GetAllUsers);
    Mediator::Unregister(MKEY_DB_VERIFY_REMOVE_USER, _mediatorId_VerifyRemoveUser);
    Mediator::Unregister(MKEY_DB_VERIFY_ADD_NEW_USER, _mediatorId_VerifyAddUser);
    Mediator::Unregister(MKEY_DB_VERIFY_UPDATE_USER, _mediatorId_VerifyUpdateUser);
}

void ManageUsers::ConfigureUserTableView()
{
    //  Configures our user table

    //  Sets the alignment of our labels to center justified
    ui->MatchingPasswordLabel->setAlignment(Qt::AlignCenter);
    ui->ButtonStatusLabel->setAlignment(Qt::AlignCenter);

    //  Set the column count and widths of user table
    ui->usertableWidget->setColumnCount(2);

    //  Define the user table horizontal header and set it's alignment
    ui->usertableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Username"));
    ui->usertableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Admin Status"));

    for (int c = 0; c < ui->usertableWidget->horizontalHeader()->count(); ++c)
    {
        ui->usertableWidget->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    //  Set the vertical header to be invisible:  Not used in this program
    ui->usertableWidget->verticalHeader()->setVisible(false);

    //  Define the method by which users are selected from the user table
    ui->usertableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->usertableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->usertableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //  Show the grid and define it's style sheet
    ui->usertableWidget->setShowGrid(true);
    ui->usertableWidget->setStyleSheet("QTableView {selection-background-color: AntiqueWhite; selection-color: Black;}");
}

void ManageUsers::PopulateUserTableView()
{
    //  Populates the user table with users from _userVector

    //  Call all methods registered under the given key.  In this case
    //  we're requesting a QVector* of Users* from the database
    Mediator::Call(MKEY_DB_GET_ALL_USER);

    //  Clear the user table and set the row count
    ui->usertableWidget->clear();
    ui->usertableWidget->setRowCount(_userVector->count());

    // Force headers ?
    ui->usertableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Username"));
    ui->usertableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Admin Status"));

    //  Iterate through _userVector and populate user table with
    //  the appropriate information
    for (int row = 0; row < _userVector->count(); row++)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(_userVector->at(row)->GetName());
        item1->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *item2 = new QTableWidgetItem(_userVector->at(row)->GetType() == USER_T_ADMIN ? "Yes" : "No");
        item2->setTextAlignment(Qt::AlignCenter);

        ui->usertableWidget->setItem(row, 0, item1);
        ui->usertableWidget->setItem(row, 1, item2);
    }
}

void ManageUsers::GetAllUsers(MediatorArg arg)
{
    //  Mediator registered method
    //  Key:  MKEY_DB_RETURN_ALL_USER
    //
    if (arg.IsSuccessful())
    {
        _userVector = arg.getArg<QVector<User*>*>();
    }
}

void ManageUsers::VerifyUpdateUser(MediatorArg arg)
{
    if (arg.IsSuccessful())
    {
        _selectedUser = nullptr;
        ui->usernameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->reenterpasswordLineEdit->setText("");
        ui->IsAdminBox->setChecked(false);

        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : green}");
        ui->ButtonStatusLabel->setText("User updated!");
    }
    else
    {
        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : red}");
        ui->ButtonStatusLabel->setText("Could not update user!");
    }

    PopulateUserTableView();
}

void ManageUsers::VerifyDeleteUser(MediatorArg arg)
{
    std::cout << "is this twerkingE?" << std::endl;
    if (arg.IsSuccessful())
    {
        _selectedUser = nullptr;
        ui->usernameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->reenterpasswordLineEdit->setText("");
        ui->IsAdminBox->setChecked(false);

        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : green}");
        ui->ButtonStatusLabel->setText("User deleted!");
    }
    else
    {
        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : red}");
        ui->ButtonStatusLabel->setText("Could not delete user!");
    }

    PopulateUserTableView();
}

void ManageUsers::VerifyAddNewUser(MediatorArg arg)
{
    if (arg.IsSuccessful())
    {
        _selectedUser = nullptr;
        ui->usernameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->reenterpasswordLineEdit->setText("");
        ui->IsAdminBox->setChecked(false);

        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : green}");
        ui->ButtonStatusLabel->setText("New user added!");
    }
    else
    {
        ui->ButtonStatusLabel->setStyleSheet("QLabel {color : red}");
        ui->ButtonStatusLabel->setText("Could not add new user!");
    }

    PopulateUserTableView();
}



void ManageUsers::on_AddUserButton_clicked()
{
    if (_passwordMatch && _username != "" && _password != "")
    {
        User *newUser = new User();
        newUser->SetName(_username);
        newUser->SetPassword(_password);
        newUser->SetType((_admin == true ? USER_T_ADMIN : USER_T_NORMAL));
        _selectedUser = newUser;

        MediatorArg arg;
        arg.SetArg(newUser);
        Mediator::Call(MKEY_DB_ADD_NEW_USER, arg);
    }
    else if (!_passwordMatch)
    {
        ui->ButtonStatusLabel->setText("Passwords must match before adding a user!");
    }
    else if (_password == "")
    {
        ui->ButtonStatusLabel->setText("Must enter a password before adding a user!");
    }
    else if (_username == "")
    {
        ui->ButtonStatusLabel->setText("Must enter a username before adding a user!");
    }
}

void ManageUsers::on_DeleteUserButton_clicked()
{
    ui->ButtonStatusLabel->setStyleSheet("QLabel {color : red}");
    if (_selectedUser != nullptr)
    {
        MediatorArg arg;
        arg.SetArg(_selectedUser);
        Mediator::Call(MKEY_DB_REMOVE_USER, arg);
    }
    else
    {
        ui->ButtonStatusLabel->setText("Please select a user to delete!");
    }
}

void ManageUsers::on_usernameLineEdit_editingFinished()
{
    _username = ui->usernameLineEdit->text();
}

void ManageUsers::on_passwordLineEdit_editingFinished()
{
    _password = ui->passwordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_editingFinished()
{
    _reenteredpassword = ui->reenterpasswordLineEdit->text();
}

void ManageUsers::on_reenterpasswordLineEdit_textChanged(const QString &arg1)
{
    if (arg1 != _password)
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : red}");
        ui->MatchingPasswordLabel->setText("No Match!!");

        _passwordMatch = false;
    }
    else
    {
        ui->MatchingPasswordLabel->setStyleSheet("QLabel {color : green}");
        ui->MatchingPasswordLabel->setText("Match!");

        _passwordMatch = true;
    }
}

void ManageUsers::on_IsAdminBox_toggled(bool checked)
{
    _admin = checked;
}

void ManageUsers::on_usertableWidget_doubleClicked(const QModelIndex &index)
{
    if(index.row() >= 0 && index.row() < (int)_userVector->size())
    {
        _selectedUser = _userVector->at(index.row());
        ui->usernameLineEdit->setText(_selectedUser->GetName());
        _username = _selectedUser->GetName();
        ui->IsAdminBox->setChecked(_selectedUser->GetType() == USER_T_ADMIN ? true: false);
        ui->passwordLineEdit->setText("");
        ui->MatchingPasswordLabel->setText("");
    }
}

void ManageUsers::on_UpdateUserButton_clicked()
{
    ui->ButtonStatusLabel->setStyleSheet("QLabel {color : red}");
    if (_passwordMatch && _username != "" && _password != "")
    {
        User *newUser = new User();
        newUser->SetName(_username);
        newUser->SetPassword(_password);
        newUser->SetType((_admin == true ? USER_T_ADMIN : USER_T_NORMAL));
        _selectedUser = newUser;

        MediatorArg arg;
        arg.SetArg(newUser);
        Mediator::Call(MKEY_DB_UPDATE_USER, arg);
    }
    else if (!_passwordMatch)
    {
        ui->ButtonStatusLabel->setText("Passwords must match before updating a user!");
    }
    else if (_password == "")
    {
        ui->ButtonStatusLabel->setText("Must enter a password befoer updating a user!");
    }
    else if (_username == "")
    {
        ui->ButtonStatusLabel->setText("Must enter a username before updating a user!");
    }
}
