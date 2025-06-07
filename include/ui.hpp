#ifndef UI_HPP
#define UI_HPP

#include <string>
#include "karakter.hpp"

std::string colorText(const std::string& text, const std::string& color, const std::string& bgColor = "");
void printTitle(const std::string& title);
void highlightTurn(const std::string& name);
void printDivider();
std::string padText(const std::string& text, const std::string& color, int width);
void printHPBar(const std::string& name, int hp, int maxHP);
void typeText(const std::string& text, int delayMs = 30);
void printBattleUI(const Character team[], int teamSize, int activeIndex, const std::string& enemyName, int enemyHP, int enemyMaxHP);

#endif
