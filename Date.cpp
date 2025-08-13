//
// Created by ishan on 7/9/25.
//
#include "Date.h"
#include<QString>

Date::Date() : year(2000), month(1), day(1) {}//Sets default date
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}//Sets date passed by user
//Type conversion code using constructor for the qdate
Date::Date(QDate qdate): day(qdate.day()), month(qdate.month()), year(qdate.year()){}


void Date::setYear(int y) {
    year = y;
}
void Date::setMonth(int m) {
    month = m;
}
void Date::setDay(int d) {
    day = d;
}

//Accesses the entered date by the user
int Date::getYear() const {
    return year;
}
int Date::getMonth() const {
    return month;
}
int Date::getDay() const {
    return day;
}



QString Date::toQString() const{
    return QString("%1/%2/%3")
                .arg(day, 2, 10, QChar('0'))
                .arg(month, 2, 10, QChar('0'))
                .arg(year);
}
