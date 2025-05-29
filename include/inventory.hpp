#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "karakter.hpp"
#include <string>
#include <vector>

void addItemToInventory(std::vector<std::string>& inventory, const std::string& itemName);
void displayInventory(const std::vector<std::string>& inventory);
bool useItem(std::vector<std::string>& inventory, const std::string& itemName, Character& target);
bool isEmpty(const std::vector<std::string>& inventory);

#endif
