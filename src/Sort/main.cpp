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
#include <cstddef>
#include <iostream>
#include <ostream>

#include "Array/Print.hpp"
#include "Sort/Heap.hpp"
#include "Sort/Insertion.hpp"
#include "Sort/Quick.hpp"

#define LINE_SEPARATING std::cout << "----------------\n"

#define SORTING_ALGORITHMS   \
    WRAPPER(Sort::Insertion) \
    WRAPPER(Sort::Heap)      \
    WRAPPER(Sort::Quick)

constexpr std::size_t SIZE = 100;

int main() {
    const auto randomArray =
        Array::Generate::Random<std::size_t, SIZE>(1, SIZE * 100);
    auto groupA = randomArray;
    auto groupB = randomArray;
    auto groupC = randomArray;

    std::sort(groupA.begin(), groupA.end(),
              [](const size_t a, const size_t b) { return a < b; });

    std::sort(groupB.begin(), groupB.end(),
              [](const size_t a, const size_t b) { return a > b; });

    std::cout << "Group A: ";
    Array::Print(groupA);
    std::cout << "Group B: ";
    Array::Print(groupB);
    std::cout << "Group C: ";
    Array::Print(groupC);

    auto array = randomArray;

#define WRAPPER(ALGORITHM)                                           \
    {                                                                \
        LINE_SEPARATING;                                             \
        std::cout << "Before Sorting:" << std::endl;                 \
        Array::Print(randomArray);                                   \
        array = randomArray;                                         \
        ALGORITHM(array);                                            \
        std::cout << "After Sorting (" #ALGORITHM "):" << std::endl; \
        Array::Print(array);                                         \
        LINE_SEPARATING;                                             \
    }
    SORTING_ALGORITHMS
#undef WRAPPER

    return 0;
}
