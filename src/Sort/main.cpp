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

#include <cstddef>
#include <iostream>
#include <ostream>

#include "Array/Print.hpp"
#include "Sort/Insertion.hpp"

#define LINE_SEPARATING std::cout << "----------------\n"

#define SORTING_ALGORITHMS   \
    WRAPPER(Sort::Insertion) \
    WRAPPER(Sort::Heap)

int main() {
    const auto randomArray = Array::Generate::Random<std::size_t, 10>(1, 100);
    auto array             = randomArray;

#define WRAPPER(ALGORITHM)                                                   \
    {                                                                        \
        LINE_SEPARATING;                                                     \
        std::cout << "Before Sorting:" << std::endl;                         \
        Array::Print(randomArray);                                           \
        array = randomArray;                                                 \
        ALGORITHM(array);                                                    \
        std::cout << "After Sorting (" #ALGORITHM "):" << std::endl; \
        Array::Print(array);                                                 \
        LINE_SEPARATING;                                                     \
    }
    SORTING_ALGORITHMS
#undef WRAPPER

    return 0;
}
