# Assignment 05: Matrices and Sequence Alignment

This project implements regular matrix multiplication, Strassen's algorithm, and Needleman-Wunsch sequence alignment in C++.

## How to run the files

Run these commands in order to run the test file and the main file.
To compile and run the main program:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -I. main.cpp -o main.exe
.\main.exe
```

To compile and run the tests:

```powershell
g++ -std=c++17 -Wall -Wextra -I. tests.cpp -o tests.exe
.\tests.exe
```

If there is successful completion of the tests it will print `All tests passed!`.

## Benchmark

I tested four  different matrix sizes and then ran each method three times to get an average. For each size, all methods used the same two matrices filled with random numbers from 0 to 9. The times are in milliseconds, and creating the input and printing are outside the timer.
So basically, the cutoff tells Strassen when to stop splitting and use regular multiplication. For example, a cutoff of 16  would mean that blocks that are 16x16 or smaller would use regular multiplication.

| Size | Regular | Strassen: cutoff 1 | Cutoff 8 | Cutoff 16 | Cutoff 32 |
|---:|---:|---:|---:|---:|---:|
| 16 | 0.0149667 | 1.6252 | 0.0576333 | 0.00696667 | 0.00646667 |
| 32 | 0.0332333 | 10.3233 | 0.279967 | 0.109267 | 0.0368 |
| 64 | 0.191567 | 79.3329 | 1.93617 | 1.3376 | 0.3934 |
| 128 | 1.85063 | 546.411 | 21.1031 | 9.7183 | 3.73773 |

### Analysis

Out of the cutoffs I tested, 32 gave the fastest Strassen times. Regular multiplication was still faster for sizes 32, 64, and 128. For example, at 128x128, regular took about 1.85 ms while Strassen with cutoff 32 took about 3.74 ms, which is about twice as long. Increasing the cutoff helped because the Strassen algorithm would stop splitting sooner and would then use regular multiplication for more of the smaller blocks. Creating and copying all those smaller matrices probably took more time than Strassen saved by doing fewer multiplications.

When the matrix is already at or below the cutoff, the function just uses regular multiplication. That explains why some results are basically timing the same method but still have slightly different times. I can definately see how the strassen algorithm can be faster for much larger matrices, but I didn’t find a size in my tests where it was faster than regular multiplication.

## DNA alignment

I used Needleman-Wunsch to align `genomeSnippet` with `testAgainst`. Matches  would score +1, mismatches -1, and gaps -1. The final score ended upbeing **143**. Dashes represent gaps in the alignment below, it is split like this since the string is too long.

```text
First:  TGGCGACAACCG-TAGCGGAATATTTTCGCGACCAGGGAAAACGGGTCGTGCTT-TTTAT
Second: TGGCCACCA-CGATAGCAGAATTTTTTCGCGATAATGGAAAGCGAGTCGT-CTTGCTTGC

First:  CGATTC-CATGACCCGTTATGCGC-GTGCTTTGCGAGACGTGGCACTGG-CGTCGG-GAG
Second: CGACTCAC-TGACGCGTTATGC-CAGGGCCGCACGGGAAATCGCTCTGGCCGCCGGAGAG

First:  AGCGTCCGG-CTCGTCGAGGTTATCCCGCC-TCCGTA-TTCGAT-AATTTGCCCCG-CTT
Second: ACCG--CGGTTTC-TGGAGAATAT-CCGCCAGGCGTATTTAG-TGCA-TTGCCACGACTT

First:  GCTGGAACGCCCAGGG---GCGACCAGCGAGGGAAGCATTACTGCCTTTTATACGGTACT
Second: -TTAGAACGTAC-GGGAATGGGA-GA-AAAAGGCAGTATTACCGCATTTTATACGGTACT

First:  GCTGGAAAGCGAGGA-A-GAGGCGGACCCGATGGCGGATGAAATTCGCTCTA-TCCTTGA
Second: GGTGGAAGGCGATGATATGA--ATGAGCCGTTGGCGGATGAAGTCCGTTC-ACTGCTTGA

First:  CGGTCA-CCTGTATCTGA-GCAGAAAGCTGGCCGGGCA-GGGACATTACCCGGCAATCGA
Second: TGGACATATTGTA-CT-ATCCCGACGGCTTGCAGAG-AGGGGGCATTATCCTGCCATTGA

First:  TGTACT-GAAAAGCGTAAGCCGCGTTTTT
Second: CGTGTTGGCAACGC-TCAGCCGCGTTTTT
```