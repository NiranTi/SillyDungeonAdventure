#include <iostream>
#include <limits>
#include "ui.hpp"
using namespace std;

int getValidIntegerInput() {
    int input;
    while (true) {
        cout << "> ";
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            typeText("Please enter a valid integer!", 20);
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean extra chars
            return input;
        }
    }
}

string getValidStringInput() {
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input.empty()) {
            typeText("Input cannot be empty. Try again.", 20);
        } else {
            return input;
        }
    }
}
