#ifndef AED_ARRAY_ARRAY_H
#define AED_ARRAY_ARRAY_H

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

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifndef ARRAY_DATA_TYPE
#define ARRAY_DATA_TYPE int
#endif
#define ARRAY_DATA_FORMAT "%d"
#define ARRAY_DATA_SEPARATOR ", "
#define ARRAY_FORMAT_PRINT \
    "Array {\n"            \
    "  size: %zu\n"        \
    "}"

typedef struct {
    size_t size;
    ARRAY_DATA_TYPE *data;
} Array;

Array createArray(const size_t size);
Array copyArray(const Array array);
void destroyArray(Array *array);
void printArray(FILE *file, const Array array, const bool printData);
Array randomArray(const size_t size, const ARRAY_DATA_TYPE min,
                  const ARRAY_DATA_TYPE max);
void randomizeArray(Array *array, const ARRAY_DATA_TYPE min,
                    const ARRAY_DATA_TYPE max);
void swapArray(Array *array, const size_t i, const size_t j);
void swap(ARRAY_DATA_TYPE *a, ARRAY_DATA_TYPE *b);

#endif  // !AED_ARRAY_ARRAY_H
