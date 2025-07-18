#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "login.hpp"
#include "leaderboard.hpp"
#include "session.hpp"

using namespace std;
using namespace std::chrono;

void saveToLeaderboard(bool cleared) {
    auto endTime = steady_clock::now();
    duration<double> elapsed = endTime - startTime;
    double timeTaken = elapsed.count(); // in seconds

    ofstream file("leaderboard.csv", ios::app); // append mode
    if (file.is_open()) {
        file << playerName << "," << (cleared ? "Cleared" : "Defeated") << "," << timeTaken << "\n";
        file.close();
    } else {
        cerr << "Failed to open leaderboard file.\n";
    }
}

#include <iomanip> 

void displayLeaderboard() {
    ifstream file("leaderboard.csv");
    if (!file.is_open()) {
        cout << "No leaderboard found.\n";
        return;
    }

    cout << "\n============ Leaderboard ============\n";
    cout << left << setw(15) << "Name"
         << setw(12) << "Result"
         << setw(10) << "Time (s)" << endl;
    cout << "-------------------------------------\n";

    string name, result, time;
    while (getline(file, name, ',')) {
        getline(file, result, ',');
        getline(file, time);

        cout << left << setw(15) << name
             << setw(12) << result
             << setw(10) << time << endl;
    }

    file.close();
}