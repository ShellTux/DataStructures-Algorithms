#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

static const Algorithm ALGORITHMS[] = {
    (Algorithm){
        .function = insertionSortArray,
        .string   = "Insertion",
        .maxSize  = 1e5,
    },
    (Algorithm){
        .function = heapSortArray,
        .string   = "Heap Sort",
        .maxSize  = ULONG_MAX,
    },
    (Algorithm){
        .function = quickSortArray,
        .string   = "Quick Sort",
        .maxSize  = ULONG_MAX,
    },
};

int asc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int des(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

void datasetA(Array *array) {
    qsort(array->data, array->size, sizeof(*array->data), asc);
}

void datasetB(Array *array) {
    qsort(array->data, array->size, sizeof(*array->data), des);
}

void datasetC(Array *array) { (void)array; }

typedef void (*datasetFunction)(Array *array);

static datasetFunction DATASETS[] = {
    datasetA,
    datasetB,
    datasetC,
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
        for (size_t j = 0; j < sizeof(DATASETS) / sizeof(*DATASETS); ++j) {
            const datasetFunction dataset = DATASETS[j];

            Array array;

            for (size_t k = 0; k < sizeof(ALGORITHMS) / sizeof(*ALGORITHMS);
                 ++k) {
                const AlgorithmFunction algorithm = ALGORITHMS[k].function;
                const char *const algorithmString = ALGORITHMS[k].string;

                if (size > ALGORITHMS[k].maxSize) {
                    continue;
                }

                array = copyArray(randomArr);
                dataset(&array);

                const size_t iterations = 1;
                const double cpuTimeUsed =
                    measureArray(array, algorithm, iterations);
                fprintf(
                    stderr,
                    "Time taken to sort an array of %zu keys %zu times by %s: "
                    "%02.02f "
                    "miliseconds\n",
                    size, iterations, algorithmString, cpuTimeUsed);
                const char datasetString = j == 0 ? 'A' : j == 1 ? 'B' : 'C';
                printf("%s;%c;%zu;%f;\n", ALGORITHMS[k].string, datasetString,
                       size, cpuTimeUsed);
                fflush(stdout);

                destroyArray(&array);
            }
        }
    }

    return 0;
}
