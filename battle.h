#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include <string> // Untuk std::string
#include "Karakter.h" // Sertakan header Karakter untuk menggunakan struct Karakter

// Deklarasi fungsi utility
void displayKarakter(const Karakter& karakter);
void initKarakter(Karakter karakters[]);
void pilihKarakter(Karakter karakters[], Karakter& pilihan);
Karakter* findKarakter(const std::string& name, std::vector<Karakter>& team);

// Deklarasi fungsi battle utama
void battle(std::vector<Karakter>& player_team, std::vector<Karakter>& enemy_team);

#endif // BATTLE_H