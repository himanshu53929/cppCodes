#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"
#include "Inventory.h"

class Transaction {


public:

    int account;
    std::string type;
    std::string nature;
    std::string itemName;
    std::string description;
    double rate;
    double amount;
    int quantity;
    double debit;
    double credit;
    Date date;
    Transaction();
    //Transaction(int acc, const std::string& nat, const std::string& desc, int qty, double r, const Date& d);

    //Transaction(int acc, const std::string& nat, const std::string& desc, int qty, double r, const Date& d);
    Transaction(int acc,
                const std::string& nat,
                const std::string& item,
                const std::string& desc,
                double rate,
                double amount,
                int    qty,

                const Date& d);


    void input(Inventory& inventory); // Accept inventory reference
    void display() const;
    void saveToFile(const std::string& filename) const;
    void setDebitCredit(std::string type, int quantity);
};

#endif
