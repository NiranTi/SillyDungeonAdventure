#include "ui.hpp"
#include "utils.hpp"
#include "FiturTelusuri.hpp"
#include "encounter.hpp"
#include "karakter.hpp"
#include "inventory.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void FiturTelusuriDungeon() {
    clearScreen();
    printTitle("SILLY DUNGEON ADVENTURE");

    cout << colorText("", "green") << flush;
    typeText("Amidst stormy seas and a sky heavy with clouds...", 35);
    typeText("The Flying Dutchman sails toward an island not found on any map.", 35);
    typeText("According to an ancient book, a legendary treasure lies hidden in a deep, dark dungeon.", 35);
    typeText("Guarded by monsters... and sealed away from the world.", 35);
    typeText("\nAt last, the ship reaches the island.", 35);
    typeText("Captain Dutchman and his crew descend into a dense jungle.", 35);
    typeText("At the edge of the jungle stands a massive stone door.", 35);
    typeText("It leads into darkness, into danger, into destiny...", 35);
    cout << "\033[0m";
    pause();
}

void ArahDungeon(Character team[], int teamSize, vector<string>& inventory) {
    clearScreen();
    printTitle("DUNGEON EXPLORATION");

    int round = 1;
    string input;

    while (true) {
        cout << colorText("\nChoose your direction.", "cyan") << endl;
        cout << "Type " << colorText("'F'", "yellow") << " to go Forward, "
             << colorText("'L'", "yellow") << " to go Left, "
             << colorText("'R'", "yellow") << " to go Right, or "
             << colorText("'Q'", "red") << " to Quit.\n";

        input = getValidStringInput();

        // convert to lowercase for simplicity
        for (auto& c : input) c = tolower(c);

        if (input == "q") {
            clearScreen();
            typeText("You decide to retreat... for now.", 30);
            break;
        } else if (input == "f") {
            clearScreen();
            typeText("You move forward. The darkness thickens...", 30);
            encounterPercentage(round, team,inventory);
        } else if (input == "l") {
            clearScreen();
            typeText("You take a left. Faint whispers echo from the walls...", 30);
            encounterPercentage(round, team,inventory);
        } else if (input == "r") {
            clearScreen();
            typeText("You turn right. The air grows colder...", 30);
            encounterPercentage(round, team, inventory);
        } else {
            clearScreen();
            typeText("That direction makes no sense here.", 20);
            continue;
        }

        round++;  // Round naik setelah langkah valid
        pause();
        clearScreen();
    }
}
