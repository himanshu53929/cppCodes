#include "ViewTransactionWindow.h"
#include "ui_ViewTransactionWindow.h"
#include "TransactionManager.h"
#include "QMessageBox"
#include<QTableWidget>
#include<QTableWidgetItem>

ViewTransactionWindow::ViewTransactionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewTransactionWindow)
{
    ui->setupUi(this);

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

    std::vector<Transaction> transactions = transactionManager.getAllTransactions();

    ui->tableWidget->clear(); // Clear previous data
    ui->tableWidget->setRowCount(transactions.size());
    ui->tableWidget->setColumnCount(11); // number of data members

    // Set headers
    QStringList headers = {
        "Account", "Type", "Nature", "Item Name", "Description",
        "Rate", "Amount", "Quantity", "Debit", "Credit", "Date"
    };
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(4, 300);

    // Fill table
    for (int row = 0; row < transactions.size(); ++row) {
        const Transaction &t = transactions[row];

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(t.account)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(t.type)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(t.nature)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(t.itemName)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(t.description)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(t.rate, 'f', 2)));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(t.amount, 'f', 2)));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(t.quantity)));
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(QString::number(t.debit, 'f', 2)));
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(QString::number(t.credit, 'f', 2)));
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(t.date.toQString()));
    }
}

ViewTransactionWindow::~ViewTransactionWindow()
{
    delete ui;
}

void ViewTransactionWindow::on_pushButton_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}

