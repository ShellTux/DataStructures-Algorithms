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

#include "Array/Array.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/error.h"

Array createArray(const size_t size) {
    Array array = {
        .size = size,
        .data = malloc(sizeof(*array.data) * size),
    };

    if (array.data == NULL) {
        HANDLE_ERROR("malloc: ");
    }

    return array;
}

Array copyArray(const Array array) {
    Array clone = array;

    clone.data = memcpy(malloc(sizeof(*clone.data) * clone.size), array.data,
                        array.size * sizeof(*array.data));

    return clone;
}

void destroyArray(Array *array) {
    if (array == NULL || array->data == NULL || array->size == 0) {
        return;
    }

    free(array->data);
    *array = (Array){0};
}

void printArray(FILE *file, const Array array, const bool printData) {
    fprintf(file, ARRAY_FORMAT_PRINT "\n", array.size);

    if (printData) {
        fprintf(file, "[");
        for (size_t i = 0; i < array.size; ++i) {
            if (i > 0) {
                fprintf(file, ARRAY_DATA_SEPARATOR);
            }

            fprintf(file, ARRAY_DATA_FORMAT, array.data[i]);
        }
        fprintf(file, "]\n");
    }
}

Array randomArray(const size_t size, const ARRAY_DATA_TYPE min,
                  const ARRAY_DATA_TYPE max) {
    Array array = createArray(size);

    randomizeArray(&array, min, max);

    return array;
}

void randomizeArray(Array *array, const ARRAY_DATA_TYPE min,
                    const ARRAY_DATA_TYPE max) {
    if (array == NULL) {
        return;
    }

    for (size_t i = 0; i < array->size; ++i) {
        array->data[i] = rand() % (max - min) + min;
    }
}

void swapArray(Array *array, const size_t i, const size_t j) {
    swap(&array->data[i], &array->data[j]);
}

void swap(ARRAY_DATA_TYPE *a, ARRAY_DATA_TYPE *b) {
    ARRAY_DATA_TYPE temp = *a;
    *a                   = *b;
    *b                   = temp;
}
