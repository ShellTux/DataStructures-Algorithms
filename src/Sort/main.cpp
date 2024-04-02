#include <cstddef>
#include <iostream>
#include <ostream>

#include "Array/Print.hpp"
#include "Sort/Insertion.hpp"

#define LINE_SEPARATING std::cout << "----------------\n"

#define SORTING_ALGORITHMS   \
    WRAPPER(Sort::Insertion) \
    WRAPPER(Sort::Heap)

int main() {
    const auto randomArray = Array::Generate::Random<std::size_t, 10>(1, 100);
    auto array             = randomArray;

#define WRAPPER(ALGORITHM)                                                   \
    {                                                                        \
        LINE_SEPARATING;                                                     \
        std::cout << "Before Sorting:" << std::endl;                         \
        Array::Print(randomArray);                                           \
        array = randomArray;                                                 \
        ALGORITHM(array);                                                    \
        std::cout << "After Sorting (" #ALGORITHM "):" << std::endl; \
        Array::Print(array);                                                 \
        LINE_SEPARATING;                                                     \
    }
    SORTING_ALGORITHMS
#undef WRAPPER

    return 0;
}
