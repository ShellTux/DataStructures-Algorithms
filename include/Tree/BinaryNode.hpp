#ifndef BINARY_NODE_HPP
#define BINARY_NODE_HPP

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>

template <typename T> class BinaryNode {
   public:
    enum class Color { NONE, RED, BLACK };
    T data;
    std::shared_ptr<BinaryNode<T>> left;
    std::shared_ptr<BinaryNode<T>> right;
    Color color{Color::NONE};

    explicit BinaryNode(const T& value)
        : data(value), left(nullptr), right(nullptr) {}

    bool is_leaf() const { return left == nullptr && right == nullptr; };
    bool is_red() const { return color == Color::RED; };
    bool is_black() const { return color == Color::BLACK; };
    static size_t height(const BinaryNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        const BinaryNode<T>* left  = node->left.get();
        const BinaryNode<T>* right = node->right.get();

        return 1 + std::max(height(left), height(right));
    }
    size_t height() const { return BinaryNode<T>::height(this); }
    static size_t size(const BinaryNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        const BinaryNode<T>* left  = node->left.get();
        const BinaryNode<T>* right = node->right.get();

        return 1 + size(left) + size(right);
    }
    size_t size() const { return BinaryNode<T>::size(this); };
    void print_data() const {
        if (color == Color::RED) {
            std::cout << "\e[41m\e[30m";
        } else if (color == Color::BLACK) {
            std::cout << "\e[41m\e[30m";
        }

        std::cout << data << "\e[0m";
    }
    void print_order(std::shared_ptr<BinaryNode<T>> node) const {
        if (node == nullptr) {
            return;
        }

        print_order(node->left);
        std::cout << node->data << std::endl;
        print_order(node->right);
    };
    void print_preorder(std::shared_ptr<BinaryNode<T>> node) const {
        if (node == nullptr) {
            return;
        }

        std::cout << node->data << std::endl;
        print_preorder(node->left);
        print_preorder(node->right);
    };
    void print_postorder(std::shared_ptr<BinaryNode<T>> node) const {
        if (node == nullptr) {
            return;
        }

        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << node->data << std::endl;
    };
    void print_order() const { print_order(this); };
    void print_preorder() const { print_preorder(this); };
    void print_postorder() const { print_postorder(this); };
    static int balanceFactor(const BinaryNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left.get()) - height(node->right.get());
    }
    int balanceFactor() const { return BinaryNode<T>::balanceFactor(this); }
};

#endif  // !BINARY_NODE_HPP
