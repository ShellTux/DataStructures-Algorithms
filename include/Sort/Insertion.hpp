#ifndef SORT_INSERTION_HPP
#define SORT_INSERTION_HPP

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
#include <cstdint>

namespace Sort {

template <typename T, std::size_t N> void Insertion(std::array<T, N>& arr) {
    for (std::size_t i = 1; i < N; ++i) {
        const T key    = arr[i];
        std::int64_t j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

}  // namespace Sort

#endif  // !SORT_INSERTION_HPP
