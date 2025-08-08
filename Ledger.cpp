#include "Ledger.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

LedgerEntry::LedgerEntry(int acc, const std::string& nat, const std::string& item,
                         int qty, double r, const std::string& desc,
                         const std::string& t, const Date& d)
    : account(acc), nature(nat), itemName(item), quantity(qty), rate(r),
    amount(qty * r), description(desc), type(t), date(d) {}

void LedgerEntry::displayStyled() const {
    std::string direction = (type == "debit") ? "To " : "By ";
    std::string particulars = direction + itemName + " A/c";
    std::cout << std::left << std::setw(30) << particulars
              << std::setw(6) << "" // Journal Folio placeholder
              << std::setw(12) << "Rs. " + std::to_string(amount)
              << std::setw(12) << (std::to_string(date.getYear()) + "/" +
                                   std::to_string(date.getMonth()) + "/" +
                                   std::to_string(date.getDay()))
              << "\n";
}
void Ledger::displayStyledLedger(int account) const {
    std::cout << "\n═══════════════════════════════════════════════════════════════════\n";
    std::cout << "                     Ledger for Account No: " << account << "\n";
    std::cout << "═══════════════════════════════════════════════════════════════════\n";
    std::cout << std::left << std::setw(30) << "Particulars"
              << std::setw(6) << "J.F."
              << std::setw(12) << "Amount"
              << std::setw(12) << "Date" << "\n";
    std::cout << "───────────────────────────────────────────────────────────────────\n";

    for (const auto& e : entries) {
        if (e.account == account) {
            e.displayStyled();
        }
    }

    std::cout << "───────────────────────────────────────────────────────────────────\n";
}
void Ledger::addEntry(const LedgerEntry& entry) {}
void Ledger::loadFromTransactions(const std::vector<Transaction>& txList){
    entries.clear(); // Optional: Reset ledger before loading

    for (const auto& tx : txList) {
        LedgerEntry entry(tx.account, tx.nature, tx.itemName, tx.quantity, tx.rate,
                          tx.description, tx.type, tx.date);
        entries.push_back(entry);
    }
}
