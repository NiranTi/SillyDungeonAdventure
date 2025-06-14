#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

int main(){
    unordered_map <string, string>userDatabase={
        {"player 1", "pass123"},
        {"admin", "adminpass"},
        {"geust", "geustpass"},
    };

    string username;
    string password;

    cout << "===Game Login===\n";

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    auto it = userDatabase.find(username);
    if (it != userDatabase.end() && it->second == password){
        cout << "Login Seccessful! Welcome, " << username << ".\n";
    }else{
        cout << "Login failed. Incorrent in username or password";
    }
    return 0;
}