#include "ViewInventoryWindow.h"
#include "ui_ViewInventoryWindow.h"


//Here, the item name should not contain space and the price should not be in float, some error


ViewInventoryWindow::ViewInventoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ViewInventoryWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    inventory.loadInventoryFromFile();
    std::vector<Item> items;
    inventory.copyInventoryItems(items);

    ui->tableWidget->setRowCount(items.size());

    for(int row=0; row<items.size(); row++){

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(items[row].itemName)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(items[row].price, 'f', 2)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(items[row].quantity)));
    }
}

ViewInventoryWindow::~ViewInventoryWindow()
{
    delete ui;
}


void ViewInventoryWindow::on_back_btn_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();//Here parentWidget returns a pointer to the parent
    }

    this -> close();
}

