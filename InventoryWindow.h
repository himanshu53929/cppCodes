#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H

#include <QMainWindow>
#include "Inventory.h"

namespace Ui {
class InventoryWindow;
}

class InventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InventoryWindow(QWidget *parent = nullptr);
    ~InventoryWindow();

private slots:
    void on_pushButton_clicked();

    void on_add_transaction_btn_clicked();

    void on_save_transaction_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::InventoryWindow *ui;
    Inventory *inventory;

};

#endif // INVENTORYWINDOW_H
