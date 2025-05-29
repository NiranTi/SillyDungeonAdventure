#include "turnOrder.hpp"
#include <iostream>

using namespace std;

TreeNode* insertBySpeed(TreeNode* root, const Character& character) {
    if (!root) return new TreeNode(character);

    if (character.speed < root->data.speed)
        root->left = insertBySpeed(root->left, character);
    else
        root->right = insertBySpeed(root->right, character);

    return root;
}

void reverseInorder(TreeNode* root, vector<Character>& turnOrder) {
    if (!root) return;

    reverseInorder(root->right, turnOrder);
    turnOrder.push_back(root->data);
    reverseInorder(root->left, turnOrder);
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

