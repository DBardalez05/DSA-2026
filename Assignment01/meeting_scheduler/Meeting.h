#pragma once
#include <vector>

struct Meeting
{
    int start;
    int end;
};

bool hasConflictStraightforward(const std::vector<Meeting>& meetings);
bool hasConflictSorted(std::vector<Meeting> meetings);