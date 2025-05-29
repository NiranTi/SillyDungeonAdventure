#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include "karakter.hpp"
#include "turnOrder.hpp"
#include "ui.hpp"
#include "encounter.hpp"
#include "utils.hpp"
#include "inventory.hpp"
#include "battle.hpp"

using namespace std;

// === UTILITAS ===
int calculateDamage(int atk, int def) {
    return max(1, atk - def);
}

void blinkText(const string& text, int times, int delay) {
    for (int i = 0; i < times; ++i) {
        cout << "\r" << text << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
        cout << "\r" << string(text.length(), ' ') << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << "\r" << text << endl;
}

bool tryToRun() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    return dis(gen) == 1;
}

// === FUNGSI BATTLE ===
BattleResult startBattle(Character team[], int teamSize, enemies& enemy, vector<string>& inventory) {
    Character enemyChar = {
        enemy.name,
        enemy.maxHP,
        enemy.hp,
        enemy.atk,
        enemy.defense,
        enemy.speed
    };

    bool battleOngoing = true;
    bool escaped = false;

    while (battleOngoing) {
        // Pilih aksi dari kiri ke kanan (team[0] -> team[2])
        struct Action {
            string actorName;
            int actionType;  // 0: Fight, 1: Check, 2: Item, 3: Run
        };
        vector<Action> plannedActions;

        cout << "=== ACTION SELECTION PHASE ===" << endl;
        for (int i = 0; i < teamSize; ++i) {
            if (team[i].hp <= 0) continue;

            printBattleUI(team, teamSize, i, enemy.name, enemy.hp, enemy.maxHP);

            int action = -1;
            while (true) {
                cout << team[i].name << ", choose action (0: FIGHT, 1: CHECK, 2: ITEM, 3: RUN): ";
                action = getValidIntegerInput();
                if (action >= 0 && action <= 3) break;
                cout << "Invalid action. Please choose again.\n";
            }

            plannedActions.push_back({ team[i].name, action });
        }

        // Bangun binary tree berdasarkan speed
        TreeNode* root = nullptr;
        for (int i = 0; i < teamSize; ++i) {
            if (team[i].hp > 0)
                root = insertBySpeed(root, team[i]);
        }
        if (enemy.hp > 0)
            root = insertBySpeed(root, enemyChar);

        // Eksekusi berdasarkan reverse inorder (kecepatan tertinggi -> terendah)
        vector<Character> turnOrder;
        reverseInorder(root, turnOrder);

        for (Character& current : turnOrder) {
            if (current.hp <= 0) continue;

            // Cek apakah current adalah player
            int teamIdx = -1;
            for (int i = 0; i < teamSize; ++i) {
                if (team[i].name == current.name) {
                    teamIdx = i;
                    break;
                }
            }

            if (teamIdx != -1) {
                // Temukan aksi yang dipilih sebelumnya
                int chosenAction = -1;
                for (auto& action : plannedActions) {
                    if (action.actorName == current.name) {
                        chosenAction = action.actionType;
                        break;
                    }
                }

                switch (chosenAction) {
                    case 0: { // FIGHT
                        int dmg = calculateDamage(current.atk, enemy.defense);
                        enemy.hp -= dmg;
                        cout << current.name << " attacks " << enemy.name << " for " << dmg << " damage!" << endl;
                        blinkText(enemy.name);
                        break;
                    }
                    case 1: { // CHECK
                        cout << "[CHECK] " << enemy.name << " - HP: " << enemy.hp << "/" << enemy.maxHP
                            << ", ATK: " << enemy.atk << ", DEF: " << enemy.defense << endl;
                        pause();
                        break;
                    }
                    case 2: {
                        displayInventory(inventory);
                        int itemIndex = -1;
                        if (!isEmpty(inventory)) {
                            while (true) {
                                cout << "Choose item index: ";
                                itemIndex = getValidIntegerInput();
                                if (itemIndex >= 0 && itemIndex < inventory.size()) break;
                                cout << "Invalid item index. Try again.\n";
                            }

                            string chosenItem = inventory[itemIndex];

                            // Pilih target
                            int targetIndex = -1;
                            while (true) {
                                cout << "Choose target:\n";
                                for (int i = 0; i < teamSize; ++i) {
                                    if (team[i].hp > 0)
                                        cout << i << ": " << team[i].name << " (HP: " << team[i].hp << "/" << team[i].maxHP << ")\n";
                                }

                                targetIndex = getValidIntegerInput();
                                if (targetIndex >= 0 && targetIndex < teamSize && team[targetIndex].hp > 0) break;

                                cout << "Invalid target. Try again.\n";
                            }

                            // Gunakan item
                            bool success = useItem(inventory, chosenItem, team[targetIndex]);
                            if (success) {
                                cout << "Used " << chosenItem << " on " << team[targetIndex].name << "!\n";
                            }
                            break;
                        } break;                    
                    }
                    case 3: {
                        if (enemy.name != "Boss Enemy") {
                            if (tryToRun()) {
                                cout << current.name << " tried to run... Success!\n";
                                escaped = true;
                                battleOngoing = false;
                                break;
                            } else {
                                cout << current.name << " tried to run... but failed!\n";
                            }
                        } else {typeText("You can't run from the boss!", 30);}
                        break;
                    }
                }
            } else {
                // Enemy attacks random alive character
                vector<Character*> alive;
                for (int i = 0; i < teamSize; ++i)
                    if (team[i].hp > 0) alive.push_back(&team[i]);

                if (!alive.empty()) {
                    Character* target = alive[rand() % alive.size()];
                    int dmg = calculateDamage(current.atk, target->def);
                    target->hp -= dmg;
                    cout << current.name << " attacks " << target->name << " for " << dmg << " damage!" << endl;
                    blinkText(target->name);
                }
            }

            if (enemy.hp <= 0) {
                cout << enemy.name << " has been defeated!\n";
                if (enemy.name == "Boss Enemy") {
                    return PLAYER_WIN; // signal game should stop
                }
                battleOngoing = false;
                break;
            }

            bool allDead = true;
            for (int i = 0; i < teamSize; ++i) {
                if (team[i].hp > 0) {
                    allDead = false;
                    break;
                }
            }
            if (allDead) {
                cout << "All party members have fallen...\n";
                battleOngoing = false;
                return PLAYER_LOSE;
            }

            if (escaped) break;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        deleteTree(root);
    }
    return PLAYER_ESCAPED;
}
