#ifndef REPORT_H
#define REPORT_H

#include "TransactionManager.h"
#include "Inventory.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

class Report {
private:
    const TransactionManager transactionManager;
    const Inventory inventory;

public:
    //Initialization code for report
    void init();
    // Constructor for binding data sources
    Report(const TransactionManager& tm, const Inventory& inv);

    // Generates profit or loss summary from sales and purchases
    void generateProfitLoss();

    // Generates a basic balance sheet from inventory + transaction data
    void generateBalanceSheet();

    // Displays key inventory statistics like total value, item count, etc.
    void generateInventorySummary();

    // Exports report to a file
    bool exportReport(const std::string& reportName);
};

#endif // REPORT_H
