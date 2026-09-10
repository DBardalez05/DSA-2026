#include "Meeting.h"
#include <iostream>
#include <algorithm>

bool startsEarlier(const Meeting& first, const Meeting& second)
{
    return first.start < second.start;
}

bool hasConflictStraightforward(const std::vector<Meeting>& meetings)
{
    int start_time = {};
    int end_time = {};
    int start_compare = {};
    int end_compare = {};
    
    for (int i = 0; i < meetings.size(); i++)
    {   
        start_time = meetings[i].start;
        end_time = meetings[i].end;
        for (int y = i+1; y < meetings.size(); y++)
        {
            start_compare = meetings[y].start;
            end_compare =  meetings[y].end;
            if((start_time < end_compare && end_time > start_compare))
            {
                return true;
            }
        }


    }

    return false;
}

bool hasConflictSorted(std::vector<Meeting> meetings)
{
    std::sort(meetings.begin(), meetings.end(), startsEarlier);
    for (int i = 1; i < meetings.size(); i++)
    {
        if (meetings[i].start < meetings[i-1].end)
        {
            return true;
        }
    }
    return false;
}
