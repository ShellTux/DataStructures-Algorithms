#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <ostream>
#include <random>
#include <unordered_set>

#include "Tree/AVLTree.hpp"
#include "Tree/BinaryNode.hpp"
#include "Tree/BinarySearchTree.hpp"
#include "Tree/RedBlackTree.hpp"

/* #define CHAVES 1000000 */
#define CHAVES 20

template <typename T, size_t size>
std::array<T, size> generate_keys(const double& repeated_percentage) {
    std::unordered_set<T> included{};
    std::array<T, size> array{};
    size_t repeatedCount = size * repeated_percentage;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distrib(0, std::numeric_limits<T>::max());

    for (size_t i = 0; i < size - repeatedCount; i++) {
        T num;
        do {
            num = distrib(gen);
        } while (included.count(num) > 0);

        array[i] = num;
        included.insert(num);
    }

    for (size_t i = size - repeatedCount; i < size; i++) {
        T num    = array[std::rand() % (size - repeatedCount)];
        array[i] = num;
    }

    return array;
}

template <typename T, size_t N>
void print_repeated(const std::array<T, N>& array) {
    size_t repeatedCount = 0;
    std::unordered_set<T> included{};

    for (const auto& element : array) {
        if (included.count(element) == 0) {
            included.insert(element);
            continue;
        }

        ++repeatedCount;
    }

    std::cout << "Array size: " << array.size() << std::endl;
    std::cout << "Array Repeated: " << repeatedCount << std::endl;
    std::cout << "Array Repeated (%): " << (double)repeatedCount / array.size()
              << std::endl;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#define LIST_GROUPS \
    WRAPPER(A, 0.1) \
    WRAPPER(B, 0.1) \
    WRAPPER(C, 0.1) \
    WRAPPER(D, 0.9)

int main() {
#define WRAPPER(letter, repeated_percentage)                       \
    {                                                              \
        std::array<int, CHAVES> group##letter =                    \
            generate_keys<int, CHAVES>(repeated_percentage);       \
                                                                   \
        if (std::string(#letter) == "A") {                         \
            std::sort(group##letter.begin(), group##letter.end()); \
        } else if (std::string(#letter) == "B") {                  \
            std::sort(group##letter.begin(), group##letter.end(),  \
                      std::greater<int>());                        \
        }                                                          \
                                                                   \
        std::cout << "Group " #letter << std::endl;                \
        if (CHAVES < 100) {                                        \
            std::cout << group##letter << std::endl;               \
        }                                                          \
        print_repeated(group##letter);                             \
        std::cout << std::endl;                                    \
    }
#ifdef DEBUG
    LIST_GROUPS
#endif
#undef WRAPPER

    srand(10);
    BinarySearchTree<int> binSearchTree{};
    AVLTree<int> avlTree{};
    RedBlackTree<int> redBlackTree{};

    constexpr const int AMOUNT  = 10;
    constexpr const int MAXIMUM = 30;
    for (int i = 0; i < AMOUNT; i++) {
        const int value = rand() % MAXIMUM;
        std::cout << value;
        if (i < AMOUNT - 1) {
            std::cout << ", ";
        }
        binSearchTree.insert(value);
        avlTree.insert(value);
        redBlackTree.insert(value);
    }
    std::cout << std::endl;

    const auto printNodeInfo =
        [](const std::shared_ptr<BinaryNode<int>> element) {
            std::cout << "Element " << element->data
                      << ", Height: " << element->height()
                      << ", Size: " << element->size() << std::endl;
        };

    std::cout << "Binary Search Tree:" << std::endl;
    binSearchTree.Dump();
    binSearchTree.for_each(printNodeInfo);
    std::cout << std::endl;

    std::cout << "AVL Tree:" << std::endl;
    avlTree.Dump();
    avlTree.for_each(printNodeInfo);
    std::cout << std::endl;

    std::cout << "Red-Black Tree:" << std::endl;
    redBlackTree.Dump();
    redBlackTree.for_each(printNodeInfo);
    std::cout << std::endl;

    return 0;
}
