#include "ui.hpp"
#include "encounter.hpp"
#include "karakter.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\n(Press Enter to continue...)";
    cin.ignore();
    cin.get();
}

string colorText(const std::string& text, const std::string& color, const std::string& bgColor) {
    string code = "\033[";

    // Text color
    if (color == "black") code += "30";
    else if (color == "red") code += "31";
    else if (color == "green") code += "32";
    else if (color == "yellow") code += "33";
    else if (color == "blue") code += "34";
    else if (color == "magenta") code += "35";
    else if (color == "cyan") code += "36";
    else if (color == "white") code += "37";
    else code += "0"; // reset

    // Background color
    if (bgColor != "") {
        code += ";";
        if (bgColor == "black") code += "40";
        else if (bgColor == "red") code += "41";
        else if (bgColor == "green") code += "42";
        else if (bgColor == "yellow") code += "43";
        else if (bgColor == "blue") code += "44";
        else if (bgColor == "magenta") code += "45";
        else if (bgColor == "cyan") code += "46";
        else if (bgColor == "white") code += "47";
    }

    code += "m";
    return code + text + "\033[0m";  // Always reset after
}

string padText(const string& text, const string& color, int width) {
    string raw = text;
    int padLength = max(0, width - (int)text.length());
    return colorText(raw + string(padLength, ' '), color);
}

void printTitle(const string& title) {
    printDivider();
    cout << colorText("========= " + title + " =========", "cyan") << "\n";
    printDivider();
}

void highlightTurn(const string& name) {
    cout << colorText("\n>> It's " + name + "'s turn! <<\n", "yellow");
}

void printDivider() {
    cout << colorText("--------------------------------------------", "magenta") << "\n";
}

string repeat(const std::string& ch, int count) {
    string result;
    for (int i = 0; i < count; ++i) result += ch;
    return result;
}

void printHPBar(const string& name, int hp, int maxHP) {
    int totalBars = 20;
    int filled = (hp * totalBars) / maxHP;

    string filledBar = repeat("#", filled);
    string emptyBar  = repeat("-", totalBars - filled);

    cout << colorText(name, "cyan") << " \t[HP: " << hp << " / " << maxHP << "] ";
    cout << colorText("\n[" + filledBar + emptyBar + "]\n\n", hp > maxHP / 2 ? "green" : "red");
}

void typeText(const std::string& text, int delayMs) {
    for (char c : text) {
        cout << c << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    cout << endl;
}

void printBattleUI(const Character team[], int teamSize, int activeIndex, const string& enemyName, int enemyHP, int enemyMaxHP) {
    clearScreen();

    // Tampilkan musuh
    cout << colorText("             Enemy: " + enemyName, "red") << endl;
    printHPBar("Enemy", enemyHP, enemyMaxHP);

    printDivider();

    // Menu aktif karakter
    for (int i = 0; i < 4; ++i) {
        string option;
        switch (i) {
            case 0: option = "FIGHT"; break;
            case 1: option = "CHECK"; break;
            case 2: option = "ITEM"; break;
            case 3: option = "RUN"; break;
        }
        if (i == 0) cout << "| ";  // awal baris
        cout << colorText("  " + option + "  ", (activeIndex == 0 ? "yellow" : "white")) << " | ";
    }
    cout << "\n";
    printDivider();

    // Tampilkan karakter + HP bar
    for (int i = 0; i < teamSize; ++i) {
        string pointer = (i == activeIndex) ? colorText(">> ", "yellow") : "   ";
        cout << pointer;
        printHPBar(team[i].name, team[i].hp, team[i].maxHP);
    }

    cout << endl;
}
