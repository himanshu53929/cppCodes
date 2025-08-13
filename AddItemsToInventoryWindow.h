#ifndef ADDITEMSTOINVENTORYWINDOW_H
#define ADDITEMSTOINVENTORYWINDOW_H

#include <QMainWindow>
#include "Inventory.h"
namespace Ui {
class AddItemsToInventoryWindow;
}

class AddItemsToInventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddItemsToInventoryWindow(QWidget *parent = nullptr);
    ~AddItemsToInventoryWindow();

private slots:

    void on_back_btn_clicked();

    void on_save_inventory_button_clicked();

private:
    Ui::AddItemsToInventoryWindow *ui;
    Inventory inventory;

};

#endif // ADDITEMSTOINVENTORYWINDOW_H
