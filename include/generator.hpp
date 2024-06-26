#ifndef GENERATOR_HPP
#define GENERATOR_HPP

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
#include <cstdlib>
#include <limits>
#include <random>
#include <unordered_set>

namespace Generate {

template <typename T, size_t size>
std::array<T, size> Keys(const double& repeated_percentage) {
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

}  // namespace Generate

#endif  // !GENERATOR_HPP
