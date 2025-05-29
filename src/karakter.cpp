#include "karakter.hpp"
#include "utils.hpp"
#include "ui.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

Character characters[CHARACTER_COUNT] = {
    {"Zara  ", 120, 120, 70, 35, 82},
    {"Gerald", 100, 100, 30, 5, 90},
    {"Robin ", 50 , 50 , 49, 9, 60},
    {"Merlin", 105, 105, 80, 14, 99},
    {"Robert", 87 , 87 , 45, 8, 43},
    {"Hans  ", 90 , 90 , 93, 10, 67},
    {"Sam   ", 74 , 74 , 87, 24, 76},
    {"Lia   ", 80 , 80 , 55, 13, 91},
    {"Tyla  ", 94 , 94 , 45, 12, 85},
    {"Max   ", 83 , 83 , 79, 15, 90}
};

void displayCharacters(bool selected[]) {
    const int perRow = 5;
    const int columnWidth = 35;

    for (int rowStart = 0; rowStart < CHARACTER_COUNT; rowStart += perRow) {
        int rowEnd = min(rowStart + perRow, CHARACTER_COUNT);

        // Line 1: Character Names or Placeholder
        for (int i = rowStart; i < rowEnd; ++i) {
            if (!selected[i]) {
                string label = "[" + to_string(i) + "] " + characters[i].name;
                cout << padText(label, "cyan", columnWidth);
            } else {
                cout << padText("[X] -------", "red", columnWidth);
            }
        }
        cout << '\n';

        // Line 2: HP
        for (int i = rowStart; i < rowEnd; ++i) {
            if (!selected[i])
                cout << padText("HP : " + to_string(characters[i].hp), "green", columnWidth);
            else
                cout << string(columnWidth, ' ');
        }
        cout << '\n';

        // Line 3: ATK
        for (int i = rowStart; i < rowEnd; ++i) {
            if (!selected[i])
                cout << padText("ATK: " + to_string(characters[i].atk), "magenta", columnWidth);
            else
                cout << string(columnWidth, ' ');
        }
        cout << '\n';

        // Line 4: DEF
        for (int i = rowStart; i < rowEnd; ++i) {
            if (!selected[i])
                cout << padText("DEF: " + to_string(characters[i].def), "blue", columnWidth);
            else
                cout << string(columnWidth, ' ');
        }
        cout << '\n';

        // Line 5: SPD
        for (int i = rowStart; i < rowEnd; ++i) {
            if (!selected[i])
                cout << padText("SPD: " + to_string(characters[i].speed), "yellow", columnWidth);
            else
                cout << string(columnWidth, ' ');
        }
        cout << '\n';

        // Separator
        cout << string(columnWidth * perRow, '-') << '\n';
    }
}


void chooseCharacters(Character team[TEAM_SIZE]) {
    bool selected[CHARACTER_COUNT] = {false};
    int input;
    int selectedCount = 0;

    while (selectedCount < TEAM_SIZE) {
        clearScreen();
        typeText("Choose " + to_string(TEAM_SIZE - selectedCount) + " more character(s).", 25);
        displayCharacters(selected);

        cout << "\nEnter index for character #" << selectedCount + 1 << ": ";
        input = getValidIntegerInput();

        if (input < 0 || input >= CHARACTER_COUNT) {
            typeText("That index is out of range!", 20);
        } else if (selected[input]) {
            typeText("That character is already chosen!", 20);
        } else {
            team[selectedCount] = characters[input];
            selected[input] = true;
            typeText(">> " + characters[input].name + " has joined your team!", 30);
            selectedCount++;
        }

        pause();
    }
    clearScreen();
}
