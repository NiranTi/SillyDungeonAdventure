#include "Battle.h"
#include "Karakter.h" // Penting untuk menyertakan Karakter.h karena Battle.cpp menggunakan struct Karakter, SpeedTree, AttackQueue
#include <iostream>
#include <algorithm> // Untuk std::max, std::find

// ========================
// IMPLEMENTASI FUNGSI UTILITY
// ========================
void displayKarakter(const Karakter& karakter) {
    std::cout << "Nama : " << karakter.name << std::endl;
    std::cout << "HP: " << karakter.HP << std::endl;
    std::cout << "ATK: " << karakter.ATK << std::endl;
    std::cout << "SPEED: " << karakter.SPEED << std::endl;
    std::cout << "DEF: " << karakter.DEF << std::endl;
}

void initKarakter(Karakter karakters[]) {
    karakters[0] = {"zara", 82, 120, 70, 35};
    karakters[1] = {"gerald", 90, 100, 30, 5};
    karakters[2] = {"robin", 60, 50, 49, 9};
    karakters[3] = {"merlin", 99, 105, 80, 14};
    karakters[4] = {"robert", 43, 87, 45, 8};
    karakters[5] = {"hans", 67, 90, 93, 10};
    karakters[6] = {"sam", 76, 74, 87, 24};
    karakters[7] = {"lia", 91, 80, 55, 13};
    karakters[8] = {"tyla", 85, 94, 45, 12};
    karakters[9] = {"max", 90, 83, 79, 15};
}

