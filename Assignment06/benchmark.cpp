#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include "Fourier.h"

int main() {
    std::vector<int> sizes = {64, 128, 256, 512, 1024, 2048, 4096};
    double pi = 3.141592653589793;
    double checksum = 0.0;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Samples,DFT_ms,FFT_ms,Speedup\n";

    for (int sampleCount : sizes) {
        double sampleRate = sampleCount;
        std::vector<double> signal;

        // THe input generation
        for (int i = 0; i < sampleCount; i++) {
            double time = i / sampleRate;

            double firstWave = std::sin(2 * pi * 5 * time);
            double secondWave = 0.5 * std::sin(2 * pi * 12 * time);

            signal.push_back(firstWave + secondWave);
        }

        std::vector<double> dftTimes;
        std::vector<double> fftTimes;

        // Loop for the five measured runs
        for (int run = 0; run < 6; run++) {
            auto dftStart = std::chrono::steady_clock::now();
            auto dftResult = dft(signal);
            auto dftEnd = std::chrono::steady_clock::now();
            auto fftStart = std::chrono::steady_clock::now();
            auto fftResult = fft(signal);
            auto fftEnd = std::chrono::steady_clock::now();

            // Convert the elapsed times to milliseconds.
            std::chrono::duration<double, std::milli> dftElapsed =
                dftEnd - dftStart;

            std::chrono::duration<double, std::milli> fftElapsed =
                fftEnd - fftStart;

            // First one is teh warm up run
            if (run > 0) {
                dftTimes.push_back(dftElapsed.count());
                fftTimes.push_back(fftElapsed.count());
            }

            // Read the outputs after it was timed
            for (int k = 0; k < sampleCount; k++) {
                checksum += std::abs(dftResult[k]);
                checksum += std::abs(fftResult[k]);
            }
        }

        // Here we sort the five times and select the middle one sicne its the median
        std::sort(dftTimes.begin(), dftTimes.end());
        std::sort(fftTimes.begin(), fftTimes.end());
        double dftMedian = dftTimes[2];
        double fftMedian = fftTimes[2];
        double speedup = dftMedian / fftMedian;

        std::cout << sampleCount << ","
                  << dftMedian << ","
                  << fftMedian << ","
                  << speedup << "\n";
    }

    std::cout << "\nResult checksum: " << checksum << "\n";
    return 0;
}