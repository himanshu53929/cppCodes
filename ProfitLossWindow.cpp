#include "ProfitLossWindow.h"
#include "ui_ProfitLossWindow.h"
#include "TransactionManager.h"
#include "Inventory.h"
#include <QMessageBox>
#include "Report.h"

ProfitLossWindow::ProfitLossWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProfitLossWindow)
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

    Report report(transactionManager, inventory);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

