#ifndef VIEWTRANSACTIONWINDOW_H
#define VIEWTRANSACTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ViewTransactionWindow;
}

class ViewTransactionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewTransactionWindow(QWidget *parent = nullptr);
    ~ViewTransactionWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewTransactionWindow *ui;
};

#endif // VIEWTRANSACTIONWINDOW_H
