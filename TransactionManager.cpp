#include "TransactionManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QMessageBox>

void TransactionManager::addTransaction(const Transaction &t) {
    transactions.push_back(t);
}

bool TransactionManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {

        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string accStr, natstr, itmstr, qun, ratstr, amoutstr, desc, debitStr, creditStr, dateStr, typeStr;

        std::getline(ss, accStr, ',');
        std::getline(ss, natstr, ',');
        std::getline(ss, itmstr, ',');
        std::getline(ss, qun, ',');
        std::getline(ss, ratstr, ',');
        std::getline(ss, amoutstr, ',');
        std::getline(ss, desc, ',');
        //std::getline(ss, debitStr, ',');
        // std::getline(ss, creditStr, ',');
        //std::getline(ss, typeStr, ',');
        std::getline(ss, dateStr, ',');

        int acc = std::stoi(accStr);
        int quant = std::stoi(qun);
        double rat = std::stod(ratstr);
        double am = std::stod(amoutstr);
        //double debit = std::stod(debitStr);
        // double credit = std::stod(creditStr);

        // Parse date
        int day, month, year;
        char slash1, slash2;
        std::stringstream ds(dateStr);
        ds >> day >> slash1 >> month >> slash2 >> year;

        Date date(year, month, day);

        // Create Transaction object with correct parameter order
        Transaction t(acc, natstr, itmstr, desc, rat, am, quant, date);
        transactions.push_back(t);
    }

    file.close();

    return true;
}

double TransactionManager::calculateBalance(const std::string &account) const {
    double balance = 0.0;
    for (const auto &t : transactions) {
        if (std::to_string(t.account) == account) {  // Compare account numbers
            balance += t.credit;
            balance -= t.debit;
        }
    }
    return balance;
}
std::vector<Transaction> TransactionManager::getAllTransactions() const {
    return transactions;
}
