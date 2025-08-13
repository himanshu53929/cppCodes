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

    showMaximized();
}

AddItemsToInventoryWindow::~AddItemsToInventoryWindow()
{
    delete ui;
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
    QString itemName = ui->item_name->text();
    double itemPrice = ui->item_price->text().toDouble();
    int itemQuantity = ui->item_quantity->text().toInt();

    Item I;
    I.itemName = itemName.toStdString();
    I.price = itemPrice;
    I.quantity = itemQuantity;

    QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";
    Inventory loadedInventory;
    loadedInventory.loadInventoryFromFile(inventoryFilePath.toStdString());

    for(const auto& item: loadedInventory.getItems()){
        if(I.itemName == item.itemName){
            QMessageBox:: StandardButton reply;
            reply = QMessageBox:: question(this, "Item already exists", "Do you want to update item quantity and price?");
            if(reply == QMessageBox:: Yes){
                loadedInventory.updateQuantity(I.itemName, I.quantity, inventoryFilePath.toStdString());
                loadedInventory.updatePrice(I.itemName, I.price,inventoryFilePath.toStdString());
            }
            return;
        }
    }

    if(inventory.addItem(I)){
        QMessageBox::StandardButton answer;
        answer = QMessageBox::question(this, "From Hacker", "Do you really want to add the item to the inventory?");

        if(answer == QMessageBox::Yes){
            inventory.saveInventoryToFile(inventoryFilePath.toStdString());
        }


        QMessageBox::information(this, "Congratulations", "Item was added Successfully");
    }

    else{
        QMessageBox::critical(this, "Error", "Somthing went wrong!");
    }


}

