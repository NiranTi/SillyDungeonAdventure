#include <iostream>
#include <vector>
#include <string>
#include "Karakter.h" // Sertakan header Karakter
#include "Battle.h"   // Sertakan header Battle

// Konstanta bisa didefinisikan di sini atau di file header global jika banyak digunakan
const int MAX_KARAKTERS_GLOBAL = 10; // Contoh, jika Anda ingin membuatnya global

int main() {
    Karakter all_karakters[MAX_KARAKTERS_GLOBAL]; // Gunakan konstanta global
    initKarakter(all_karakters);

    std::vector<Karakter> player_team;
    std::cout << "Pilih 3 karakter untuk tim Anda:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        Karakter temp_pilihan;
        pilihKarakter(all_karakters, temp_pilihan);
        player_team.push_back(temp_pilihan);
        std::cout << "\nKarakter yang Anda pilih: " << temp_pilihan.name << std::endl;
        // Tandai karakter di array all_karakters agar tidak dipilih lagi
        for(int j = 0; j < MAX_KARAKTERS_GLOBAL; ++j) {
            if (all_karakters[j].name == temp_pilihan.name) {
                all_karakters[j].name = "SUDAH_DIPILIH";
                break;
            }
        }
    }

    std::cout << "\n===== Tim Anda =====" << std::endl;
    for (const auto& kar : player_team) {
        displayKarakter(kar);
        std::cout << std::endl;
    }
    std::cout << std::string(20, '=') << std::endl;

    std::vector<Karakter> enemy_team;
    enemy_team.push_back({"Goblin", 60, 10, 8, 5});
    enemy_team.push_back({"Orc", 120, 20, 5, 10});
    enemy_team.push_back({"Skeleton", 50, 18, 11, 7});

    std::cout << "\n===== Tim Musuh =====" << std::endl;
    for (const auto& kar : enemy_team) {
        displayKarakter(kar);
        std::cout << std::endl;
    }
    std::cout << std::string(20, '=') << std::endl;

    battle(player_team, enemy_team);

    return 0;
}