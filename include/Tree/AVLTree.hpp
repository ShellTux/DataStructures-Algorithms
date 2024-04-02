#ifndef AVL_TREE
#define AVL_TREE

/***************************************************************************
 * Project                                      ___       _______  _______
 *                                             /   \     |   ____||       \
 *                                            /  ^  \    |  |__   |  .--.  |
 *                                           /  /_\  \   |   __|  |  |  |  |
 *                                          /  _____  \  |  |____ |  '--'  |
 *                                         /__/     \__\ |_______||_______/
 *
 * Author: Luís Góis
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the LICENSE file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include <memory>

#include "BinarySearchTree.hpp"
#include "Tree/BinaryNode.hpp"

template <typename T> class AVLTree : public BinarySearchTree<T> {
   public:
    void insert(const T& value) {
        this->root = insertHelper(this->root, value);
    }

   private:
    std::shared_ptr<BinaryNode<T>> rotateRight(
        std::shared_ptr<BinaryNode<T>> node) {
        this->rotation_count++;
        auto newRoot   = node->left;
        node->left     = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    std::shared_ptr<BinaryNode<T>> rotateLeft(
        std::shared_ptr<BinaryNode<T>> node) {
        this->rotation_count++;
        auto newRoot  = node->right;
        node->right   = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    std::shared_ptr<BinaryNode<T>> insertHelper(
        std::shared_ptr<BinaryNode<T>> node, const T& value) {
        if (node == nullptr) {
            return std::make_shared<BinaryNode<T>>(value);
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        } else {
            return node;
        }

        // Perform balancing after insertion
        int bf = node->balanceFactor();
        if (bf > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        if (bf < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        if (bf > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
};

#endif  // !AVL_TREE
