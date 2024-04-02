#ifndef SORT_INSERTION_HPP
#define SORT_INSERTION_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>

namespace Sort {

template <typename T, std::size_t N> void Insertion(std::array<T, N>& arr) {
    for (std::size_t i = 1; i < N; ++i) {
        T key         = arr[i];
	std::int64_t j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

template <typename T, std::size_t N> void Heap(std::array<T, N>& array) {
    std::make_heap(array.begin(), array.end());
    std::sort_heap(array.begin(), array.end());
}

template <typename T, std::size_t N>
void Quick(std::array<T, N>& arr, const int low, const int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

template <typename T, std::size_t N>
int partition(std::array<T, N>& arr, const int low, const int high) {
    T pivot = arr[high];
    int i   = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);

    return i + 1;
}

}  // namespace Sort

#endif  // !SORT_INSERTION_HPP
