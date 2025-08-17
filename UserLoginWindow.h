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

    void on_actionrefresh_triggered();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::UserLoginWindow *ui;

    void setRandomMessage();
};

#endif // USERLOGINWINDOW_H
