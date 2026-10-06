#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>

std::vector<int> selectionSort(std::vector<int> temp){
    std::vector<int> final = {};
    int high  = {};
    int loc = {};
    // Initial check since vector with 0 or 1 elements is already sorted
    if (temp.size() <=  1){
        return temp;
    }

    while (!temp.empty()) {
        // Set first num of unsorted list as temporaary highest
        high = temp[0];
        loc = 0;
        //look throuhg list for smaller number and save location
        for(size_t i = 0; i < temp.size(); i++){
            if (temp[i] < high ){
                high = temp[i];
                loc = i;
            }   
        }
        // Append smallest value to final vector and delete it from unsorted list
        final.push_back(temp[loc]);
        temp.erase(temp.begin() + loc);
    }
    return final;

}