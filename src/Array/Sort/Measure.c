#include "Array/Sort/Measure.h"

#include <bits/types.h>
#include <stddef.h>
#include <time.h>

#include "Array/Array.h"

double measureArray(Array array, AlgorithmFunction algorithm,
                    const size_t iterations) {
    if (algorithm == NULL) {
        return 0;
    }

    clock_t delta = 0;

    for (size_t i = 0; i < iterations; ++i) {
        const clock_t start = clock();
        algorithm(&array);
        delta += clock() - start;
    }

    return ((double)(delta) / (double)CLOCKS_PER_SEC) * 1000;
}
