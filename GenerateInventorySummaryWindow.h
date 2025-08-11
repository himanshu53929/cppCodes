#ifndef GENERATEINVENTORYSUMMARYWINDOW_H
#define GENERATEINVENTORYSUMMARYWINDOW_H

#include <QMainWindow>

namespace Ui {
class GenerateInventorySummaryWindow;
}

class GenerateInventorySummaryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateInventorySummaryWindow(QWidget *parent = nullptr);
    ~GenerateInventorySummaryWindow();

private slots:
    void on_back_button_clicked();

private:
    Ui::GenerateInventorySummaryWindow *ui;
};

#endif // GENERATEINVENTORYSUMMARYWINDOW_H
