# Assignment 04: Sorting Algorithms

I implemented selection sort, merge sort, heap sort, and radix sort in C++. Each function takes a vector of integers and returns it sorted from smallest to largest. Radix sort works with nonnegative integers.

## Files

- `SelectionSort.h`, `MergeSort.h`, `HeapSort.h`, `RadixSort.h`: sorting functions.
- `MinPriorityQueue.h`: used by heap sort.
- `tests.cpp`: checks that the sorts work.
- `main.cpp`: compares sorting times.

## How to run

Run these commands to run tests and main

Tests:
```powershell
g++ -std=c++17 -Wall -Wextra -I. tests.cpp -o tests.exe
.\tests.exe
```

Benchmark:
```powershell
g++ -std=c++17 -O2 -Wall -Wextra -I. main.cpp -o benchmark.exe
.\benchmark.exe
```

## Tests

The tests that I checked for was unsorted input, sorted input, duplicates and zero, and empty input. All tests passed.

## Runtime explained

| Sort | Runtime | Why |
|---|---|---|
| Selection sort | Θ(n²) | It scans n values, then n−1, then n−2, and so on. These scans add up to quadratic work. |
| Merge sort | Θ(n log n) | There are about log n levels, with n values merged across each level. |
| Heap sort | Θ(n log n) | It adds and removes n values. Each heap operation takes up to log n work so worst case scenario. |
| Radix sort | Θ(nk) | It processes n values for each digit position. For values from 0–999, there are at most three passes, giving Θ(n). The k shows how many places it has to process. |

## Benchmark

For this comparison I used random values from 0 to 999 and ran five trials at each size. All sorts used the same input during each trial. The times below are averages in milliseconds and include sorting and its input copy into the actual function.

| Size | Selection (ms) | Merge (ms) | Heap (ms) | Radix (ms) |
|---:|---:|---:|---:|---:|
| 10 | 0.0014 | 0.0098 | 0.00246 | 0.00392 |
| 100 | 0.01098 | 0.07604 | 0.01398 | 0.01748 |
| 1000 | 0.6458 | 0.71208 | 0.1564 | 0.06274 |
| 10000 | 88.5732 | 6.99596 | 1.75876 | 0.27846 |

Selection sort was fastest for 10 and 100 values, but became much slower as the input grew. This fits its Θ(n²) runtime. Merge sort and heap sort handled larger inputs better. Radix sort was fastest for 1,000 and 10,000 values. The 0–999 range helps because it needs at most three digit passes. Maybe would be different if we added a number range of like 0-100k perhaps.

## Master Theorem worksheet

| Question | Runtime (Θ) | Reason |
|---|---|---|
| 1 | $n^2$ | Extra > critical |
| 2 | $n^{\log_2 7}$ | Critical > extra |
| 3 | $n^2\lg n$ | Same growth; add log |
| 4 | $n\lg n$ | Extra > critical |
| 5 | $n^2$ | Critical > extra |
| 6 | Does not apply | Input is n−1, not n/b |
| 7 | $n^2(\lg n)^2$ | Extra = critical × log; add another log |
| 8 | $n^{\log_2 5}$ | Critical > extra, even with the extra log |
| 9 | Does not apply | Only a log gap, not a power gap |
| 10 | $\sqrt n$ | Critical > constant extra work |
| 11 | $(\lg n)^2$ | Extra = critical × log; add another log |
| 12 | Does not apply | Recursive calls have different input sizes |
| 13 | $\sqrt n$ | Critical > extra |
| 14 | $n(\lg n)^2$ | Extra = critical × log; add another log |
| 15 | Does not apply | Input is not n/b for a fixed b |
| 16 | $\sqrt n\lg n$ | Same growth; add log |
| 17 | $n^{0.51}$ | Extra > critical: 0.51 > 0.5 |
| 18 | $n!$ | Factorial extra work > critical |
| 19 | $n^{\log_2 3}$ | Critical > extra |
| 20 | $n^2$ | Critical > extra; c is constant |
| 21 | $n\lg n$ | Same growth; dividing by 2 is a constant factor |
| 22 | $n^2$ | Critical n² > extra n/log n by a power of n |
| 23 | $n^2$ | Extra > critical |
| 24 | $2^n$ | Exponential extra work > critical |
| 25 | $n^2$ | Critical > extra |
