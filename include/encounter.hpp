#ifndef ENCOUNTER_HPP
#define ENCOUNTER_HPP

#include "karakter.hpp"
#include <string>
#include <vector>

struct enemies {
    std::string name;
    int hp;
    int maxHP;
    int atk;
    int speed;
    int defense;
    int debuff;
};

void encounterPercentage(int round, Character team[], std::vector<std::string>& inventory);



#endif
