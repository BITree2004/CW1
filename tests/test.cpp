#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/quicksort.h"

bool test_empty_array() {
    std::vector<int> arr;
    sequential_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

bool test_single_element() {
    std::vector<int> arr = {42};
    sequential_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

bool test_sorted_array() {
    std::vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    sequential_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

bool test_reverse_sorted_array() {
    std::vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    sequential_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

bool test_random_small_array() {
    std::vector<int> arr = {6, 541, 141, 1424, 14, 6, 7, 8, 3, 14, 516, 6644, 124};
    sequential_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

bool test_parallel_small() {
    std::vector<int> arr = {3, 1, 4, 1, 1, 1, 5, 9, 8, 7, 6, 2, 4, 4, 6, 5, 3, 4, 0, 0, 0, 1, 0, 5, 8, 9, 7, 9};
    parallel_quicksort(arr);
    return std::ranges::is_sorted(arr);
}

int main() {
    bool all_passed = true;

    if (!test_empty_array()) {
        std::cout << "Empty array test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Empty array test passed" << std::endl;
    }

    if (!test_single_element()) {
        std::cout << "Single element test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Single element test passed" << std::endl;
    }

    if (!test_sorted_array()) {
        std::cout << "Sorted array test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Sorted array test passed" << std::endl;
    }

    if (!test_reverse_sorted_array()) {
        std::cout << "Reverse sorted array test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Reverse sorted array test passed" << std::endl;
    }

    if (!test_random_small_array()) {
        std::cout << "Random small array test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Random small array test passed" << std::endl;
    }

    if (!test_parallel_small()) {
        std::cout << "Parallel small array test failed" << std::endl;
        all_passed = false;
    } else {
        std::cout << "Parallel small array test passed" << std::endl;
    }

    std::cout << std::endl;
    if (!all_passed) {
        std::cout << "Some tests failed!" << std::endl;
        return 1;
    }
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
