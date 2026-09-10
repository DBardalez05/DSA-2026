#include "Meeting.h"
#include <cassert>
#include <iostream>

void testBasicOverlap()//one overlap tested should return true
{
    const std::vector<Meeting> meetings{
        {540, 600},
        {570, 630}
    };

    assert(hasConflictStraightforward(meetings) == true);
    assert(hasConflictSorted(meetings) == true);
}

void testNoOverlap()//Simple no overlap test should return false
{
    const std::vector<Meeting> meetings{
        {540, 600},
        {660, 720}
    };

    assert(hasConflictStraightforward(meetings) == false);
    assert(hasConflictSorted(meetings) == false);
}

void testTouchingEndpoints()//testing if meeting that start at teh end of another are considered overlap(should return false)
{
    const std::vector<Meeting> meetings{
        {540, 600},
        {600, 660}
    };

    assert(hasConflictStraightforward(meetings) == false);
    assert(hasConflictSorted(meetings) == false);
}

void testContainedMeeting()//Test if one meeting is fully insode the meeting time of another(expected: return true)
{
    const std::vector<Meeting> meetings{
        {540, 720},
        {600, 660}
    };

    assert(hasConflictStraightforward(meetings) == true);
    assert(hasConflictSorted(meetings) == true);
}

void testIdenticalTimes()//Testing if two meetings with same start and end time over lap(expected: return true)
{
    const std::vector<Meeting> meetings{
        {540, 600},
        {540, 600}
    };

    assert(hasConflictStraightforward(meetings) == true);
    assert(hasConflictSorted(meetings) == true);
}

void testSingleMeeting()// Testing if the function is given only one meeting (expected: return false)
{
    const std::vector<Meeting> meetings{
        {540, 600}
    };

    assert(hasConflictStraightforward(meetings) == false);
    assert(hasConflictSorted(meetings) == false);
}

void testEmptyVector()// Testing when function is given no meetings in the vector (should return false)
{
    const std::vector<Meeting> meetings{};

    assert(hasConflictStraightforward(meetings) == false);
    assert(hasConflictSorted(meetings) == false);
}

void testUnsortedMeetings() // Testing if the unsorted vector method works
{
    const std::vector<Meeting> meetings{
        {720, 780},
        {570, 630},
        {540, 600}
    };

    assert(hasConflictStraightforward(meetings) == true);
    assert(hasConflictSorted(meetings) == true);
}

int main()
{
    testBasicOverlap();
    testNoOverlap();
    testTouchingEndpoints();
    testContainedMeeting();
    testIdenticalTimes();
    testSingleMeeting();
    testEmptyVector();
    testUnsortedMeetings();

    std::cout << "All tests passed!\n";
    return 0;
}