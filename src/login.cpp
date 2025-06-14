#include <iostream>
#include <string>
#include <chrono>
#include "login.hpp"
#include "ui.hpp"
#include "session.hpp"

using namespace std;
using namespace std::chrono;

void login() {
    typeText("Enter your name: ",20);
    getline(cin, playerName); // make sure to use getline for spaces
    startTime = steady_clock::now();
}
