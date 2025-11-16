#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <random>
#include <chrono>
#include <parlay/parallel.h>
#include <parlay/primitives.h>

constexpr size_t SEQ_CUTOFF = 100'000;

template<typename T>
void sequential_quicksort(std::vector<T> &arr, size_t left, size_t right) {
    // тут смысла брать случайный нет, массив и так случайный)
    T pivot = arr[right];
    size_t i = left;

    for (size_t j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[right]);

    if (left + 1 < i) sequential_quicksort(arr, left, i - 1);
    if (i + 1 < right) sequential_quicksort(arr, i + 1, right);
}

template<typename T>
void sequential_quicksort(std::vector<T> &arr) {
    if (arr.size() <= 1) return;
    sequential_quicksort(arr, 0, arr.size() - 1);
}

template<typename T>
void parallel_quicksort(std::vector<T> &arr, size_t left, size_t right) {
    const size_t size = right - left + 1;

    if (size <= SEQ_CUTOFF) {
        sequential_quicksort(arr, left, right);
        return;
    }

    T pivot = arr[right];
    size_t i = left;

    for (size_t j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[right]);

    parlay::par_do(
        [&]() { if (left + 1 < i) parallel_quicksort(arr, left, i - 1); },
        [&]() { if (i + 1 < right) parallel_quicksort(arr, i + 1, right); }
    );
}

template<typename T>
void parallel_quicksort(std::vector<T> &arr) {
    if (arr.size() <= 1) return;
    parallel_quicksort(arr, 0, arr.size() - 1);
}

template<typename T>
std::vector<T> generate_random_array(size_t size, unsigned seed = 0) {
    std::vector<T> arr(size);
    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

    parlay::parallel_for(0, size, [&](size_t i) {
        arr[i] = dist(rng);
    });
    return arr;
}

template<typename F>
long double measure_time(F func) {
    const auto start = std::chrono::high_resolution_clock::now();
    func();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<long double>(end - start).count();
}

#endif // QUICKSORT_H
