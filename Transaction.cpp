#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <QCoreApplication>
#include <QString>

Transaction::Transaction()
    : account(0), type(""), nature(""), itemName(""), description(""),
    rate(0.0), amount(0.0), quantity(0),
    debit(0.0), credit(0.0), date() {}


Transaction::Transaction(int acc,
                         const std::string& nat,
                         const std::string& item,
                         const std::string& desc,
                         double rate,
                         double amount,
                         int qty,

                         const Date& date1)
    :account(acc),
    nature(nat),
    itemName(item),
    description(desc),
    rate(rate),
    amount(amount),
    quantity(qty),

    date(date1)

{
    this->amount = quantity * rate;
    if (nature == "Sales" || nature == "Purchase Return") {
        type = "debit";
        debit = amount;
        credit = 0.0;
    } else {
        type = "credit";
        credit = amount;
        debit = 0.0;
    }

}


// Saves transaction to file
void Transaction::saveToFile(const std::string& filename) const {
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    outfile << account << ","
            << nature << ","
            << itemName << ","
            << quantity << ","
            << rate << ","
            << amount << ","
            << description << ","

            << date.getDay() << "/" << date.getMonth() << "/" << date.getYear()
            << "\n";

    outfile.close();
}
