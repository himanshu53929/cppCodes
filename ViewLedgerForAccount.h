#ifndef VIEWLEDGERFORACCOUNT_H
#define VIEWLEDGERFORACCOUNT_H

#include <QMainWindow>
#include "Ledger.h"

namespace Ui {
class ViewLedgerForAccount;
}

class ViewLedgerForAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewLedgerForAccount(QWidget *parent = nullptr);
    ~ViewLedgerForAccount();

private slots:

    void on_back_button_clicked();


    void on_display_button_clicked();

private:
    Ui::ViewLedgerForAccount *ui;

};

#endif // VIEWLEDGERFORACCOUNT_H
