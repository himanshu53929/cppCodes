#include "mainwindow.h"
#include "UserLoginWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserLoginWindow userLoginWindow;


    userLoginWindow.show();
    return a.exec();

}
