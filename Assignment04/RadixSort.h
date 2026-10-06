#pragma once
#include <vector>

std::vector<int> radixSort(std::vector<int> temp) {
    // First we find what the biggest number is to see what position we start from
    int biggest = 0;
    for (int number : temp) {
        if (number > biggest) {
            biggest = number;
        }
    }

    // We start in the ones place then 10 then 100s and so on depending on what the biggest value in the temp list is
    for (long long place = 1; biggest / place > 0; place *= 10) { //just learned tha long long used to tolerate massive numbers
        // Make 10 bins so 0-9 that represent a number in whatever place we working in atm
        std::vector<int> bins[10];
        for (int number : temp) {
            // First run through it will sort by ones
            // Second will sort by tens but the ones will be already sorted
            int digit = (number / place) % 10;
            bins[digit].push_back(number);
        }
        //clear temp to input new order
        temp.clear();
        for (int digit = 0; digit < 10; digit++) {
            for (int number : bins[digit]) {
                temp.push_back(number);
            }
        }
    }

    return temp;
}