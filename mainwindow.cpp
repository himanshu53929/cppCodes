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

