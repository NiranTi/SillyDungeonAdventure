#ifndef KARAKTER_H
#define KARAKTER_H

#include <string>
#include <vector>
#include <queue> // Untuk std::queue

// Forward declaration untuk menghindari circular dependency
struct BSTNode;

struct Karakter {
    std::string name;
    int HP;
    int ATK;
    int SPEED;
    int DEF;

    bool isAlive() const;
    void takeDamage(int damage);
};

// ========================
// BST UNTUK PENGURUTAN SPEED
// ========================
struct BSTNode {
    Karakter character;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Karakter& kar);
    ~BSTNode(); // Destructor untuk membersihkan memori secara rekursif
};

class SpeedTree {
public:
    BSTNode* root;

    SpeedTree();
    ~SpeedTree(); // Destructor untuk membersihkan seluruh pohon

    void insert(const Karakter& character);
    std::vector<Karakter> getCharactersBySpeedDescending() const;

private:
    void _insertRecursive(BSTNode* node, const Karakter& character);
    void _reverseInOrderTraversal(BSTNode* node, std::vector<Karakter>& characters) const;
};

// ========================
// QUEUE UNTUK SERANGAN MUSUH
// ========================
struct AttackInfo {
    Karakter* attacker; // Pointer ke Karakter yang menyerang
    Karakter* target;   // Pointer ke Karakter yang menjadi target
    int damage;

    AttackInfo(Karakter* att, Karakter* tar, int dmg);
};

class AttackQueue {
public:
    std::queue<AttackInfo> q;

    void addAttack(Karakter* attacker, Karakter* target, int damage);
    void processNextAttack();
    bool isEmpty() const;
    size_t size() const;
};

#endif // KARAKTER_H