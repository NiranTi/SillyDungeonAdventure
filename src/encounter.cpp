#include "ui.hpp"
#include "battle.hpp"
#include "karakter.hpp"
#include "inventory.hpp"
#include <iostream>
#include <random>
#include <vector>
using namespace std;

void encounterPercentage(int round, Character team[], vector<string>& inventory) {
    enemies rookie = {"Rookie Enemy", 100, 100, 20, 5, 2, 4};
    enemies mid    = {"Mid Enemy", 200, 200, 40, 80, 3, 4};
    enemies boss   = {"Boss Enemy", 500, 500, 50, 100, 5, 4};

    BattleResult result = PLAYER_ESCAPED;

    if (round == 10) {
        cout << colorText("BOSS FIGHT!\n\n", "red");
        result = startBattle(team, TEAM_SIZE, boss,inventory);
    }
    else {
        int check = round % 10;

        if (check == 1 || check == 4 || check == 7) {
            cout << colorText("ROOKIE ENEMY ENCOUNTERED!\n\n", "green");
            result = startBattle(team, TEAM_SIZE, rookie, inventory);
        }
        else if (check == 2 || check == 6) {
            cout << colorText("MID ENEMY ENCOUNTERED!\n\n", "yellow");
            result = startBattle(team, TEAM_SIZE, mid, inventory);
        }
        else if (check == 3 || check == 9) {
            int chestDrop = round % 3;
            typeText("You've found a chest!\n\n");

            if (chestDrop == 0) {
                addItemToInventory(inventory, "Heal Potion");
                cout << "Congrats! You've received Heal Potion!" << endl;
            }
            else if (chestDrop == 1) {
                addItemToInventory(inventory, "Devil Fruit");
                cout << colorText("Congrats! You've received Devil Fruit!","magenta") << endl;
            }
            else{
                addItemToInventory(inventory, "Elixir");
                cout << "Congrats! You've received Elixir!" << endl;
            }
        }
        else{
            cout << "There's nothing here..." << endl;
        }
    }
    if (result == PLAYER_WIN) {
        clearScreen();
        typeText("\nYOU WIN!\n", 30);
        exit(0);
    }
    else if (result == PLAYER_LOSE) {
        clearScreen();
        typeText("\nGAME OVER\n", 30);
        exit(0);
    }
}