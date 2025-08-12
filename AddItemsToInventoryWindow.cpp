#include "AddItemsToInventoryWindow.h"
#include "ui_AddItemsToInventoryWindow.h"
#include<QString>
#include "Inventory.h"
#include<QMessageBox>

AddItemsToInventoryWindow::AddItemsToInventoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddItemsToInventoryWindow)
{
    ui->setupUi(this);
}

AddItemsToInventoryWindow::~AddItemsToInventoryWindow()
{
    delete ui;
}


void AddItemsToInventoryWindow::on_add_item_clicked()
{
    QString itemName = ui->item_name->text();
    int itemPrice = ui->item_price->text().toInt();
    int itemQuantity = ui->item_quantity->text().toInt();

    Item I;
    I.itemName = itemName.toStdString();
    I.price = itemPrice;
    I.quantity = itemQuantity;

    if(inventory.addItem(I)){
        QMessageBox::information(this, "Congratulations", "Item was added Successfully");
    }

    else{
        QMessageBox::critical(this, "Error", "Somthing went wrong!");
    }

}


void AddItemsToInventoryWindow::on_back_btn_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}


void AddItemsToInventoryWindow::on_save_inventory_button_clicked()
{
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "From Hacker", "Do you really want to update the inventory?");

    if(answer == QMessageBox::Yes){
        QString filePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";

        inventory.saveInventoryToFile(filePath.toStdString());
    }

}

