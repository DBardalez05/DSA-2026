#pragma once
#include <vector>
#include <cstddef>
#include <optional>

std::vector<int> mergeSort(std::vector<int> temp) {

    //return if already sorted
    if (temp.size() <= 1) {
        return temp;
    }

    // Initialize vectors and first find the halfway point of input vector to see where we split
    std::size_t middle = temp.size() / 2;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> final;

    // Based on halfway split append the temp values into left or right
    for (std::size_t i = 0; i < temp.size(); i++) {
        if (i < middle) {
            left.push_back(temp[i]);
        } else {
            right.push_back(temp[i]);
        }
    }

    // Call again to split and merge
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge left and right
    std::size_t i = 0;
    std::size_t j = 0;

    // While both side of the left and right are sorted and have elements we compare first of left and first of 
    // right i ordr to take teh smallest then keep doing until no elements in either list left
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            final.push_back(left[i]);
            i++;
        } else {
            final.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        final.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        final.push_back(right[j]);
        j++;
    }
    //return final list
    return final;
}