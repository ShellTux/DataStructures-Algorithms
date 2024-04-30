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

#include "Sort/main.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>

#include "Array/Print.hpp"
#include "Sort/Heap.hpp"
#include "Sort/Insertion.hpp"
#include "Sort/Quick.hpp"

#define LINE_SEPARATING std::cout << "----------------\n"

constexpr std::size_t SIZE           = 10;
constexpr std::size_t MAX_SIZE_PRINT = 15;
constexpr std::size_t ITERATIONS     = 5;
constexpr std::size_t RANDOM_MIN     = std::numeric_limits<std::size_t>::min();
constexpr std::size_t RANDOM_MAX     = std::numeric_limits<std::size_t>::max();

#define SIZES    \
    WRAPPER(1e3) \
    WRAPPER(5e3) \
    WRAPPER(1e4) \
    WRAPPER(5e4) \
    WRAPPER(1e5)

#define BENCHMARK 1
int main() {
#if BENCHMARK
#define WRAPPER(SIZE) \
    benchmark<std::size_t, std::size_t(SIZE)>(RANDOM_MIN, RANDOM_MAX);
    SIZES
#undef WRAPPER
#else
    const auto randomArray =
        Array::Generate::Random<std::size_t, SIZE>(1, SIZE * 100);
    auto groupA = randomArray;
    auto groupB = randomArray;
    auto groupC = randomArray;

    std::sort(groupA.begin(), groupA.end(),
              [](const size_t a, const size_t b) { return a < b; });

    std::sort(groupB.begin(), groupB.end(),
              [](const size_t a, const size_t b) { return a > b; });

    if (SIZE <= MAX_SIZE_PRINT) {
        std::cout << "Group A: ";
        Array::Print(groupA);
        std::cout << "Group B: ";
        Array::Print(groupB);
        std::cout << "Group C: ";
        Array::Print(groupC);
    }

    auto array = randomArray;

#define WRAPPER(ALGORITHM)                                               \
    {                                                                    \
        if (SIZE <= MAX_SIZE_PRINT) {                                    \
            LINE_SEPARATING;                                             \
            std::cout << "Before Sorting:" << std::endl;                 \
            Array::Print(randomArray);                                   \
        }                                                                \
        array = randomArray;                                             \
        Sort::ALGORITHM(array);                                          \
        if (SIZE <= MAX_SIZE_PRINT) {                                    \
            std::cout << "After Sorting (" #ALGORITHM "):" << std::endl; \
            Array::Print(array);                                         \
            LINE_SEPARATING;                                             \
        }                                                                \
    }
    SORTING_ALGORITHMS
#undef WRAPPER
#endif

    return 0;
}
