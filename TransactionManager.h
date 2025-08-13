//
// Created by ishan on 7/9/25.
//

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H
#include "Transaction.h"
#include <vector>

class TransactionManager {
private:
    std::vector<Transaction> transactions;
public:
    void addTransaction(const Transaction& transaction);
    bool loadFromFile(const std::string& filename);
    std::vector<Transaction> getAllTransactions() const;
    double calculateBalance(const std::string& account) const;
};
#endif //TRANSACTIONMANAGER_H
