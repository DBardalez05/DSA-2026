#include "SelectionSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "RadixSort.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <cstdlib>
#include <iostream>

int main() {
    // Use random numbers when doing these runs
    std::srand(42);
    std::vector<int> sizes = {10, 100, 1000, 10000};
    int trials = 5;

    std::cout << "| Size | Selection (ms) | Merge (ms) | Heap (ms) | Radix (ms) |\n";
    std::cout << "|---:|---:|---:|---:|---:|\n";

    // Try for each input size
    for (int size : sizes) {
        double selectionTime = 0.0;
        double mergeTime = 0.0;
        double heapTime = 0.0;
        double radixTime = 0.0;

        // Repeat five times so we can calculate an average
        for (int trial = 0; trial < trials; trial++) {
            std::vector<int> input;

            // create random numbers from 0-999
            for (int i = 0; i < size; i++) {
                input.push_back(std::rand() % 1000);
            }

            // Make a correct answer to check against, outside the timer.
            auto expected = input;
            std::sort(expected.begin(), expected.end()); // sort all
            std::vector<int> result;

            //for each it has a start and stop timer and elapsed time
            // Selection sort
            auto start = std::chrono::steady_clock::now();
            result = selectionSort(input);
            auto end = std::chrono::steady_clock::now();
            selectionTime += std::chrono::duration<double, std::milli>(end - start).count();
            assert(result == expected);

            // Merge sort.
            start = std::chrono::steady_clock::now();
            result = mergeSort(input);
            end = std::chrono::steady_clock::now();
            mergeTime += std::chrono::duration<double, std::milli>(end - start).count();
            assert(result == expected);

            // Heap sort.
            start = std::chrono::steady_clock::now();
            result = heapSort(input);
            end = std::chrono::steady_clock::now();
            heapTime += std::chrono::duration<double, std::milli>(end - start).count();
            assert(result == expected);

            // Radix sort.
            start = std::chrono::steady_clock::now();
            result = radixSort(input);
            end = std::chrono::steady_clock::now();
            radixTime += std::chrono::duration<double, std::milli>(end - start).count();
            assert(result == expected);
        }

        // Divide each total by five and print the averages in milliseconds.
        std::cout << "| " << size << " | "
                  << selectionTime / trials << " | "
                  << mergeTime / trials << " | "
                  << heapTime / trials << " | "
                  << radixTime / trials << " |\n";
    }

    return 0;
}
