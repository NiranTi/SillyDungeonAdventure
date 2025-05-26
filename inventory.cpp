#include "inventory.hpp"
#include <iostream>

using namespace std;

const int MAX_ITEMS = 10;

void addItem(vector<Item>& inventory, const string& name) {
    if (inventory.size() >= MAX_ITEMS) {
        cout << "Inventory is full. Cannot add " << name << ".\n";
        return;
    }

    Item item{name, "A mysterious item called " + name + "."};
    inventory.push_back(item);
    cout << name << " added to inventory.\n";
}

void useItem(vector<Item>& inventory, int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        cout << "Invalid item index.\n";
        return;
    }

    cout << "You used " << inventory[index].name << ".\n";
    inventory.erase(inventory.begin() + index);
}

void throwItem(vector<Item>& inventory, int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        cout << "Invalid item index.\n";
        return;
    }

    cout << "You threw away " << inventory[index].name << ".\n";
    inventory.erase(inventory.begin() + index);
}

void displayInventory(const vector<Item>& inventory) {
    cout << "Inventory (" << inventory.size() << "/" << MAX_ITEMS << "):\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i << ": " << inventory[i].name << "\n";
    }
}

void viewItemDetail(const vector<Item>& inventory, int index) {
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        cout << "Invalid item index.\n";
        return;
    }

    const Item& item = inventory[index];
    cout << "Item Detail [" << index << "]\n";
    cout << "Name: " << item.name << "\n";
    cout << "Description: " << item.description << "\n";
}
