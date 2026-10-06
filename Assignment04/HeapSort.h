#pragma once
#include <vector>
#include "MinPriorityQueue.h"

std::vector<int> heapSort(std::vector<int> temp) {
    MinPriorityQueue<int> queue;
    std::vector<int> final;

    // For each value from temp we put it into the add with priority function and since the key for each value will be same
    // the parameters is just the same thing
    for (int number : temp) {
        queue.addWithPriority(number, number);
    }
    // Keep going until the queue is empty, next sorted value will be at the start
    while (!queue.isEmpty()) {
        final.push_back(queue.next().value());
    }
    //return sorted
    return final;
}