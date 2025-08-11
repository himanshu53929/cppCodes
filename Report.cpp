#include "Report.h"
#include <QDebug>


void Report::init()
{
    TransactionManager tm;
    bool state;
    state = tm.loadFromFile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/transaction.txt");

    if(state == false){
        qDebug() << "Error!!! Transaction file loading failed";
        exit(1);
    }

    Inventory inv;
    state = inv.loadInventoryFromFile();

    if(state == false){
        qDebug() << "Error!!! Inventory file loading failed";
    }

}

Report::Report(const TransactionManager &tm, const Inventory &inv): transactionManager(tm), inventory(inv) {}

void Report::generateProfitLoss() {
    float income = 0.0;
    float expense = 0.0;
    for (const Transaction& t: transactionManager.getAllTransactions()) {
        if (t.nature == "sales" || t.nature == "purchase return") {
            income += t.amount;
        }

        if (t.nature == "sales return" || t.nature == "purchase") {
            expense += t.amount;
        }
        float net = income - expense;
    }
    //Output ya hunxa
}
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

void Report::generateInventorySummary() {
    double totalValue = 0.0;
    int totalItems = 0;

    for (const auto& item : inventory.getItems()) {
        totalItems += item.quantity;
        totalValue += item.quantity * item.price;
    }

    std::cout << "\n📦 Inventory Summary 📦\n";
    std::cout << "----------------------------------\n";
    std::cout << "Total Unique Items: " << inventory.getItems().size() << "\n";
    std::cout << "Total Quantity:     " << totalItems << "\n";
    std::cout << "Total Value:        Rs. " << totalValue << "\n\n";
}
