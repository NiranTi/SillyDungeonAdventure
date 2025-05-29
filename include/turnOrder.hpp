#ifndef TURNORDER_HPP
#define TURNORDER_HPP

#include <vector>
#include "karakter.hpp"

struct TreeNode {
    Character data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Character& character)
        : data(character), left(nullptr), right(nullptr) {}
};

// Insert karakter ke BST berdasarkan speed
TreeNode* insertBySpeed(TreeNode* root, const Character& character);

// Traverse BST dari speed tertinggi ke terendah
void reverseInorder(TreeNode* root, std::vector<Character>& turnOrder);

// Delete tree setelah battle selesai
void deleteTree(TreeNode* root);

#endif
