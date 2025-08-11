#include<iostream>
#include "Inventory.h"
//#include<fstream>

Inventory::Inventory(){}//Nothing just a default constructor
//to get price of item
double Inventory::getPriceByName(const std::string& itemName) const {
    for (const Item& I : items) {
        if (I.itemName == itemName)
            return I.price;
    }
    return -1; // Item not found
}

//Adds Items in the inventory
bool Inventory::addItem(Item& I)
{
    size_t before = items.size();

    items.push_back(I);//Think like appending the structure I to the vector items

    if(items.size() == before+1){
        return true;
    }

    else{
        return false;
    }
}

//Updates price if needed
void Inventory::updatePrice(const std::string nam, const int &p)
{

    //This is called for each loop. Think like all the vector members are loaded to the variable in left
    for( Item &I: items){
        if(nam == I.itemName){
            I.price = p;
        }
    }

    return;
}

//Updates inventory based on the quantity
void Inventory::updateQuantity(const std::string nam, const int& q)
{
    for(Item &I: items){
        if(nam == I.itemName){
            I.quantity += q;
        }
    }

    //I will also add some code here to check if the quantity is 0 and then remove it
    std::ofstream outfile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/inventory.txt", std::ios::out);

    for(const Item& I: items){
        outfile<<I.itemName<<std::endl;
        outfile<<I.quantity<<std::endl;
        outfile<<I.price<<std::endl;
    }

    return;
}

//Displays Item in the inventory
void Inventory::viewInventory() const
{
    for(const Item& I: items){
        std::cout<<"Name of item: "<<I.itemName<<std::endl<<"Quantity of item: "<<I.quantity<<
            std::endl<<"Price of Item: "<<I.price<<std::endl;

        std::cout<<"\n";
    }

    return;
}

//Writes all items present in the vector to the file
void Inventory::saveInventoryToFile() const
{
    std::ofstream outfile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/inventory.txt", std::ios::app);

    for(const Item& I: items){
        outfile<<I.itemName<<std::endl;
        outfile<<I.quantity<<std::endl;
        outfile<<I.price<<std::endl;
    }

    return;
}

//In future I will also add a code here to clear all the inventory

//Reads all items from the inventory and assigns them to the vector
void Inventory::loadInventoryFromFile()
{
    std::ifstream infile("D:/Pulchowk Campus/Second Semester/OOP in C++/QT Tutorial/ProjectMew/inventory.txt");

    if(infile){
        Item I;
        while (infile >> I.itemName >> I.quantity >> I.price) {
            items.push_back(I);
        }
    }

    return;
}

//Checks if the item is less than or equal to 15 and displays an alert message if it does
void Inventory::checkReorderAlerts()
{
    for(const Item I: items){
        if(I.quantity <= 15){
            std::cout<<"The "<<I.itemName<<" is almost finished!!! You may reorder it."<<std::endl;
        }
    }

    return;
}

void Inventory:: copyInventoryItems(std::vector<Item>& itms) const{
    itms = items;
}

const std::vector<Item> &Inventory::getItems() const {
    return items;
}

