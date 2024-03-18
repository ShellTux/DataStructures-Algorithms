#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "Tree/AVLTree.hpp"
#include "Tree/BinaryNode.hpp"
#include "Tree/BinarySearchTree.hpp"
#include "Tree/RedBlackTree.hpp"
#include "Tree/print.hpp"
#include "generator.hpp"
#include "time.hpp"

#define BENCHMARK_KEYS 10000
#define VISUALIZE_KEYS 10

#define FLAGS                                                             \
    WRAPPER(HELP, 0, "-h", "--help", "Display this help message")         \
    WRAPPER(VERSION, 1, "-v", "--version", "Display version information") \
    WRAPPER(VISUALIZE, 2, "-V", "--visualize", "Visualize Binary Trees")  \
    WRAPPER(BENCHMARK, 3, "-B", "--benchmark", "Benchmark Binary Trees")

typedef enum {
#define WRAPPER(enum, bit_shift, short, long, description) \
    enum = 1 << bit_shift,
    FLAGS
#undef WRAPPER
} Flag;

void usage(const std::string& program_name) {
    using std::cout;
    using std::endl;

    cout << "Usage: " << program_name << " [options]" << endl;
    cout << "Options:" << endl;
#define WRAPPER(enum, bit_shift, short, long, description) \
    cout << "  " short ", " long "\t\t" description << endl;
    FLAGS
#undef WRAPPER

    exit(EXIT_FAILURE);
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

int main(int argc, char** argv) {
    size_t enabled_flags = 0;
    for (int i = 0; i < argc; ++i) {
        const char* const argument = argv[i];
#define WRAPPER(enum, bit_shift, short, long, description) \
    if (strncmp(argument, short, sizeof(short)) == 0 ||    \
        strncmp(argument, long, sizeof(long)) == 0) {      \
        enabled_flags |= enum;                             \
    }
        FLAGS
#undef WRAPPER
    }

    if (enabled_flags & HELP) {
        usage(argv[0]);
    }

#define WRAPPER(letter, repeated_percentage)                          \
    {                                                                 \
        std::array<int, VISUALIZE_KEYS> group##letter =               \
            Generate::Keys<int, VISUALIZE_KEYS>(repeated_percentage); \
                                                                      \
        if (std::string(#letter) == "A") {                            \
            std::sort(group##letter.begin(), group##letter.end());    \
        } else if (std::string(#letter) == "B") {                     \
            std::sort(group##letter.begin(), group##letter.end(),     \
                      std::greater<int>());                           \
        }                                                             \
                                                                      \
        std::cout << "Group " #letter << std::endl;                   \
        if (VISUALIZE_KEYS < 100) {                                   \
            std::cout << group##letter << std::endl;                  \
        }                                                             \
        Array::print_repeated(group##letter);                         \
        std::cout << std::endl;                                       \
    }
#ifdef DEBUG
    LIST_GROUPS
#endif
#undef WRAPPER

    if (enabled_flags & VISUALIZE) {
        BinarySearchTree<int> binSearchTree{};
        AVLTree<int> avlTree{};
        RedBlackTree<int> redBlackTree{};

        const auto keys = Generate::Keys<int, VISUALIZE_KEYS>(0);
        Array::print(keys);

        for (const auto& key : keys) {
            binSearchTree.insert(key);
            avlTree.insert(key);
            redBlackTree.insert(key);
        }

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
    }

    if (enabled_flags & BENCHMARK) {
        BinarySearchTree<int> binSearchTree{};
        AVLTree<int> avlTree{};
        RedBlackTree<int> redBlackTree{};

        const auto keys = Generate::Keys<int, BENCHMARK_KEYS>(0);
        Array::print(keys);

        std::chrono::duration<double> duration;

        MEASURE_TIME(for (const auto& key
                          : keys) { binSearchTree.insert(key); }

        );
        std::cout << "Binary Search Tree Insertion of " << BENCHMARK_KEYS
                  << " keys took: " << duration.count() << " seconds"
                  << std::endl;

        MEASURE_TIME(for (const auto& key
                          : keys) { avlTree.insert(key); }

        );
        std::cout << "AVL Tree Insertion of " << BENCHMARK_KEYS
                  << " keys took: " << duration.count() << " seconds"
                  << std::endl;

        MEASURE_TIME(for (const auto& key
                          : keys) { redBlackTree.insert(key); }

        );
        std::cout << "Red-Black Tree Insertion of " << BENCHMARK_KEYS
                  << " keys took: " << duration.count() << " seconds"
                  << std::endl;

        std::cout << std::endl;
        std::cout << "Binary Search Tree Rotations: "
                  << binSearchTree.rotation_count << std::endl;
        std::cout << "AVL Tree Rotations:           " << avlTree.rotation_count
                  << std::endl;
        std::cout << "Red Black Tree Rotations:     "
                  << redBlackTree.rotation_count << std::endl;
    }

    return 0;
}
