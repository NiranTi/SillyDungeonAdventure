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
    Character team[3];
    chooseCharacters(team);  // Pemain pilih tim
    vector<string> inventory;

    // Konfirmasi sebelum mulai
    string confirm;
    while (true) {
        typeText("\nStart the game? (Y/N)", 25);
        confirm = getValidStringInput();
        
        if (confirm == "Y" || confirm == "y") {
            clearScreen();
            FiturTelusuriDungeon(); // Cutscene
            ArahDungeon(team, TEAM_SIZE, inventory);          // Masuk eksplorasi
            break;
        } else if (confirm == "N" || confirm == "n") {
            typeText("Returning to character selection...", 20);
            chooseCharacters(team);  // Ulangi pemilihan karakter
        } else {
            typeText("Please enter Y or N.", 20);
        }
    }

    return 0;
}
