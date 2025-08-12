#include "Report.h"
#include <QDebug>


Report::Report(const TransactionManager &tm, const Inventory &inv): transactionManager(tm), inventory(inv) {}

void Report::generateBalanceSheet() {
    float asset = 0.0;
    float liability = 0.0;
    //credit is marked as liability
    for (const Transaction& t: transactionManager.getAllTransactions()) {
        if (t.type == "credit") {
            liability += t.amount;
        }
    }
    for (const auto& item : inventory.getItems() ) {
        asset = item.price * item.quantity;
    }
    //balance sheet to output ya hunxa
}

bool Report::exportReport(const std::string &reportName) {
    std::ofstream outFile(reportName);
    if (!outFile.is_open()) {
        return false;
    }
    float income = 0.0, expense = 0.0, asset = 0.0, liability = 0.0;
    for (const Transaction& t: transactionManager.getAllTransactions()) {
        if (t.nature == "sales" || t.nature == "purchase return") {
            income += t.amount;
        }

        if (t.nature == "sales return" || t.nature == "purchase") {
            expense += t.amount;
        }
    }
    outFile << "Accouting report" << std::endl;
    outFile << "=========================\n";
    outFile << "Proit and Loss \n" ;
    outFile << "Income rs." << income << "\n" ;
    outFile << "Expense rs." << expense << "\n" ;
    std::string resultType = (income - expense) < 0 ? "Loss" : "Profit";
    outFile << "Net: " << resultType << std::abs(income - expense) << std::endl;
    outFile << "Balance Sheet:\n";
    for (const Transaction& t: transactionManager.getAllTransactions()) {
        if (t.type == "credit") {
            liability += t.amount;
        }
    }
    for (const auto& item : inventory.getItems() ) {
        asset = item.price * item.quantity;
    }
    outFile << "Asset: " << asset << std::endl;
    outFile << "Liability: " << liability << std::endl;
    outFile << "Net Worth: Rs. " << (asset - liability) << "\n\n";
    outFile.close();
    return true;
}
