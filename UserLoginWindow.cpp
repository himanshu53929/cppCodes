#include "UserLoginWindow.h"
#include "User.h"
#include "ui_UserLoginWindow.h"
#include <QString>
#include "mainwindow.h"

UserLoginWindow::UserLoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserLoginWindow)
{
    ui->setupUi(this);
}

UserLoginWindow::~UserLoginWindow()
{
    delete ui;
}

void UserLoginWindow::on_submit_button_clicked()
{
    QString name, password;

    name = ui->userName->text();
    password = ui->userPassword->text();

    User user;
    QString userFilePath;

    userFilePath = "D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug/data/user.txt";
    user.loadUsersFromFile(userFilePath.toStdString());

    bool state = user.loginUser(name.toStdString(), password.toStdString());

    if(state == true){
        // Open MainWindow
        MainWindow *mainWin = new MainWindow();
        mainWin->show();

        // Close login window
        this->close();
    }

    else{
        QMessageBox:: critical(this, "Error", "Invalid Username or Password");
    }
}

