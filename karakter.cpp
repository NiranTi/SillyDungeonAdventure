#include <iostream>
#include <string>

using namespace std;

const int MAX_KARAKTERS = 10;

struct Karakter{
   string name;
   int HP;
   int ATK;
   int SPEED;
   int DEF;
};

void displayKarakter(const Karakter& karakter){
   cout << "Nama : " << karakter.name << endl;
   cout << "HP: " << karakter.HP << endl;
   cout << "ATK: " << karakter.ATK << endl;
   cout << "SPEED: " << karakter.SPEED << endl;
   cout << "DEF: " << karakter.DEF << endl;
}

void initKarakter(Karakter karakters[]){
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

void pilihKarakter(Karakter karakters[],Karakter& pilihan){
   string inputName;
   bool ditemukan = false;

   while (!ditemukan){
   cout << "\n===== Pilih Karakter yang anda inginkan =====\n";
   cout << "Daftar karakter: \n"; 

   for (int i = 0; i < MAX_KARAKTERS; i++){
      cout << "-" << karakters[i].name << " (" << karakters[i].HP << ")(" << karakters[i].ATK << ")(" <<karakters[i].SPEED << ")(" << karakters[i].DEF << ")\n";
   }

   cout << "Masukan nama karakter yang anda pilih: ";
   getline(cin, inputName);

   for (int i = 0; i < MAX_KARAKTERS; i++){
      if (karakters[i].name== inputName){
         pilihan = karakters[i];
         ditemukan = true;
         break;
      }
   }
   if (!ditemukan){
      cout << "karakter dengan nama " << inputName << " tidak ditemukan\n";
   }
   }
}

int main(){
   Karakter karakters[MAX_KARAKTERS];
   Karakter karakterPilihan;

   initKarakter(karakters);
   pilihKarakter(karakters, karakterPilihan);

   cout << "\n Karakter yang anda pilih\n" ;
   displayKarakter(karakterPilihan);

   return 0;
}