#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <future> 
#include "ui.hpp"
using namespace std;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush buffer
    cin.get(); // tunggu enter
}

int getValidIntegerInput() {
    int input;
    while (true) {
        cout << "> ";
        if (cin >> input) {
            return input;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            typeText("Please enter a valid integer!", 20);
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

void wait() {
    cout << "Continuing in 5 seconds";
    cout.flush();
    for (int i = 0; i < 5; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "." << flush;
    }
    cout << "\n";
}

