#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

int main(){
   json data;
   data ["Karaktrer"] = {
    {{"nama", "Thalor"}, {"HP", 150}, {"ATK", 40}, {"SPEED", 25}, {"DEF", 20}},
    {{"nama", "Elyndra"}, {"HP", 90}, {"ATK", 55}, {"SPEED", 30}, {"DEF", 8}},
    {{"nama", "Kael"}, {"HP", 95}, {"ATK", 45}, {"SPEED", 55}, {"DEF", 12}},
    {{"nama", "Liora"}, {"HP", 115}, {"ATK", 30}, {"SPEED", 40}, {"DEF", 15}},
    {{"nama", "Neil"}, {"HP", 85}, {"ATK", 50}, {"SPEED", 38}, {"DEF", 30}},
    {{"nama", "Vanya"}, {"HP", 130}, {"ATK", 20}, {"SPEED", 22}, {"DEF", 28}},
    {{"nama", "Lia"}, {"HP", 95}, {"ATK", 60}, {"SPEED", 50}, {"DEF", 9}},
    {{"nama", "Draxil"}, {"HP", 100}, {"ATK", 25}, {"SPEED", 47}, {"DEF", 13}},
    {{"nama", "Orin"}, {"HP", 80}, {"ATK", 35}, {"SPEED", 34}, {"DEF", 10}},
    {{"nama", "Sam"}, {"HP", 125}, {"ATK", 50}, {"SPEED", 25}, {"DEF", 5}},
   };

   cout << data.dump(4) << endl;

   ofstream file("karakter.json");
   if (file.is_open()){
      file << data.dump (4) << endl;
      file.close();
      cout << "Data karakter disimpan di karkteer.json" << endl;
   }else{
      cout << "Gagal menyimpan file" << endl;
   }
   return 0;
}