void pilihKarakter(Karakter karakters[], Karakter& pilihan) {
    std::string inputName;
    bool ditemukan = false;
    const int MAX_KARAKTERS = 10; // Definisi ulang atau ambil dari header global jika ada

    while (!ditemukan) {
        std::cout << "\n===== Pilih Karakter yang anda inginkan =====\n";
        std::cout << "Daftar karakter: \n";

        for (int i = 0; i < MAX_KARAKTERS; i++) {
            if (karakters[i].name != "SUDAH_DIPILIH") { // Jangan tampilkan yang sudah dipilih
                 std::cout << "-" << karakters[i].name << " (HP: " << karakters[i].HP << ")(ATK: " << karakters[i].ATK << ")(SPD: " << karakters[i].SPEED << ")(DEF: " << karakters[i].DEF << ")\n";
            }
        }

        std::cout << "Masukan nama karakter yang anda pilih: ";
        std::getline(std::cin, inputName);

        for (int i = 0; i < MAX_KARAKTERS; i++) {
            if (karakters[i].name == inputName) {
                pilihan = karakters[i];
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            std::cout << "Karakter dengan nama " << inputName << " tidak ditemukan\n";
        }
    }
}

Karakter* findKarakter(const std::string& name, std::vector<Karakter>& team) {
    for (auto& kar : team) {
        if (kar.name == name) {
            return &kar;
        }
    }
    return nullptr;
}


// ========================
// IMPLEMENTASI FUNGSI BATTLE UTAMA
// ========================
void battle(std::vector<Karakter>& player_team, std::vector<Karakter>& enemy_team) {
    std::cout << "\n" << std::string(30, '=') << std::endl;
    std::cout << "           BATTLE START!          " << std::endl;
    std::cout << std::string(30, '=') << "\n" << std::endl;

    SpeedTree all_participants_tree;
    for (const auto& char_p : player_team) {
        all_participants_tree.insert(char_p);
    }
    for (const auto& char_e : enemy_team) {
        all_participants_tree.insert(char_e);
    }

    std::vector<Karakter> turn_order_initial = all_participants_tree.getCharactersBySpeedDescending();
    std::vector<Karakter*> turn_order;
    for(const auto& kar : turn_order_initial) {
        Karakter* found_char = findKarakter(kar.name, player_team);
        if (found_char == nullptr) {
            found_char = findKarakter(kar.name, enemy_team);
        }
        if (found_char != nullptr) {
            turn_order.push_back(found_char);
        }
    }

    std::cout << "Urutan Giliran (Berdasarkan Kecepatan):" << std::endl;
    for (size_t i = 0; i < turn_order.size(); ++i) {
        std::cout << i + 1 << ". " << turn_order[i]->name << " (Speed: " << turn_order[i]->SPEED << ")" << std::endl;
    }
    std::cout << std::string(30, '-') << std::endl;

    AttackQueue enemy_attack_queue;
    int turn_count = 0;

    while (true) {
        turn_count++;
        std::cout << "\n--- GILIRAN " << turn_count << " ---" << std::endl;

        bool player_team_alive = false;
        for (const auto& char_p : player_team) {
            if (char_p.isAlive()) {
                player_team_alive = true;
                break;
            }
        }
        if (!player_team_alive) {
            std::cout << "\n----- Anda Kalah! Semua Karakter Pemain Tumbang -----" << std::endl;
            break;
        }

        bool enemy_team_alive = false;
        for (const auto& char_e : enemy_team) {
            if (char_e.isAlive()) {
                enemy_team_alive = true;
                break;
            }
        }
        if (!enemy_team_alive) {
            std::cout << "\n----- Anda Menang! Semua Musuh Tumbang! -----" << std::endl;
            break;
        }

        for (Karakter* current_char_ptr : turn_order) {
            if (!current_char_ptr->isAlive()) {
                continue;
            }

            std::cout << "\nGiliran: " << current_char_ptr->name << std::endl;

            bool is_player = false;
            for (const auto& char_p : player_team) {
                if (char_p.name == current_char_ptr->name) {
                    is_player = true;
                    break;
                }
            }

            if (is_player) {
                Karakter* target_enemy = nullptr;
                for (auto& enemy : enemy_team) {
                    if (enemy.isAlive()) {
                        target_enemy = &enemy;
                        break;
                    }
                }

                if (target_enemy) {
                    std::cout << current_char_ptr->name << " menyerang " << target_enemy->name << "!" << std::endl;
                    target_enemy->takeDamage(current_char_ptr->ATK);
                } else {
                    std::cout << "Tidak ada musuh yang tersisa untuk diserang." << std::endl;
                }

            } else {
                Karakter* target_player = nullptr;
                for (auto& player : player_team) {
                    if (player.isAlive()) {
                        target_player = &player;
                        break;
                    }
                }

                if (target_player) {
                    enemy_attack_queue.addAttack(current_char_ptr, target_player, current_char_ptr->ATK);
                } else {
                    std::cout << "Tidak ada pemain yang tersisa untuk diserang." << std::endl;
                }
            }
        }

        std::cout << "\n--- Memproses Antrean Serangan Musuh (" << enemy_attack_queue.size() << " serangan) ---" << std::endl;
        while (!enemy_attack_queue.isEmpty()) {
            enemy_attack_queue.processNextAttack();
            bool current_player_team_alive = false;
            for (const auto& char_p : player_team) {
                if (char_p.isAlive()) {
                    current_player_team_alive = true;
                    break;
                }
            }
            if (!current_player_team_alive) {
                std::cout << "Pemain kalah selama pemrosesan antrean serangan musuh." << std::endl;
                goto end_battle;
            }
        }

        std::vector<Karakter*> new_turn_order;
        for (Karakter* char_ptr : turn_order) {
            if (char_ptr->isAlive()) {
                new_turn_order.push_back(char_ptr);
            }
        }
        turn_order = new_turn_order;

        std::cout << "\n--- STATUS HP SAAT INI ---" << std::endl;
        std::cout << "Pemain:" << std::endl;
        for (const auto& char_p : player_team) {
            std::cout << "- " << char_p.name << ": " << char_p.HP << " HP (" << (char_p.isAlive() ? "Hidup" : "Kalah") << ")" << std::endl;
        }
        std::cout << "Musuh:" << std::endl;
        for (const auto& char_e : enemy_team) {
            std::cout << "- " << char_e.name << ": " << char_e.HP << " HP (" << (char_e.isAlive() ? "Hidup" : "Kalah") << ")" << std::endl;
        }
        std::cout << std::string(30, '-') << std::endl;
    }

end_battle:;
    std::cout << "\n" << std::string(30, '=') << std::endl;
    std::cout << "           BATTLE END!            " << std::endl;
    std::cout << std::string(30, '=') << "\n" << std::endl;
}     