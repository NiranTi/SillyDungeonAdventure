#include "ui.hpp"
#include "utils.hpp"
#include "FiturTelusuri.hpp"
#include "encounter.hpp"
#include "karakter.hpp"
#include "inventory.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 

using namespace std;

void FiturTelusuriDungeon() {
    clearScreen();
    printTitle("SILLY DUNGEON ADVENTURE");
    int delay = 20;

    cout << colorText("", "green") << flush;
    typeText("Amidst stormy seas and a sky heavy with clouds...", delay);
    typeText("The Flying Dutchman sails toward an island not found on any map.", delay);
    typeText("According to an ancient book, a legendary treasure lies hidden in a deep, dark dungeon.", delay);
    typeText("Guarded by monsters... and sealed away from the world.", delay);
    typeText("\nAt last, the ship reaches the island.", delay);
    typeText("Captain Dutchman and his crew descend into a dense jungle.", delay);
    typeText("At the edge of the jungle stands a massive stone door.", delay);
    typeText("It leads into darkness, into danger, into destiny...", delay);
    cout << "\033[0m";
    pause();
}

void ArahDungeon(Character team[], int teamSize, vector<string>& inventory) {
    clearScreen();
    printTitle("DUNGEON EXPLORATION");

    int round = 1;

    while (true) {
        cout << colorText("\nChoose your direction.", "cyan") << endl;
        cout << "Type " << colorText("'W'", "yellow") << " to go Forward, "
             << colorText("'A'", "yellow") << " to go Left, "
             << colorText("'D'", "yellow") << " to go Right, or "
             << colorText("'Q'", "red") << " to Quit." << endl;

        cout << "> ";
        char input = tolower(getch());  // input real-time (tanpa Enter)
        cout << input << endl;          // tampilkan input setelah '>'

        if (input == 'q') {
            clearScreen();
            typeText("You decide to retreat... for now.", 30);
            break;
        } else if (input == 'w') {
            clearScreen();
            typeText("You move forward. The darkness thickens...", 30);
            encounterPercentage(round, team, inventory);
        } else if (input == 'a') {
            clearScreen();
            typeText("You take a left. Faint whispers echo from the walls...", 30);
            encounterPercentage(round, team, inventory);
        } else if (input == 'd') {
            clearScreen();
            typeText("You turn right. The air grows colder...", 30);
            encounterPercentage(round, team, inventory);
        } else {
            clearScreen();
            typeText("That direction makes no sense here.", 20);
        }

        round++;
        wait();
        clearScreen();
    }
}