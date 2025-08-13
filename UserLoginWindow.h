#ifndef USERLOGINWINDOW_H
#define USERLOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserLoginWindow;
}

class UserLoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserLoginWindow(QWidget *parent = nullptr);
    ~UserLoginWindow();

private slots:
    void on_submit_button_clicked();

private:
    Ui::UserLoginWindow *ui;
};

#endif // USERLOGINWINDOW_H
