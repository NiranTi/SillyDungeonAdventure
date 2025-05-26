#include <iostream>
#include <random>
using namespace std;

struct enemies{
    int hp;
    int atk;
    int speed;
    int defense;
    int debuff;
};

struct items{
    int heal_potion;
    int devil_fruit;
    int elixir;
};

void encounterPercentage(int round) {
    enemies rookie = {100, 10, 5, 2, 4};
    enemies mid = {200, 20, 20, 3, 4};
    enemies boss = {500, 45, 35, 5, 4};

    if (round == 10) {
        cout << "BOSS FIGHT!\n\n";
        cout << "HP | " << boss.hp << endl;
        cout << "ATK | " << boss.atk << endl;
        cout << "SPEED | " << boss.speed << endl;
        cout << "DEF | " << boss.defense << endl;
    }
    else {
        int check = round % 10;

        if (check == 1 || check == 4 || check == 7) {
            cout << "ROOKIE ENEMY ENCOUNTERED!\n\n";
            cout << "HP | " << rookie.hp << endl;
            cout << "ATK | " << rookie.atk << endl;
            cout << "SPEED | " << rookie.speed << endl;
            cout << "DEF | " << rookie.defense << endl;
        }
        else if (check == 2 || check == 6) {
            cout << "MID ENEMY ENCOUNTERED!\n\n";
            cout << "HP | " << mid.hp << endl;
            cout << "ATK | " << mid.atk << endl;
            cout << "SPEED | " << mid.speed << endl;
            cout << "DEF | " << mid.defense << endl;
        }
        else if (check == 3 || check == 9) {
            int chestDrop = round % 3;
            cout << "You've found a chest!\n\n";

            items chest = {0, 0, 0};
            if (chestDrop == 0) {
                chest.heal_potion = 1;
                cout << "Congrats! You've received Heal Potion!" << endl;
            }
            else if (chestDrop == 1) {
                chest.devil_fruit = 1;
                cout << "Congrats! You've received Devil Fruit!" << endl;
            }
            else{
                chest.elixir = 1;
                cout << "Congrats! You've received Elixir!" << endl;
            }
        }
        else{
            cout << "There's nothing here..." << endl;
        }
    }
}

int main() {
    for (int round = 1; round <= 10; round++) {
        encounterPercentage(round);
    }
    return 0;
}