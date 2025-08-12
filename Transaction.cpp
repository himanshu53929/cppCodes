#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QCoreApplication>
#include <QString>

Transaction::Transaction()
    : account(0), type(""), nature(""), itemName(""), description(""),
    rate(0.0), amount(0.0), quantity(0),
    debit(0.0), credit(0.0), date() {}


Transaction::Transaction(int acc,
                         const std::string& nat,
                         const std::string& item,
                         const std::string& desc,
                         double rate,
                         double amount,
                         int qty,

                         const Date& date1)
    :account(acc),
    nature(nat),
    itemName(item),
    description(desc),
    rate(rate),
    amount(amount),
    quantity(qty),

    date(date1)

{
    this->amount = quantity * rate;
    if (nature == "Sales" || nature == "Purchase Return") {
        type = "debit";
        debit = amount;
        credit = 0.0;
    } else {
        type = "credit";
        credit = amount;
        debit = 0.0;
    }

}

// Input function now depends on Inventory
void Transaction::input(Inventory& inventory) {
    std::cout << "Enter account number: ";
    std::cin >> account;

    std::cout << "Enter nature of transaction (sales, purchase, sales return, purchase return): ";
    std::cin >> nature;

    if (nature != "sales" && nature != "purchase" &&
        nature != "sales return" && nature != "purchase return") {
        std::cerr << "Invalid transaction nature.\n";
        return;
    }

    std::cout << "Enter item name: ";
    std::cin >> itemName;

    rate = inventory.getPriceByName(itemName);
    if (rate == -1) {
        std::cerr << "Item not found in inventory.\n";
        return;
    }

    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    std::cin.ignore(); // clear input buffer
    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    amount = quantity * rate;

    if(nature == "sales" || nature == "purchase return") {
        type = "debit";
        debit = amount;
        credit = 0.0;
        QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";

        inventory.updateQuantity(itemName, -quantity, inventoryFilePath.toStdString()); // reduce stock
    } else {
        type = "credit";
        credit = amount;
        debit = 0.0;
        QString inventoryFilePath = QCoreApplication::applicationDirPath() + "/data/inventory.txt";

        inventory.updateQuantity(itemName, quantity, inventoryFilePath.toStdString()); // increase stock
    }

    std::cout << "Enter date of transaction:\n";
    date.setDate();
}

// Displays transaction details
void Transaction::display() const {
    std::cout << "\n--- Transaction Details ---\n";
    std::cout << "Account No: " << account << "\n";
    std::cout << "Nature: " << nature << " (" << type << ")\n";
    std::cout << "Item: " << itemName << "\n";
    std::cout << "Quantity: " << quantity << "\n";
    std::cout << "Rate: " << rate << "\n";
    std::cout << "Amount: " << amount << "\n";
    std::cout << "Description: " << description << "\n";

    std::cout << "Date: " << date << "\n";
}

// Saves transaction to file
void Transaction::saveToFile(const std::string& filename) const {
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    outfile << account << ","
            << nature << ","
            << itemName << ","
            << quantity << ","
            << rate << ","
            << amount << ","
            << description << ","

            << date.getDay() << "/" << date.getMonth() << "/" << date.getYear()
            << "\n";

    outfile.close();
}
