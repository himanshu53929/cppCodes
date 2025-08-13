#include "InventoryWindow.h"
#include "ui_InventoryWindow.h"
#include <QString>
#include <QMessageBox>
#include "Inventory.h"
#include "Transaction.h"
#include "Date.h"
#include "TransactionManager.h"


InventoryWindow::InventoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InventoryWindow)
{
    ui->setupUi(this);

    showMaximized();

}

InventoryWindow::~InventoryWindow()
{
    delete ui;
}

namespace data{
QString account_no;
QString transaction_nature;
int quantity;
QString item_name;
QString description;
QDate date;
double amount;
QString type;
double credit;
double debit;
double rate;
Transaction transaction;
TransactionManager transactionManager;
}

void InventoryWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "From Hacker", "Do you really want to submit the details?");

    if(reply == QMessageBox::Yes){
        //Gets data from the ui or the window and stores it on sumbit button clicked
        data::account_no = ui->account_no->text();
        data::transaction_nature = ui->transaction_nature->currentText();
        data::quantity = ui->quantity->value();
        data::item_name = ui->item_name->text();
        data::description = ui->description->toPlainText();
        data::date = ui->date->date();

        //To get the price of the item
        inventory = new Inventory;

        QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";
        inventory->loadInventoryFromFile(inventoryFilePath.toStdString());

        data::rate = inventory->getPriceByName(data::item_name.toStdString());

        if(data::rate == -1){
            QMessageBox::critical(this, "Error", "Item not found in Inventory");
        }

        else{
            data::amount = data::quantity * data::rate;

            //Sets credit and debit
            if(data::transaction_nature == "Sales" || data::transaction_nature == "Purchase Return") {
                data::type = "debit";
                data::debit = data::amount;
                data::credit = 0.0;

                QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";
                inventory->updateQuantity(data::item_name.toStdString(), -data::quantity, inventoryFilePath.toStdString()); // reduce stock
            }

            else {
                data::type = "credit";
                data::credit = data::amount;
                data::debit = 0.0;

                QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";
                inventory->updateQuantity(data::item_name.toStdString(), data::quantity, inventoryFilePath.toStdString()); // increase stock
            }

            Date date(data::date);

            data::transaction = Transaction(data::account_no.toInt(), data::transaction_nature.toStdString(),
                                        data::item_name.toStdString(), data::description.toStdString(),
                                        data::rate, data::amount, data::quantity, date);

        }
    }

}



void InventoryWindow::on_add_transaction_btn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "From Hacker", "Do you really want to add the current transaction?");

    if(reply == QMessageBox::Yes){
        data::transactionManager.addTransaction(data::transaction);

        QMessageBox::information(this, "From Hacker", "Transaction added Sucessfully!!");
    }

}



void InventoryWindow::on_save_transaction_btn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "From Hacker", "Do you really want to save the current transaction?");

    if(reply == QMessageBox::Yes){
        QString filePath = QCoreApplication::applicationDirPath() + "/data/transaction.txt";

        data::transaction.saveToFile(filePath.toStdString());
        QMessageBox::information(this, "From Hacker", "Transaction saved Sucessfully!!");
    }

}


void InventoryWindow::on_back_btn_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}

