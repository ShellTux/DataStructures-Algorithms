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

#include "Array/Sort/Heap.h"

#include "Array/Array.h"

void heapSortArray(Array *array) {
    for (int i = array->size / 2 - 1; i >= 0; i--) {
        heapify(array->data, array->size, i);
    }

    for (int i = array->size - 1; i > 0; i--) {
        swapArray(array, 0, i);

        heapify(array->data, i, 0);
    }
}

void heapify(ARRAY_DATA_TYPE array[], int size, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&array[i], &array[largest]);

        heapify(array, size, largest);
    }
}
