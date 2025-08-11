#ifndef GENERATEBALANCESHEET_H
#define GENERATEBALANCESHEET_H

#include <QMainWindow>

namespace Ui {
class GenerateBalanceSheet;
}

class GenerateBalanceSheet : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateBalanceSheet(QWidget *parent = nullptr);
    ~GenerateBalanceSheet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GenerateBalanceSheet *ui;
};

#endif // GENERATEBALANCESHEET_H
