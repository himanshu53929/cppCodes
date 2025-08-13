#include "UserLoginWindow.h"
#include "User.h"
#include "ui_UserLoginWindow.h"
#include <QString>
#include "mainwindow.h"
#include <QStringList>
#include <QRandomGenerator>


UserLoginWindow::UserLoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserLoginWindow)
{
    ui->setupUi(this);

    // showMaximized();

    setRandomMessage();


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

    userFilePath = QCoreApplication::applicationDirPath() + "/data/user.txt";
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

void UserLoginWindow::setRandomMessage()
{
    QStringList messages = {
        "Welcome back! Let’s make today’s numbers shine ✨",
        "Hello there! Ready to turn data into success? 📊",
        "A fresh day, fresh books — let’s get counting! 🧮",
        "Good to see you! Your accounts are in good hands 💼",
        "Let’s balance more than books — let’s balance success 🌟",
        "Numbers tell stories… let’s write a great one today 📖",
        "Your ledger is smiling already 😄",
        "Hello, finance wizard! Let’s work some magic ✨💰",
        "Every transaction counts — and so do you 🙌",
        "Time to turn accounting into achievement 🏆"
    };

    int random_index = QRandomGenerator:: global()->bounded(messages.size());

    ui->random_message->setText(messages[random_index]);
}


void UserLoginWindow::on_actionrefresh_triggered()
{
    setRandomMessage();
}

