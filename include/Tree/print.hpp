#ifndef PRINT_HPP
#define PRINT_HPP

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

#include <array>
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace Array {
template <typename T, size_t size>
void print(const std::array<T, size>& array) {
    const size_t length = array.size();
    std::cout << "[";

    for (size_t i = 0; i < length; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }

        std::cout << array[i];
    }

    std::cout << "]" << std::endl;
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

}  // namespace Array

#endif  // !PRINT_HPP
