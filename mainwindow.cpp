#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "User.h"
#include<QString>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();
    TransactionManager transactionManager;
    bool state;
    QString filePath = QCoreApplication::applicationDirPath() + "/data/transaction.txt";

    state = transactionManager.loadFromFile(filePath.toStdString());
    if(state == false){
        QMessageBox::critical(this, "Error", "File was not loaded sucessfully!!, Returning to main window");
        if(parentWidget()){
            parentWidget() -> show();
        }

        this -> close();
    }

    Inventory inventory;
    QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";
    inventory.loadInventoryFromFile(inventoryFilePath.toStdString());

    ptr_report = new Report(transactionManager, inventory);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_transaction_clicked()
{
    hide();
    invetWin = new InventoryWindow(this);
    invetWin -> show();
}


void MainWindow::on_view_inventory_clicked()
{
    hide();
    viewInventWin = new ViewInventoryWindow(this);
    viewInventWin -> show();
}



void MainWindow::on_add_items_to_inventory_clicked()
{   User user;

    QString userFilePath = QCoreApplication::applicationDirPath() + "/data/user.txt";
    user.loadUsersFromFile(userFilePath.toStdString());
    if(user.isAdmin(User::currentUser))
    {
        hide();
        AddItemsToInventWin = new AddItemsToInventoryWindow(this);
        AddItemsToInventWin -> show();
    }

    else{
        QMessageBox:: critical(this, "Error", "Admin Required for Modifying Inventory");
    }
}


void MainWindow::on_exit_clicked()
{
    close();
}


void MainWindow::on_view_tansaction_clicked()
{
    hide();
    viewTransactionWin = new ViewTransactionWindow(this);
    viewTransactionWin -> show();
}

void MainWindow::on_view_ledger_for_account_clicked()
{
    hide();
    viewLedgerForAcc = new ViewLedgerForAccount(this);
    viewLedgerForAcc -> show();
}


void MainWindow::on_profit_loss_button_clicked()
{
    hide();
    profitLossWin = new ProfitLossWindow(this);
    profitLossWin -> show();
}


void MainWindow::on_export_report_button_clicked()
{
    dialog = new QDialog();

    font.setFamily("Arial");
    font.setPointSize(12);

    dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    dialog->setMaximumHeight(135);
    dialog->setMinimumWidth(800);
    dialog->show();

    QLabel* label = new QLabel();
    label->setParent(dialog);
    label->setGeometry(10, 10, 450, 50);
    label->setText("Enter the name of the file to genrate the report in .txt format");
    label->show();
    label->setFont(font);

    line = new QLineEdit();
    line->setParent(dialog);
    line->show();
    line->setGeometry(480, 15, 300, 35);
    line->setFont(font);

    QPushButton* button = new QPushButton();
    connect(button, &QPushButton::clicked, this, &MainWindow::on_submit_button_clicked);
    button->setParent(dialog);
    button->setText("Submit");
    button->setGeometry(700, 80, 80, 30);
    button->show();
    button->setFont(font);

}

void MainWindow::on_submit_button_clicked()
{
    QString fileName;
    fileName = line->text();
    bool state;
    std::string file = fileName.toStdString();
    state = ptr_report->exportReport(file);

    if(state == false){
        QMessageBox:: critical(this, "Error", "File wasn't exported sucessfully!!!");
    }

    else{
        QMessageBox:: information(this, "Congratulations", "File was successfully exported!");
    }

    dialog->close();
    dialog->deleteLater();
}


void MainWindow::on_inventory_summary_button_clicked()
{
    hide();
    generateInventorySummaryWin = new GenerateInventorySummaryWindow(this);
    generateInventorySummaryWin -> show();
}




void MainWindow::on_add_user_button_clicked()
{
    User user;

    QString userFilePath = QCoreApplication::applicationDirPath() + "/data/user.txt";

    user.loadUsersFromFile(userFilePath.toStdString());

    if(user.isAdmin(User::currentUser)){
        newUser = new QDialog();

        font.setFamily("Arial");
        font.setPointSize(12);

        newUser->setWindowModality(Qt::WindowModality::ApplicationModal);
        newUser->setMaximumHeight(265);
        newUser->setMinimumWidth(800);
        newUser->show();

        QLabel* label = new QLabel();
        label->setParent(newUser);
        label->setGeometry(10, 10, 450, 50);
        label->setText("Enter new User's Name");
        label->show();
        label->setFont(font);

        newUserName = new QLineEdit();
        newUserName->setParent(newUser);
        newUserName->show();
        newUserName->setGeometry(480, 15, 300, 35);
        newUserName->setFont(font);

        QLabel* label1 = new QLabel(newUser);
        label1->setGeometry(10, 80, 450, 50);
        label1->setText("Enter new User's Password");
        label1->show();
        label1->setFont(font);

        newUserPassword = new QLineEdit();
        newUserPassword->setParent(newUser);
        newUserPassword->show();
        newUserPassword->setGeometry(480, 80, 300, 35);
        newUserPassword->setFont(font);
        newUserPassword->setEchoMode(QLineEdit::Password);

        QCheckBox* checkBox = new QCheckBox("Show Password",newUser);
        checkBox->setGeometry(670, 130, 110, 20);
        checkBox->show();

        connect(checkBox, &QCheckBox::toggled, this, [=](bool checked){
            if(checked){
                newUserPassword->setEchoMode(QLineEdit::Normal);
            }

            else{
                newUserPassword->setEchoMode(QLineEdit::Password);
            }
        });



        QLabel* label2 = new QLabel(newUser);
        label2->setGeometry(10, 170, 450, 50);
        label2->setText("Enter new User's Role");
        label2->show();
        label2->setFont(font);

        roleComboBox = new QComboBox(newUser);
        roleComboBox->setGeometry(480, 185, 300, 35);
        roleComboBox->addItem("Admin");
        roleComboBox->addItem("User");
        roleComboBox->show();
        roleComboBox->setFont(font);



        QPushButton* button = new QPushButton();
        connect(button, &QPushButton::clicked, this, &MainWindow::on_submit_newUser_button_clicked);
        button->setParent(newUser);
        button->setText("Submit");
        button->setGeometry(700, 230, 80, 30);
        button->show();
        button->setFont(font);
    }

    else{
        QMessageBox:: critical(this, "Error", "Access denied!!");
    }
}

void MainWindow::on_submit_newUser_button_clicked()
{
    QString userName = newUserName->text();
    QString userPassword = newUserPassword->text();
    QString userRole = roleComboBox->currentText();
    userRole = userRole.toLower();

    User user;
        QString userFilePath = QCoreApplication::applicationDirPath() + "/data/user.txt";

    user.loadUsersFromFile(userFilePath.toStdString());

    bool state = user.registerUser(userName.toStdString(), userPassword.toStdString(), userRole.toStdString());

    if(state){
        QMessageBox:: information(this, "User Added", "Congratulations!! user was registerd sucessfully.");
    }

    else{
        QMessageBox:: critical(this, "Error", "An error occured");
    }

    newUser->close();
    newUser->deleteLater();
}


void MainWindow::on_log_out_button_clicked()
{
    QMessageBox:: StandardButton answer;
    answer = QMessageBox:: question(this, "Confirmation", "Are you sure to Log Out?");

    if(answer == QMessageBox:: Yes){
        userLoginWindow = new UserLoginWindow;
        userLoginWindow -> show();

        this -> close();
    }
}
