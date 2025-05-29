#ifndef KARAKTER_HPP
#define KARAKTER_HPP

#include <string>

#define TEAM_SIZE 3
#define CHARACTER_COUNT 10

struct Character {
    std::string name;
    int maxHP;
    int hp;
    int atk;
    int def;
    int speed;
};

void displayCharacters(bool chosen[10]);
void chooseCharacters(Character selectedCharacters[3]);

#endif
