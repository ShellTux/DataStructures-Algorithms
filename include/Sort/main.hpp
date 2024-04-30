#ifndef SORT_MAIN_HPP
#define SORT_MAIN_HPP

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

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <ratio>

#include "Array/Print.hpp"
#include "Sort/Heap.hpp"
#include "Sort/Insertion.hpp"
#include "Sort/Quick.hpp"

#define SORTING_ALGORITHMS \
    WRAPPER(Insertion)     \
    WRAPPER(Heap)          \
    WRAPPER(Quick)

enum class Algorithm {
#define WRAPPER(ALGORITHM) ALGORITHM,
    SORTING_ALGORITHMS
#undef WRAPPER
};

enum class Dataset {
    A,
    B,
    C,
};

using DataPoint = struct DataPoint {
    Algorithm algorithm;
    Dataset dataset;
    std::size_t N;
    double timeMiliseconds;

    DataPoint(Algorithm algorithm, Dataset dataset, std::size_t N = 0,
              double timeMiliseconds = 0)
        : algorithm(algorithm),
          dataset(dataset),
          N(N),
          timeMiliseconds(timeMiliseconds){};

    void print() const {}
    void printCSV() const {
        switch (algorithm) {
            case Algorithm::Insertion:
                std::cout << "Insertion";
                break;
            case Algorithm::Heap:
                std::cout << "Heap";
                break;
            case Algorithm::Quick:
                std::cout << "Quick";
                break;
        }

        std::cout << ";";

        switch (dataset) {
            case Dataset::A:
                std::cout << "A";
                break;
            case Dataset::B:
                std::cout << "B";
                break;
            case Dataset::C:
                std::cout << "C";
                break;
        }

        std::cout << ";" << N << ";" << timeMiliseconds << ";" << std::endl;
    }
};

template <typename T, const std::size_t S>
DataPoint measure(const std::array<T, S> &randomArray,
                  const Algorithm algorithm, const Dataset dataset) {
    auto datasetArray = randomArray;

    switch (dataset) {
        case Dataset::A:
            std::sort(datasetArray.begin(), datasetArray.end(),
                      [](const size_t a, const size_t b) { return a < b; });
            break;
        case Dataset::B:
            std::sort(datasetArray.begin(), datasetArray.end(),
                      [](const size_t a, const size_t b) { return a > b; });
            break;
        case Dataset::C:
            break;
    }

    using clock = std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::time_point;

    time_point start = clock::now();

    switch (algorithm) {
        case Algorithm::Insertion:
            Sort::Insertion(datasetArray);
            break;
        case Algorithm::Heap:
            Sort::Heap(datasetArray);
            break;
        case Algorithm::Quick:
            Sort::Quick(datasetArray);
            break;
    }

    time_point end = clock::now();

    duration<double, std::milli> deltaTime = end - start;

    return DataPoint(algorithm, dataset, S, deltaTime.count());
}

template <typename T, const std::size_t SIZE>
void benchmark(const std::size_t minimum, const std::size_t maximum) {
    const auto randomArray = Array::Generate::Random<T, SIZE>(minimum, maximum);

#define WRAPPER(ALGORITHM)                                             \
    measure(randomArray, Algorithm::ALGORITHM, Dataset::A).printCSV(); \
    measure(randomArray, Algorithm::ALGORITHM, Dataset::B).printCSV(); \
    measure(randomArray, Algorithm::ALGORITHM, Dataset::C).printCSV();
    SORTING_ALGORITHMS
#undef WRAPPER
}

#endif  // !SORT_MAIN_HPP
