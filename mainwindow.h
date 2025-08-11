#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"InventoryWindow.h"
#include "ViewInventoryWindow.h"
#include "AddItemsToInventoryWindow.h"
#include "ViewTransactionWindow.h"
#include "ViewLedgerForAccount.h"
#include "ProfitLossWindow.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include "Report.h"
#include <QMessageBox>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_add_transaction_clicked();

    void on_view_inventory_clicked();

    void on_add_items_to_inventory_clicked();

    void on_exit_clicked();

    void on_view_tansaction_clicked();

    void on_view_ledger_for_account_clicked();

    void on_profit_loss_button_clicked();

    void on_export_report_button_clicked();

    void on_submit_button_clicked();

private:
    Ui::MainWindow *ui;

    InventoryWindow *invetWin;

    ViewInventoryWindow *viewInventWin;

    AddItemsToInventoryWindow *AddItemsToInventWin;

    ViewTransactionWindow *viewTransactionWin;

    ViewLedgerForAccount *viewLedgerForAcc;

    ProfitLossWindow *profitLossWin;

    QDialog* dialog;

    QFont font;

    QLineEdit* line;

    Report* ptr_report;
};
#endif // MAINWINDOW_H
