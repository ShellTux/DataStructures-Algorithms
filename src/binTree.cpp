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

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "Tree/AVLTree.hpp"
#include "Tree/BinaryNode.hpp"
#include "Tree/BinarySearchTree.hpp"
#include "Tree/BinaryTree.hpp"
#include "Tree/RedBlackTree.hpp"
#include "Tree/print.hpp"
#include "generator.hpp"
#include "time.hpp"

#define BENCHMARK_KEYS 10000
#define KEYS_PER_REPORT 1000
#define VISUALIZE_KEYS 10
#define BENCHMARK_ITERATIONS 10
#define BENCHMARK_THRESHOLD_SECONDS 5 * 60

#define FLAGS                                                             \
    WRAPPER(HELP, 0, "-h", "--help", "Display this help message")         \
    WRAPPER(VERSION, 1, "-v", "--version", "Display version information") \
    WRAPPER(QUIET, 2, "-q", "--quiet", "Show less output")                \
    WRAPPER(VISUALIZE, 3, "-V", "--visualize", "Visualize Binary Trees")  \
    WRAPPER(BENCHMARK, 4, "-B", "--benchmark", "Benchmark Binary Trees")  \
    WRAPPER(CSV_FORMAT, 5, "-c", "--csv-format", "Output style in csv format")

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

    if (enabled_flags & VISUALIZE) {
        BinaryTree<int> binTree{};
        BinarySearchTree<int> binSearchTree{};
        AVLTree<int> avlTree{};
        RedBlackTree<int> redBlackTree{};

        const auto keys = Generate::Keys<int, VISUALIZE_KEYS>(0);
        Array::print(keys);

        for (const auto& key : keys) {
            binTree.insert(key);
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

#define PRINT_FORMAT_VISUALIZE(STRUCTURE_TEXT, STRUCTURE) \
    std::cout << STRUCTURE_TEXT ":" << std::endl;         \
    STRUCTURE.Dump();                                     \
    STRUCTURE.for_each(printNodeInfo);                    \
    std::cout << std::endl;

        PRINT_FORMAT_VISUALIZE("Binary Tree", binTree);
        PRINT_FORMAT_VISUALIZE("Binary Search Tree", binSearchTree);
        PRINT_FORMAT_VISUALIZE("AVL Tree", avlTree);
        PRINT_FORMAT_VISUALIZE("Red-Black Tree", redBlackTree);
    }

    if (enabled_flags & BENCHMARK) {
        std::map<const char* const, std::array<int, BENCHMARK_KEYS>>
            group_keys{};
#define WRAPPER(letter, repeated_percentage)                          \
    {                                                                 \
        std::array<int, BENCHMARK_KEYS> group##letter =               \
            Generate::Keys<int, BENCHMARK_KEYS>(repeated_percentage); \
                                                                      \
        if (std::string(#letter) == "A") {                            \
            std::sort(group##letter.begin(), group##letter.end());    \
        } else if (std::string(#letter) == "B") {                     \
            std::sort(group##letter.begin(), group##letter.end(),     \
                      std::greater<int>());                           \
        }                                                             \
                                                                      \
        if (BENCHMARK_KEYS < 100) {                                   \
            std::cout << "Group " #letter << std::endl;               \
            std::cout << group##letter << std::endl;                  \
            Array::print_repeated(group##letter);                     \
            std::cout << std::endl;                                   \
        }                                                             \
                                                                      \
        group_keys.insert(std::make_pair(#letter, group##letter));    \
    }
        LIST_GROUPS
#undef WRAPPER

        if (enabled_flags & CSV_FORMAT) {
            std::cout << "Group;Structure;Insertion Time of " << BENCHMARK_KEYS
                      << " keys (seconds);Rotations" << std::endl;
        }

        for (auto it = group_keys.begin(); it != group_keys.end(); ++it) {
            const char* const letter              = it->first;
            std::array<int, BENCHMARK_KEYS>& keys = it->second;

            BinaryTree<int> binTree{};
            BinarySearchTree<int> binSearchTree{};
            AVLTree<int> avlTree{};
            RedBlackTree<int> redBlackTree{};

            if (!(enabled_flags & QUIET)) {
                Array::print(keys);
            }

            std::chrono::duration<double> duration;

	    MEASURE_TIME(
			    binTree.insert(keys[i]),
			    i,
			    keys.size(),
			    KEYS_PER_REPORT,
			    BENCHMARK_ITERATIONS,
			    BENCHMARK_THRESHOLD_SECONDS
			);
            std::chrono::duration<double> binTreeDuration = duration;

	    MEASURE_TIME(
			    binSearchTree.insert(keys[i]),
			    i,
			    keys.size(),
			    KEYS_PER_REPORT,
			    BENCHMARK_ITERATIONS,
			    BENCHMARK_THRESHOLD_SECONDS
			);
            std::chrono::duration<double> binSearchTreeDuration = duration;

	    MEASURE_TIME(
			    avlTree.insert(keys[i]),
			    i,
			    keys.size(),
			    KEYS_PER_REPORT,
			    BENCHMARK_ITERATIONS,
			    BENCHMARK_THRESHOLD_SECONDS
			);
            std::chrono::duration<double> avlTreeDuration = duration;

	    MEASURE_TIME(
			    redBlackTree.insert(keys[i]),
			    i,
			    keys.size(),
			    KEYS_PER_REPORT,
			    BENCHMARK_ITERATIONS,
			    BENCHMARK_THRESHOLD_SECONDS
			);
            std::chrono::duration<double> redBlackTreeDuration = duration;

            if (enabled_flags & CSV_FORMAT) {
#define CSV_FORMAT_PRINT(feature, duration, structure)                \
    std::cout << letter << ";" feature ";" << duration.count() << ";" \
              << structure.rotation_count << std::endl;

                CSV_FORMAT_PRINT("BinaryTree", binTreeDuration, binTree);
                CSV_FORMAT_PRINT("BinarySearchTree", binSearchTreeDuration,
                                 binSearchTree);
                CSV_FORMAT_PRINT("AVLTree", avlTreeDuration, avlTree);
                CSV_FORMAT_PRINT("RedBlackTree", redBlackTreeDuration,
                                 redBlackTree);
            } else {
                std::cout << "Group " << letter << std::endl;
#define FORMAT_PRINT_INSERTION(structure, duration)               \
    std::cout << structure " Insertion of " << BENCHMARK_KEYS     \
              << " keys took: " << duration.count() << " seconds" \
              << std::endl;

                FORMAT_PRINT_INSERTION("Binary Tree", binTreeDuration);
                FORMAT_PRINT_INSERTION("Binary Search Tree",
                                       binSearchTreeDuration);
                FORMAT_PRINT_INSERTION("AVL Tree", avlTreeDuration);
                FORMAT_PRINT_INSERTION("Red-Black Tree", redBlackTreeDuration);

                std::cout << std::endl;

#define FORMAT_PRINT_ROTATIONS(structure, count) \
    std::cout << structure " Rotations: " << count << std::endl;

                FORMAT_PRINT_ROTATIONS("Binary Tree", binTree.rotation_count);
                FORMAT_PRINT_ROTATIONS("Binary Search Tree",
                                       binSearchTree.rotation_count);
                FORMAT_PRINT_ROTATIONS("AVL Tree", avlTree.rotation_count);
                FORMAT_PRINT_ROTATIONS("Red Black Tree",
                                       redBlackTree.rotation_count);
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
