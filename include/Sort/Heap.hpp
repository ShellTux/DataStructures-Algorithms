#ifndef SORT_HEAP_HPP
#define SORT_HEAP_HPP

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

// https://www.geeksforgeeks.org/heap-sort/
template <typename T, std::size_t S>
void Heapify(std::array<T, S>& array, int N, int i) {
    int largest = i;
    int l       = 2 * i + 1;
    int r       = 2 * i + 2;

    if (l < N && array[l] > array[largest]) largest = l;

    // If right child is larger than largest
    // so far
    if (r < N && array[r] > array[largest]) largest = r;

    // If largest is not root
    if (largest != i) {
        Sort::Swap(array, i, largest);
        /* swap(array[i], array[largest]); */

        // Recursively heapify the affected sub-tree
        Sort::Heapify(array, N, largest);
    }
}

template <typename T, std::size_t S>
void Heap(std::array<T, S>& array, std::size_t N = S) {
    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--) {
        Sort::Heapify(array, N, i);
    }

    // One by one extract an element from heap
    for (int i = N - 1; i > 0; i--) {
        // Move current root to end
        Sort::Swap(array, 0, i);

        // call max heapify on the reduced heap
        Sort::Heapify(array, i, 0);
    }
}

}  // namespace Sort

#endif  // !SORT_HEAP_HPP
