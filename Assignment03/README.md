# Assignment 03: Graphs and Dijkstra

## Overview

This assignment implements a weighted directed graph, a minimum priority queue, and Dijkstra's shortest-path algorithm in C++. The example finds routes between cities using fake travel costs.

## Files

- `Graph.h`: Stores vertices and weighted edges.
- `MinPriorityQueue.h`: Uses a heap to remove the element with the lowest priority.
- `Dijkstra.h`: Returns a shortest path, or `std::nullopt` when no route exists.
- `main.cpp`: Demonstrates shortest routes between cities.
- `tests.cpp`: Checks basic graph, queue, and shortest-path operations.

## Building and Running

Run these commands from the `Assignment03` folder:

To run the city test implementation example:

```powershell
g++ -std=c++17 -Wall -Wextra -I. main.cpp -o main.exe
.\main.exe
```

To run the tests:

```powershell
g++ -std=c++17 -Wall -Wextra -I. tests.cpp -o tests.exe
.\tests.exe
```

Successful tests print `All tests passed!`.