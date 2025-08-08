#ifndef LEDGER_H
#define LEDGER_H

#include <vector>
#include <string>
#include "Date.h"
#include "Transaction.h"
#include "TransactionManager.h"

class LedgerEntry {
public:
    int account;
    std::string nature;
    std::string itemName;
    int quantity;
    double rate;
    double amount;
    std::string description;
    std::string type; // debit or credit
    Date date;


    LedgerEntry() = default;
    LedgerEntry(int acc, const std::string& nat, const std::string& item,
                int qty, double r, const std::string& desc,
                const std::string& t, const Date& d);

    void displayStyled() const;
};

class Ledger {
private:
    std::vector<LedgerEntry> entries;

public:
    void loadFromTransactions(const std::vector<Transaction>& txList);
    void addEntry(const LedgerEntry& entry);
    void displayStyledLedger(int account) const;
};

#endif
