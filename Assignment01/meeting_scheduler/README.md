# Meeting Scheduler

## Overview

This program for assignment 1 determines whether any meetings in a schedule overlap. Each meeting is represented by a `Meeting` struct containing a start time and an end time. Times for each meeting are stored as the number of minutes after midnight. For example, 10:30 AM is stored as `630`. Based on the assignment, a meeting ending exactly when another meeting starts would not count as a conflict.

## Implementations

### Unsorted approach

The straightforward implementation does not assume that the meetings are sorted. It uses two nested loops to compare every unique pair of meetings. Its worst-case runtime is Θ(n²) since each meeting is compared to every meeting tat coms after it.

### Sorted approach

The second implementation uses the built-in C++ `std::sort` function to arrange the meetings by starting time. It then uses one loop to compare neighboring meetings. Sorting takes Θ(n log n), since it sorts the meetings then checks it once.


## Files

* `Meeting.h`: Contains the `Meeting` struct and function declarations.
* `Meeting.cpp`: Contains both conflict-detection implementations.
* `main.cpp`: Creates an example schedule and displays the result from both implementations.
* `tests.cpp`: Contains unit tests for scheduler.

## Unit Tests

The tests cover:

* Two overlapping meetings
* Two non-overlapping meetings
* Meetings that touch exactly at their endpoints
* One meeting completely contained inside another
* Meetings with identical times
* A schedule containing one meeting
* An empty schedule
* Meetings provided in an unsorted order

Both implementations are tested with the same inputs and expected results.

## Building and Running

Compile and run the main file where we have a test schedule:

```powershell
g++ main.cpp Meeting.cpp -o meeting.exe
.\meeting.exe
```

Compile and run the unit tests:

```powershell
g++ tests.cpp Meeting.cpp -o tests.exe
.\tests.exe
```

If every assertion succeeds, the test program displays:

```text
All tests passed!
```
