#include "ViewLedgerForAccount.h"
#include "ui_ViewLedgerForAccount.h"
#include "TransactionManager.h"
#include<QMessageBox>

namespace dataLedger{
QString accountNumber;
}

ViewLedgerForAccount::ViewLedgerForAccount(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewLedgerForAccount)
{
    ui->setupUi(this);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ViewLedgerForAccount::~ViewLedgerForAccount()
{
    delete ui;
}

void ViewLedgerForAccount::on_back_button_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}


void ViewLedgerForAccount::on_display_button_clicked()
{
    dataLedger::accountNumber = ui->account_number_ledger->text();

    TransactionManager transactionManager;
    bool state;
    state = transactionManager.loadFromFile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/transaction.txt");
    if(state == false){
        QMessageBox::critical(this, "Error", "File was not loaded sucessfully!!, Returning to main window");
        if(parentWidget()){
            parentWidget() -> show();
        }

        this -> close();
        return;
    }

    Ledger ledger;
    ledger.loadFromTransactions(transactionManager.getAllTransactions());

    ui->table->setRowCount(0);

    float debitTotal = 0, creditTotal = 0;
    int i = 0;
    for(const LedgerEntry& entry: ledger.returnLedger()){
        if(dataLedger::accountNumber.toInt() == entry.account){
            ui->table->setRowCount(i+1);

            std::string direction = (entry.type == "debit") ? "To " : "By ";
            std::string particulars = direction + entry.nature + " A/c";

            if(direction == "To "){
                debitTotal += entry.amount;
                ui->table->setItem(i, 0, new QTableWidgetItem(entry.date.toQString()));
                ui->table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(particulars)));
                ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(entry.amount, 'f', 2)));
                ui->table->setItem(i, 3, new QTableWidgetItem(QString("Null")));
                ui->table->setItem(i, 4, new QTableWidgetItem(QString("Null")));
                ui->table->setItem(i, 5, new QTableWidgetItem(QString("Null")));
            }

            else{
                creditTotal += entry.amount;
                ui->table->setItem(i, 0, new QTableWidgetItem(QString("Null")));
                ui->table->setItem(i, 1, new QTableWidgetItem(QString("Null")));
                ui->table->setItem(i, 2, new QTableWidgetItem(QString("Null")));
                ui->table->setItem(i, 3, new QTableWidgetItem(entry.date.toQString()));
                ui->table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(particulars)));
                ui->table->setItem(i, 5, new QTableWidgetItem(QString::number(entry.amount, 'f', 2)));
            }

            i++;
        }
    }


    if(i == 0){
        QMessageBox::critical(this, "Error", "Account Number didn't match with any entry.");
    }

    else{
        if(debitTotal>creditTotal){
            i++;
            ui->table->setRowCount(i+1);

            ui->table->setItem(i, 3, new QTableWidgetItem(QString("Null")));
            ui->table->setItem(i, 4, new QTableWidgetItem(QString("To Balance c/d*")));
            ui->table->setItem(i, 5, new QTableWidgetItem(QString::number(debitTotal-creditTotal, 'f', 2)));
        }

        else{
            i++;
            ui->table->setRowCount(i+1);

            ui->table->setItem(i, 0, new QTableWidgetItem(QString("Date")));
            ui->table->setItem(i, 1, new QTableWidgetItem(QString("To Balance c/d*")));
            ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(debitTotal-creditTotal, 'f', 2)));
        }
    }
}

