//
// Created by ishan on 7/9/25.
//

#ifndef DATE_H
#define DATE_H
#include<iostream>
#include<QDate>
#include<QString>

class Date {
private:
    int year, month, day;

public:
    Date();
    Date(int y, int m, int d);
    Date(QDate qdate);

    void setDate(); // user input
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    QString toQString() const;


    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif // DATE_H
