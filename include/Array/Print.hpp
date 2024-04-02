#ifndef ARRAY_PRINT_HPP
#define ARRAY_PRINT_HPP

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
#include <random>
namespace Array {

template <typename T, std::size_t N> void Print(const std::array<T, N>& array) {
    using std::cout;
    using std::endl;

    cout << "[";

    for (size_t i = 0; i < N; ++i) {
        if (i > 0) {
            cout << ", ";
        }

        cout << array[i];
    }

    cout << "]" << endl;
}

namespace Generate {

template <typename T, size_t N>
std::array<T, N> Random(const T minValue, const T maxValue) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(minValue, maxValue);

    std::array<T, N> arr;

    for (size_t i = 0; i < N; i++) {
        arr[i] = dist(gen);
    }

    return arr;
}

}  // namespace Generate

}  // namespace Array

#endif  // !ARRAY_PRINT_HPP
