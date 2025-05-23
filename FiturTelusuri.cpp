#include<iostream>
using namespace std;

void FiturTelusuriDungeon()
{
    cout << "\033[32m";
    cout << "Di tengah lautan bergelombang dan langit mendung, kapal Flying Dutchman berlayar menuju pulau yang tak ada di peta." << endl;
    cout << "Menurut peta kuno dari buku tua, di sanalah harta karun legendaris tersembunyi dan terkunci dalam dungeon bawah tanah, dijaga monster.\n" << endl;
    cout << "Sesampainya di pulau, Kapten Dutchman dan krunya menembus hutan gelap." << endl;
    cout << "Di ujungnya, mereka menemukan pintu batu menuju kegelapan" << endl;
    cout << "Untuk mendapatkan harta itu, sang kapten harus menghadapi bahaya yang tak pernah dibayangkan sebelumnya..." << endl;
    cout << "\033[0m";
}

void ArahDungeoun()
{
    int x= 0, y= 0;
    char input;

    while (true) {
        cout << "\nKetik 'F' untuk maju, 'B' untuk mundur, 'L' untuk belok kiri, 'R' untuk belok kanan, atau 'q' untuk keluar: ";
        cin >> input;

        if (input == 'q') {
            break;
        } else if (input == 'F' || input == 'f') {
            y++;
        } else if (input == 'B' || input == 'b') {
            y--;
        } else if (input == 'L' || input == 'l') {
            x--;
        } else if (input == 'R' || input == 'r') {
            x++;
        } else {
            cout << "Input tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main() {
    FiturTelusuriDungeon();
    ArahDungeoun();
    return 0;
}
