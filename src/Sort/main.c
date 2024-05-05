#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Array/Array.h"
#include "Array/Sort/Heap.h"
#include "Array/Sort/Insertion.h"
#include "Array/Sort/Measure.h"
#include "Array/Sort/Quick.h"

static const size_t SIZES[] = {
    1e4, 3e4, 5e4, 7e4, 1e5, 3e5, 5e5, 7e5, 1e6,
    3e6, 5e6, 7e6, 1e7, 3e7, 5e7, 7e7, 1e8,
};

#define MAX 1000 * 1000
#define MIN 1

int asc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int des(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

void datasetA(Array *array) {
    qsort(array->data, array->size, sizeof(*array->data), asc);
}

void datasetB(Array *array) {
    qsort(array->data, array->size, sizeof(*array->data), des);
}

void datasetC(Array *array) { (void)array; }

static const Algorithm ALGORITHMS[] = {
    (Algorithm){.function = insertionSortArray,
                .string   = "Insertion",
                .datasets =
                    {
                        {'A', datasetA, ULONG_MAX},
                        {'B', datasetB, 1e5},
                        {'C', datasetC, 1e6},
                    }},
    (Algorithm){.function = heapSortArray,
                .string   = "Heap Sort",
                .datasets =
                    {
                        {'A', datasetA, ULONG_MAX},
                        {'B', datasetB, ULONG_MAX},
                        {'C', datasetC, ULONG_MAX},
                    }},
    (Algorithm){.function = quickSortArray,
                .string   = "Quick Sort",
                .datasets =
                    {
                        {'A', datasetA, ULONG_MAX},
                        {'B', datasetB, ULONG_MAX},
                        {'C', datasetC, ULONG_MAX},
                    }},
};

#define for2(LOOP1_START, LOOP1_CONDITION, LOOP1_STEP, LOOP2_START, \
             LOOP2_CONDITION, LOOP2_STEP)                           \
    for (LOOP1_START; LOOP1_CONDITION; LOOP1_STEP)                  \
        for (LOOP2_START; LOOP2_CONDITION; LOOP2_STEP)

#define for3(LOOP1_START, LOOP1_CONDITION, LOOP1_STEP, LOOP2_START,     \
             LOOP2_CONDITION, LOOP2_STEP, LOOP3_START, LOOP3_CONDITION, \
             LOOP3_STEP)                                                \
    for (LOOP1_START; LOOP1_CONDITION; LOOP1_STEP)                      \
        for (LOOP2_START; LOOP2_CONDITION; LOOP2_STEP)                  \
            for (LOOP3_START; LOOP3_CONDITION; LOOP3_STEP)

int main(void) {
    printf("Algorithm;Dataset;Array Size;Time (ms);\n");
    for (size_t i = 0; i < sizeof(SIZES) / sizeof(*SIZES); ++i) {
        const size_t size = SIZES[i];

        const Array randomArr = randomArray(size, 0, 1e4);

        for (size_t j = 0; j < sizeof(ALGORITHMS) / sizeof(*ALGORITHMS); ++j) {
            const Algorithm algorithm = ALGORITHMS[j];

            for (size_t k = 0;
                 k < sizeof(algorithm.datasets) / sizeof(*algorithm.datasets);
                 ++k) {
                const struct Dataset dataset = algorithm.datasets[k];

                if (size > dataset.maxSize) {
                    continue;
                }

                Array array = copyArray(randomArr);
                dataset.function(&array);

                const size_t iterations = 1;
                const double cpuTimeUsed =
                    measureArray(array, algorithm.function, iterations);

                fprintf(stdout, "%s;%c;%zu;%f;\n", algorithm.string,
                        dataset.letter, size, cpuTimeUsed);
                fflush(stdout);

                destroyArray(&array);
            }
        }
    }

    return 0;
}
