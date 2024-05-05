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

#include "Array/Sort/Insertion.h"

#include "Array/Array.h"

void insertionSortArray(Array *array) {
    for (size_t i = 1; i < array->size; ++i) {
        const ARRAY_DATA_TYPE key = array->data[i];

        int j = i - 1;

        while (j >= 0 && array->data[j] > key) {
            array->data[j + 1] = array->data[j];
            --j;
        }

        array->data[j + 1] = key;
    }
}
