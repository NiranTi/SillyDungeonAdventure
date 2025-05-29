#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <string>
#include <vector>
#include "karakter.hpp"
#include "turnOrder.hpp"
#include "encounter.hpp"

int calculateDamage(int atk, int def);

void blinkText(const std::string& text, int times = 3, int delay = 100);

bool tryToRun();

enum BattleResult {
    PLAYER_WIN,
    PLAYER_LOSE,
    PLAYER_ESCAPED
};

BattleResult startBattle(Character team[], int teamSize, enemies& enemy, std::vector<std::string>& inventory);

#endif
