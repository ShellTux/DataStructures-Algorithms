#ifndef SORT_QUICK_HPP
#define SORT_QUICK_HPP

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

#include "Sort/Swap.hpp"

namespace Sort {

template <typename T, std::size_t N>
int partition(std::array<T, N>& array, const int lowest_index,
              const int highest_index) {
    const std::size_t pivot = array[highest_index];

    // Index of smaller element and Indicate
    // the right position of pivot found so far
    std::size_t i = lowest_index - 1;

    for (int j = lowest_index; j <= highest_index; j++) {
        // If current element is smaller than the pivot
        if (array[j] < pivot) {
            // Increment index of smaller element
            i++;
            Sort::Swap(array, i, j);
        }
    }

    Sort::Swap(array, i + 1, highest_index);
    return i + 1;
}

template <typename T, std::size_t N>
void Quick(std::array<T, N>& array, const std::size_t lowest_index = 0,
           const std::size_t highest_index = N) {
    if (N == 0 || N == 1) {
        return;
    }

    if (lowest_index < highest_index) {
        // pi is the partition return index of pivot

        /* const std::size_t pivot_index = 0.5 * (lowest_index + highest_index);
         */

        int partition_index =
            Sort::partition(array, lowest_index, highest_index);

        // Recursion Call
        // smaller element than pivot goes left and
        // higher element goes right
	Sort::Quick(array, lowest_index, partition_index - 1);
	Sort::Quick(array, partition_index + 1, highest_index);
    }
}

}  // namespace Sort

#endif  // !SORT_QUICK_HPP
