#ifndef REPORT_H
#define REPORT_H

#include "TransactionManager.h"
#include "Inventory.h"
#include <string>

class Report {
private:
    TransactionManager transactionManager;
    const Inventory inventory;

public:
    // Constructor for binding data sources
    Report(const TransactionManager& tm, const Inventory& inv);

    // Generates profit or loss summary from sales and purchases
    void generateProfitLoss();


    // Displays key inventory statistics like total value, item count, etc.
    void generateInventorySummary();

    // Exports report to a file
    bool exportReport(std::string& reportName);
};

#endif // REPORT_H
