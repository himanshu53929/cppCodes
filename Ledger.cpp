#include "Ledger.h"

LedgerEntry::LedgerEntry(int acc, const std::string& nat, const std::string& item,
                         int qty, double r, const std::string& desc,
                         const std::string& t, const Date& d)
    : account(acc), nature(nat), itemName(item), quantity(qty), rate(r),
    amount(qty * r), description(desc), type(t), date(d) {}


void Ledger::addEntry(const LedgerEntry& entry) {}
std::vector<LedgerEntry> Ledger::returnLedger()
{
    return entries;
}

void Ledger::loadFromTransactions(const std::vector<Transaction>& txList){
    entries.clear(); // Optional: Reset ledger before loading

    for (const auto& tx : txList) {
        LedgerEntry entry(tx.account, tx.nature, tx.itemName, tx.quantity, tx.rate,
                          tx.description, tx.type, tx.date);
        entries.push_back(entry);
    }
}
