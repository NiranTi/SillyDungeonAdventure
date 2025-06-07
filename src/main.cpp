#include "karakter.hpp"
#include "ui.hpp"
#include "FiturTelusuri.hpp"
#include "utils.hpp"
#include "inventory.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    while (true) {
        Character team[3];
        vector<string> inventory;

        chooseCharacters(team);

        string confirm;
        while (true) {
            typeText("\nStart the game? (Y/N)", 25);
            confirm = getValidStringInput();
            
            if (confirm == "Y" || confirm == "y") {
                clearScreen();
                FiturTelusuriDungeon(); // Cutscene
                ArahDungeon(team, TEAM_SIZE, inventory);

                cout << "\nPlay Again?(Y/N) ";
                string choose = getValidStringInput();
                while (true) {
                    if (choose == "Y" || choose == "y") {
                        clearScreen();
                        break;
                    } else if (choose == "N" || choose == "n") {
                        return 0;
                    }
                    else {
                        typeText("Please enter Y or N.", 20);
                    }
                }
            } else if (confirm == "N" || confirm == "n") {
                typeText("Returning to character selection...", 20);
                break;
            } else {
                typeText("Please enter Y or N.", 20);
            }
        }
    }
    return 0;
}
