#include "SequenceAlignment.h"
#include "Genome.h"
#include "Matrix.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <chrono>
#include <cstdlib>

int main() {
    AlignmentResult result = needlemanWunsch(genomeSnippet, testAgainst);

    std::cout << "Alignment score: " << result.score << "\n\n";
    //test the sequence alignment first
    //print both aligned strings in blocks of 60 characters since full string is too long
    for (std::size_t i = 0; i < result.firstAligned.size(); i += 60) {
        std::cout << "First:  " << result.firstAligned.substr(i, 60) << "\n";
        std::cout << "Second: " << result.secondAligned.substr(i, 60) << "\n\n";
    }

    //set the matrix sizes and Strassen cutoffs to try.
    std::vector<int> sizes = {16, 32, 64, 128};
    std::vector<int> cutoffs = {1, 8, 16, 32};
    int trials = 3;
    double resultTotal = 0.0;
    std::srand(42);
    //make table to compare and analyze run times
    std::cout << "| Size | Method | Cutoff | Average (ms) |\n";
    std::cout << "|---:|---|---:|---:|\n";

    for (int size : sizes) {
        Matrix first(size);
        Matrix second(size);

        //fill both matrices with random numbers from 0 to 9
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                first.set(r, c, std::rand() % 10);
                second.set(r, c, std::rand() % 10);
            }
        }

        //track time taken
        double regularTime = 0.0;

        for (int trial = 0; trial < trials; trial++) {
            auto start = std::chrono::steady_clock::now();
            auto result = first.multiply(second);
            auto end = std::chrono::steady_clock::now();

            regularTime += std::chrono::duration<double, std::milli>(end - start).count();

            //use a value from the answer after timing ends
            resultTotal += result.value().get(0, 0).value();
        }

        std::cout << "| " << size << " | Regular | - | "
                << regularTime / trials << " |\n";

        //time Strassen with each cutoff, using the same matrices
        for (int cutoff : cutoffs) {
            double strassenTime = 0.0;

            for (int trial = 0; trial < trials; trial++) {
                auto start = std::chrono::steady_clock::now();
                auto result = first.strassenMultiply(second, cutoff);
                auto end = std::chrono::steady_clock::now();

                strassenTime += std::chrono::duration<double, std::milli>(end - start).count();

                resultTotal += result.value().get(0, 0).value();
            }

            std::cout << "| " << size << " | Strassen | " << cutoff
                    << " | " << strassenTime / trials << " |\n";
        }
    }

    std::cout << "\nResult total: " << resultTotal << "\n";    
    
    return 0;
}