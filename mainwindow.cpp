#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include <iostream>
// #include "Inventory.h"
// #include "Transaction.h"
// #include "TransactionManager.h"
// #include "Ledger.h"

#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    TransactionManager transactionManager;
    bool state;
    state = transactionManager.loadFromFile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/transaction.txt");
    if(state == false){
        QMessageBox::critical(this, "Error", "File was not loaded sucessfully!!, Returning to main window");
        if(parentWidget()){
            parentWidget() -> show();
        }

        this -> close();
    }

    Inventory inventory;
    inventory.loadInventoryFromFile();

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
{
    hide();
    AddItemsToInventWin = new AddItemsToInventoryWindow(this);
    AddItemsToInventWin -> show();
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
    state = ptr_report->exportReport(fileName.toStdString());

    if(state == false){
        QMessageBox:: critical(this, "Error", "File wasn't exported sucessfully!!!");
    }

    else{
        QMessageBox:: information(this, "Congratulations", "File was successfully exported!");
    }

    dialog->close();
    dialog->deleteLater();
}

