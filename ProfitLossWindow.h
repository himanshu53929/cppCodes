#ifndef PROFITLOSSWINDOW_H
#define PROFITLOSSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ProfitLossWindow;
}

class ProfitLossWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfitLossWindow(QWidget *parent = nullptr);
    ~ProfitLossWindow();

private slots:
    void on_back_button_clicked();

private:
    Ui::ProfitLossWindow *ui;
};

#endif // PROFITLOSSWINDOW_H
