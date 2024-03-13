#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "BinaryTree.hpp"

template <typename T> class BinarySearchTree : public BinaryTree<T> {
   public:
    void insert(const T& value) {
        if (this->root == nullptr) {
            this->root = std::make_shared<BinaryNode<T>>(value);
            return;
        }

        auto curr = this->root;
        while (curr != nullptr) {
            if (value < curr->data) {
                if (curr->left == nullptr) {
                    curr->left = std::make_shared<BinaryNode<T>>(value);
                    return;
                }
                curr = curr->left;
            } else if (value > curr->data) {
                if (curr->right == nullptr) {
                    curr->right = std::make_shared<BinaryNode<T>>(value);
                    return;
                }
                curr = curr->right;
            } else {
#ifdef DEBUG
                std::cout << "Value already exists on the tree" << std::endl;
#endif
                return;
            }
        }
    }
    T min() {
        if (this->root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }

        auto current = this->root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    T max() {
        if (this->root == nullptr) {
            throw std::runtime_error("Tree is empty");
        }

        auto current = this->root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

   private:
    bool searchHelper(std::shared_ptr<BinaryNode<T>> node, const T& value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
};

#endif  // !BINARY_SEARCH_TREE_HPP
