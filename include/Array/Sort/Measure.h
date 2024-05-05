#ifndef AED_ARRAY_SORT_MEASURE_H
#define AED_ARRAY_SORT_MEASURE_H

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

typedef void (*AlgorithmFunction)(Array *array);
typedef void (*DatasetFunction)(Array *array);

typedef struct {
    AlgorithmFunction function;
    char *string;
    struct Dataset {
        char letter;
        DatasetFunction function;
        size_t maxSize;
    } datasets[3];
} Algorithm;

double measureArray(Array array, AlgorithmFunction algorithm,
                    const size_t iterations);

#endif  // !AED_ARRAY_SORT_MEASURE_H
