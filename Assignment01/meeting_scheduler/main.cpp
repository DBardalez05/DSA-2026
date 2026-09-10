#include <iostream>    
#include "Meeting.h"

int main()
{
    const std::vector<Meeting> meetings{ //meeting times are written in minutes not hours
        {540, 600}, // 9:00–10:00
        {600, 630}, // 9:30–10:30
        {660, 720}, // 11:00–12:00
        {720, 780}  // 12:00–1:00
    };

    std::cout << std::boolalpha;

    std::cout << "Straightforward: " << hasConflictStraightforward(meetings) << '\n';

    std::cout << "Sorted: " << hasConflictSorted(meetings) << '\n';

    return 0;
}