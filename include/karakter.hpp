#ifndef KARAKTER_HPP
#define KARAKTER_HPP

#include <string>
#include <queue>

#define TEAM_SIZE 3
#define CHARACTER_COUNT 10

struct DebuffEffect {
    std::string type;
    int value;

    DebuffEffect(std::string t, int v) : type(t), value(v) {}
};

struct Character {
    std::string name;
    int maxHP;
    int hp;
    int atk;
    int def;
    int speed;

    std::queue<DebuffEffect> debuffs;
};

void displayCharacters(bool chosen[10]);
void chooseCharacters(Character selectedCharacters[3]);

#endif
