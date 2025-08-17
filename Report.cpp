#include "Report.h"
#include<fstream>
#include <QDebug>
#include <QApplication>


Report::Report(const TransactionManager &tm, const Inventory &inv): transactionManager(tm), inventory(inv) {}


bool Report::exportReport(std::string &reportName) {
    QString path = QCoreApplication::applicationDirPath() + "/Exported Reports/";
    std::string finalPath = path.toStdString() + reportName;
    std::ofstream outFile(finalPath);
    if (!outFile.is_open()) {
        return false;
    }

    QString transactionFilePath = QCoreApplication:: applicationDirPath() + "/data/transaction.txt";
    transactionManager.loadFromFile(transactionFilePath.toStdString());
    float income = 0.0, expense = 0.0;
    for (const Transaction& t: transactionManager.getAllTransactions()) {
        if (t.nature == "Sales" || t.nature == "Purchase Return") {
            income += t.amount;
        }

        else {
            expense += t.amount;
        }
    }

    qDebug()<<expense;
    outFile << "Accounting Report" << std::endl;
    outFile << "=========================\n";
    outFile << "Profit and Loss \n" ;
    outFile << "Income Rs." << income << "\n" ;
    outFile << "Expense Rs." << expense << "\n" ;
    std::string resultType = (income - expense) < 0 ? "Loss" : "Profit";
    outFile << "Net " << resultType <<" Rs."<<std::abs(income - expense) << std::endl;
    outFile<< "=========================\n";
    outFile<<"Thank you from Himanshu, Ishan and Janak"<<std::endl;
    outFile<<"Radhe Radhe 🙏";

    return true;
}
