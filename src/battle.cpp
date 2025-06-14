#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include <limits>
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
        int i = 0;
        while (i < teamSize) {
            if (team[i].hp <= 0) {
            ++i;
            continue;
            }

        printBattleUI(team, teamSize, i, enemy.name, enemy.hp, enemy.maxHP);

        cout << team[i].name << ", choose action:\n";
        cout << "0: FIGHT\n1: ACT\n2: ITEM\n3: RUN\n4: UNDO last action\n";

        int action = getValidIntegerInput();

        if (action >= 0 && action <= 3) {
            plannedActions.push_back({ team[i].name, action });
            ++i;
        } else if (action == 4) {
        if (!plannedActions.empty() && i > 0) {
            plannedActions.pop_back();
            --i;
            cout << "Undoing action for " << team[i].name << ".\n";
        } else {
            cout << "Nothing to undo.\n";
        }
        } else {
        cout << "Invalid action. Please choose again.\n";
        }
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
                        if (team[teamIdx].hp<= 0) {
                            cout << team[teamIdx].name << " fainted before taking action!\n";
                            continue;
                        } else {
                            int dmg = calculateDamage(current.atk, enemy.defense);
                            enemy.hp -= dmg;
                            cout << current.name << " attacks " << enemy.name << " for " << dmg << " damage!" << endl;
                            blinkText(enemy.name);
                            break;
                        }
                    }
                    case 1: {
                        if (team[teamIdx].hp<= 0) {
                            cout << team[teamIdx].name << " fainted before taking action!\n";
                            continue;
                        } else {
                            cout << team[teamIdx].name << " choose ACT:\n";
                            cout << "1: CHECK\n";
                            cout << "2: DISPEL\n";
                            int subchoice = getValidIntegerInput();
                            if (subchoice == 1) {
                                cout << "[CHECK] " << enemy.name << " - HP: " << enemy.hp << "/" << enemy.maxHP
                                    << ", ATK: " << enemy.atk << ", DEF: " << enemy.defense << endl;
                            } else if (subchoice == 2) {
                                if (!team[teamIdx].debuffs.empty()) {
                                    DebuffEffect removed = team[teamIdx].debuffs.front();
                                    team[teamIdx].debuffs.pop();
                                    cout << team[teamIdx].name; typeText(" dispelled defense down effect.\n",30);
                                } else {cout << "No debuffs to dispel!\n";}
                            }
                            pause();
                            break;
                        }
                    }
                    case 2: {
                        if (team[teamIdx].hp<= 0) {
                            cout << team[teamIdx].name << " fainted before taking action!\n";
                            continue;
                        } else {
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
                        };
                    }
                    case 3: {
                        if (team[teamIdx].hp<= 0) {
                            cout << team[teamIdx].name << " fainted before taking action!\n";
                            continue;
                        } else {
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
                }
            } else {
                int effectiveDef = current.def;
                queue<DebuffEffect> temp = current.debuffs;
                while (!temp.empty()) {
                    DebuffEffect debuff = temp.front();
                    temp.pop();

                    if (debuff.type == "DEFENSE_DOWN") {
                        effectiveDef += debuff.value;
                    }
                }

                // Enemy attacks random alive character
                vector<Character*> alive;
                for (int i = 0; i < teamSize; ++i)
                    if (team[i].hp > 0) alive.push_back(&team[i]);

                if (!alive.empty()) {
                    Character* target = alive[rand() % alive.size()];
                    int dmg = calculateDamage(current.atk, effectiveDef);
                    target->hp -= dmg;
                    if (target->hp < 0) target->hp = 0;
                    cout << current.name << " attacks " << target->name << " for " << dmg << " damage!" << endl;
                    blinkText(target->name);

                    if (rand() % 2 == 0) {
                        int value = rand();
                        target->debuffs.push(DebuffEffect("DEFENSE_DOWN", -5));
                        cout << target->name << " is afflicted with DEFENSE DOWN!\n";
                    }
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
        pause();
    }
    return PLAYER_ESCAPED;
}
