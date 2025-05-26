#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>

struct Item {
    std::string name;
    std::string description;
};

void addItem(std::vector<Item>& inventory, const std::string& name);
void useItem(std::vector<Item>& inventory, int index);
void throwItem(std::vector<Item>& inventory, int index);
void displayInventory(const std::vector<Item>& inventory);
void viewItemDetail(const std::vector<Item>& inventory, int index);

#endif
