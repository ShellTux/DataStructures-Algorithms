#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>

#include "BinarySearchTree.hpp"
#include "Tree/BinaryNode.hpp"

template <typename T> class RedBlackTree : public BinarySearchTree<T> {
   public:
    void insert(const T& value) {
        std::shared_ptr<BinaryNode<T>> newNode =
            std::make_shared<BinaryNode<T>>(value);
        newNode->color = BinaryNode<T>::Color::RED;

        this->root = insertHelper(this->root, newNode);

        // Ensure root is black
        this->root->color = BinaryNode<T>::Color::BLACK;
    }

   private:
    std::shared_ptr<BinaryNode<T>> insertHelper(
        std::shared_ptr<BinaryNode<T>> node,
        std::shared_ptr<BinaryNode<T>> newNode) {
        if (node == nullptr) {
            return newNode;
        }

        if (newNode->data < node->data) {
            node->left = insertHelper(node->left, newNode);
        } else if (newNode->data > node->data) {
            node->right = insertHelper(node->right, newNode);
        } else {
            return node;
        }

        // Fix red-red violation
        if (isRed(node->right) && !isRed(node->left)) {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        }

        return node;
    }

    bool isRed(std::shared_ptr<BinaryNode<T>> node) {
        return node != nullptr && node->is_red();
    }

    std::shared_ptr<BinaryNode<T>> rotateLeft(
        std::shared_ptr<BinaryNode<T>> node) {
        this->rotation_count++;
        auto newRoot   = node->right;
        node->right    = newRoot->left;
        newRoot->left  = node;
        newRoot->color = node->color;
        node->color    = BinaryNode<T>::Color::RED;
        return newRoot;
    }

    std::shared_ptr<BinaryNode<T>> rotateRight(
        std::shared_ptr<BinaryNode<T>> node) {
        this->rotation_count++;
        auto newRoot   = node->left;
        node->left     = newRoot->right;
        newRoot->right = node;
        newRoot->color = node->color;
        node->color    = BinaryNode<T>::Color::RED;
        return newRoot;
    }

    void flipColors(std::shared_ptr<BinaryNode<T>> node) {
        node->color        = BinaryNode<T>::Color::RED;
        node->left->color  = BinaryNode<T>::Color::BLACK;
        node->right->color = BinaryNode<T>::Color::BLACK;
    }
};

#endif  // !RED_BLACK_TREE_HPP
