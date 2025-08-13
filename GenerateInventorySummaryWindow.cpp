#include "GenerateInventorySummaryWindow.h"
#include "ui_GenerateInventorySummaryWindow.h"
#include "Inventory.h"
#include "TransactionManager.h"
#include <QMessageBox>
#include "Report.h"
#include <QString>

GenerateInventorySummaryWindow::GenerateInventorySummaryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GenerateInventorySummaryWindow)
{
    ui->setupUi(this);

    showMaximized();

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

    double totalValue = 0.0;
    int totalItems = 0;

    for (const auto& item : inventory.getItems()) {
        totalItems += item.quantity;
        totalValue += item.quantity * item.price;
    }


    ui->table->setRowCount(1);

    ui->table->setItem(0, 0, new QTableWidgetItem(QString::number(inventory.getItems().size())));
    ui->table->setItem(0, 1, new QTableWidgetItem(QString::number(totalValue, 'f', 2)));
    ui->table->setItem(0, 2, new QTableWidgetItem(QString::number(totalItems)));
}

GenerateInventorySummaryWindow::~GenerateInventorySummaryWindow()
{
    delete ui;
}

void GenerateInventorySummaryWindow::on_back_button_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}

