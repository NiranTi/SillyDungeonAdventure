#include "inventory.hpp"
#include "karakter.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip> 

using namespace std;

const int MAX_INVENTORY = 10;

void addItemToInventory(vector<string>& inventory, const string& itemName) {
    if (inventory.size() >= MAX_INVENTORY) {
        cout << "Inventory is full! Couldn't add " << itemName << ".\n";
        return;
    }
    inventory.push_back(itemName);
}

bool isEmpty(const vector<string>& inventory) {
    return inventory.empty();
}

void displayInventory(const std::vector<std::string>& inventory) {
    if (isEmpty(inventory)) {
        cout << "Your inventory is empty.\n";
        return;
    }

    cout << "Inventory:\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << "[" << setw(2) << i << "] " << setw(15) << left << inventory[i] << "\n";
    }
}

bool useItem(vector<string>& inventory, const string& itemName, Character& target) {
    auto it = find(inventory.begin(), inventory.end(), itemName);
    if (it != inventory.end()) {
        if (itemName == "Heal Potion") {
            int healAmount = 50;
            target.hp = min(target.maxHP, target.hp + healAmount);
            cout << target.name << " healed by " << healAmount << " HP!\n";
        }
        else if (itemName == "Devil Fruit") {
            target.atk += 10;
            cout << target.name << " ate a Devil Fruit! ATK increased!\n";
        }
        else if (itemName == "Elixir") {
            target.hp = target.maxHP;
            cout << target.name << " used Elixir! HP fully restored!\n";
        }
        inventory.erase(it);
        return true;
    } else {
        cout << "Item not found in inventory.\n";
        return false;
    }
    return false;  // fallback kalau item tidak cocok
}
