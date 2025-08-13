#include "User.h"
#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <QDebug>
#include <QCoreApplication>

std::vector<User> User::users;
std::string User::currentUser;
// User::User()
// {

// }

User::User(const std::string& uname,const std::string& pass,const std::string& r): username(uname), password(pass), role(r) {}

void User::loadUsersFromFile(const std::string& fileName){
    std::ifstream infile(fileName);

    if(!infile){
        qDebug()<<"File was not opened";
        std::ofstream outfile(fileName);
        qDebug()<<"File created";

    }

    else{
        std::string line;

        while(std::getline(infile, line)){
            std::stringstream ss(line);

            std::string userName, userPassword, Role;

            std::getline(ss, userName, ',');
            std::getline(ss, userPassword, ',');
            std::getline(ss, Role, ',');

            User::users.push_back(User(userName, userPassword, Role));

        }
    }
}//JANAK

bool User::loginUser(const std::string& uname, const std::string& pass){
    for(const auto &user:users){
        if (user.username == uname){
            if(user.password == pass){
                User::currentUser = uname;
                return true;
            }
        }

    }
    return false;
}

bool User::registerUser(const std::string &uname,const std::string &pass,const std::string &r){
    for(const auto &user:users){
        if (user.username == uname){
            qDebug()<<"User already registered!\n";
            return false;
        }
    }

    QString userFilePath = QCoreApplication::applicationDirPath() + "/data/user.txt";
    std::ofstream outfile(userFilePath.toStdString(), std::ios::app);
    if(!outfile){
        qDebug()<<"File not opened\n";
        return false;
    }

    outfile<<uname<<","<<pass<<","<<r<<","<<std::endl;

    return true;
}

bool User::isAdmin(const std::string& uname){
    for(const auto &user:users){
        if (user.username == uname){
            return(user.role == "admin");
        }
    }
    return false;
}


