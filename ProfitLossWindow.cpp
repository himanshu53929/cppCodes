#include "ProfitLossWindow.h"
#include "ui_ProfitLossWindow.h"
#include "TransactionManager.h"
#include "Inventory.h"
#include <QMessageBox>
#include "Report.h"
#include <QString>

ProfitLossWindow::ProfitLossWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProfitLossWindow)
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

    Report report(transactionManager, inventory);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table->setRowCount(0);

    float income = 0.0;
    float expense = 0.0;
    int i = 0;
    ui->table->setRowCount(0);
    std::string particular;

    for(const auto& transaction: transactionManager.getAllTransactions()){
        ui->table->setRowCount(i+1);

        if (transaction.nature == "Sales" || transaction.nature == "Purchase Return") {
            income += transaction.amount;
            particular = "To " + transaction.nature + " Balance";
            ui->table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(particular)));
            ui->table->setItem(i, 1, new QTableWidgetItem(QString::number(income, 'f', 2)));
            ui->table->setItem(i, 2, new QTableWidgetItem(QString("")));
            ui->table->setItem(i, 3, new QTableWidgetItem(QString("")));

        }

        else {
            expense += transaction.amount;
            particular = "By " + transaction.nature + " Balance";
            ui->table->setItem(i, 0, new QTableWidgetItem(QString("")));
            ui->table->setItem(i, 1, new QTableWidgetItem(QString("")));
            ui->table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(particular)));
            ui->table->setItem(i, 3, new QTableWidgetItem(QString::number(expense, 'f', 2)));
        }

        i++;
    }

    if(income > expense){
        ui->table->setRowCount(i+3);

        particular = "By Net Profit";
        ui->table->setItem(i+1, 0, new QTableWidgetItem(QString("")));
        ui->table->setItem(i+1, 1, new QTableWidgetItem(QString("")));
        ui->table->setItem(i+1, 2, new QTableWidgetItem(QString::fromStdString(particular)));
        ui->table->setItem(i+1, 3, new QTableWidgetItem(QString::number(income - expense, 'f', 2)));


        ui->table->setItem(i+2, 0, new QTableWidgetItem(QString("Total")));
        ui->table->setItem(i+2, 1, new QTableWidgetItem(QString::number(income)));

        ui->table->setItem(i+2, 2, new QTableWidgetItem(QString("Total")));
        ui->table->setItem(i+2, 3, new QTableWidgetItem(QString::number(income)));
    }

    else{
        ui->table->setRowCount(i+2);

        particular = "To Net Loss";
        ui->table->setItem(i+1, 0, new QTableWidgetItem(QString::fromStdString(particular)));
        ui->table->setItem(i+1, 1, new QTableWidgetItem(QString::number(expense - income, 'f', 2)));
        ui->table->setItem(i+1, 2, new QTableWidgetItem(QString("")));
        ui->table->setItem(i+1, 3, new QTableWidgetItem(QString("")));

        ui->table->setItem(i+2, 0, new QTableWidgetItem(QString("Total")));
        ui->table->setItem(i+2, 1, new QTableWidgetItem(QString::number(expense)));

        ui->table->setItem(i+2, 2, new QTableWidgetItem(QString("Total")));
        ui->table->setItem(i+2, 3, new QTableWidgetItem(QString::number(expense)));
    }


}

ProfitLossWindow::~ProfitLossWindow()
{
    delete ui;
}

void ProfitLossWindow::on_back_button_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}

