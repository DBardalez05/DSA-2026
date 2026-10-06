#include "SelectionSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "RadixSort.h"
#include <vector>
#include <cassert>
#include <iostream>

//If I make one function that checks all of the sorting methods then I can simply feed the function different initial conditions
void checkSorts(std::vector<int> input, std::vector<int> expected) {
    assert(selectionSort(input) == expected);
    assert(mergeSort(input) == expected);
    assert(heapSort(input) == expected);
    assert(radixSort(input) == expected);
}

int main() {
    // All are given, a simple unsorted list 
    checkSorts({32, 15, 21, 13}, {13, 15, 21, 32});

    // Input a sorted list
    checkSorts({1, 2, 3, 4}, {1, 2, 3, 4});

    // Input a list that has both duplicates and zeros
    checkSorts({3, 1, 3, 0}, {0, 1, 3, 3});

    // Input an empty list
    checkSorts({}, {});

    std::cout << "All tests passed!\n";
    return 0;
}
