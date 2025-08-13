#ifndef INVENTORY_H
#define INVENTORY_H
#include<vector>
#include<iostream>
#include<fstream>
#include <string>

struct Item{
    std::string itemName;
    int quantity;
    double price;
};

class Inventory {
private:
    std::vector<Item> items;

public:
    Inventory();
    //void input();
    bool addItem(Item& I);
    void updatePrice(const std:: string nam, const int& p, const std::string& filename);
    void updateQuantity(const std::string nam, const int& q, const std::string& filename);
    void viewInventory() const;
    double getPriceByName(const std::string& itemName) const;
    void checkReorderAlerts();
    void saveInventoryToFile(const std::string& filename) const;
    bool loadInventoryFromFile(const std::string& filename);
    void copyInventoryItems(std::vector<Item>& itms) const;
    const std::vector<Item>& getItems() const;
};

#endif
