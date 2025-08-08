#ifndef VIEWINVENTORYWINDOW_H
#define VIEWINVENTORYWINDOW_H
#include "Inventory.h"

#include <QMainWindow>

namespace Ui {
class ViewInventoryWindow;
}

class ViewInventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewInventoryWindow(QWidget *parent = nullptr);
    ~ViewInventoryWindow();

private slots:
    void on_back_btn_clicked();

private:
    Ui::ViewInventoryWindow *ui;
    Inventory inventory;
};

#endif // VIEWINVENTORYWINDOW_H
