#include "Karakter.h"
#include <iostream>
#include <algorithm> // Untuk std::max

// ========================
// IMPLEMENTASI STRUCT KARAKTER
// ========================
bool Karakter::isAlive() const {
    return HP > 0;
}

void Karakter::takeDamage(int damage) {
    int actualDamage = std::max(0, damage - DEF);
    HP -= actualDamage;
    if (HP < 0) {
        HP = 0;
    }
    std::cout << name << " menerima " << actualDamage << " damage. HP tersisa: " << HP << std::endl;
}

// ========================
// IMPLEMENTASI BST UNTUK PENGURUTAN SPEED
// ========================
BSTNode::BSTNode(const Karakter& kar) : character(kar), left(nullptr), right(nullptr) {}

BSTNode::~BSTNode() {
    delete left;
    delete right;
}

SpeedTree::SpeedTree() : root(nullptr) {}

SpeedTree::~SpeedTree() {
    delete root;
}

void SpeedTree::insert(const Karakter& character) {
    if (!root) {
        root = new BSTNode(character);
    } else {
        _insertRecursive(root, character);
    }
}

void SpeedTree::_insertRecursive(BSTNode* node, const Karakter& character) {
    if (character.SPEED < node->character.SPEED) {
        if (node->left == nullptr) {
            node->left = new BSTNode(character);
        } else {
            _insertRecursive(node->left, character);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new BSTNode(character);
        } else {
            _insertRecursive(node->right, character);
        }
    }
}

std::vector<Karakter> SpeedTree::getCharactersBySpeedDescending() const {
    std::vector<Karakter> characters;
    _reverseInOrderTraversal(root, characters);
    return characters;
}

void SpeedTree::_reverseInOrderTraversal(BSTNode* node, std::vector<Karakter>& characters) const {
    if (node) {
        _reverseInOrderTraversal(node->right, characters);
        characters.push_back(node->character);
        _reverseInOrderTraversal(node->left, characters);
    }
}

// ========================
// IMPLEMENTASI QUEUE UNTUK SERANGAN MUSUH
// ========================
AttackInfo::AttackInfo(Karakter* att, Karakter* tar, int dmg) : attacker(att), target(tar), damage(dmg) {}

void AttackQueue::addAttack(Karakter* attacker, Karakter* target, int damage) {
    q.push(AttackInfo(attacker, target, damage));
    std::cout << "[QUEUE] " << attacker->name << " menambahkan serangan ke " << target->name << " sebesar " << damage << " ke antrean." << std::endl;
}

void AttackQueue::processNextAttack() {
    if (!isEmpty()) {
        AttackInfo info = q.front();
        q.pop();
        if (info.attacker->isAlive() && info.target->isAlive()) {
            std::cout << "[MEMPROSES SERANGAN] " << info.attacker->name << " menyerang " << info.target->name << "!" << std::endl;
            info.target->takeDamage(info.damage);
        } else {
            std::cout << "[MEMPROSES SERANGAN] Serangan dari " << info.attacker->name << " ke " << info.target->name << " dibatalkan (salah satu sudah kalah)." << std::endl;
        }
    }
}

bool AttackQueue::isEmpty() const {
    return q.empty();
}

size_t AttackQueue::size() const {
    return q.size();
}