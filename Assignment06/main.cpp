#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include "Fourier.h"

int main() {
    int sampleCount = 64;
    double sampleRate = 64.0;
    double pi = 3.141592653589793;
    std::vector<double> signal;

    // Create a signal containing 5 Hz and 12 Hz waves
    for (int i = 0; i < sampleCount; i++) {
        double time = i / sampleRate;

        double firstWave = 1.0 * std::sin(2 * pi * 5 * time);
        double secondWave = 0.5 * std::sin(2 * pi * 12 * time);

        signal.push_back(firstWave + secondWave);
    }

    std::cout << "Created " << signal.size() << " samples.\n";

    // Print the first eight sample heights
    for (int i = 0; i < 8; i++) {
        std::cout << "Sample " << i << ": " << signal[i] << "\n";
    }

    // Run both transforms on the same signal
    auto dftResult = dft(signal);
    auto fftResult = fft(signal);

    // Check sizes before accessing teh results
    if (dftResult.size() != signal.size() ||
        fftResult.size() != signal.size()) {
        std::cout << "ERROR: Unexpected number of frequency bins.\n";
        return 1;
    }

    // With this setup, bin 5 reoresents 5 Hz and bin 12 represents 12 Hz
    std::cout << "\nDFT amplitudes:\n";
    std::cout << "5 Hz: "
              << 2.0 * std::abs(dftResult[5]) / sampleCount << "\n";
    std::cout << "12 Hz: "
              << 2.0 * std::abs(dftResult[12]) / sampleCount << "\n";

    std::cout << "\nFFT amplitudes:\n";
    std::cout << "5 Hz: "
              << 2.0 * std::abs(fftResult[5]) / sampleCount << "\n";
    std::cout << "12 Hz: "
              << 2.0 * std::abs(fftResult[12]) / sampleCount << "\n";

    // Find the largest difference between all of teh bins
    double maxError = 0.0;
    for (int k = 0; k < sampleCount; k++) {
        double error = std::abs(dftResult[k] - fftResult[k]);

        if (error > maxError) {
            maxError = error;
        }
    }

    double tolerance = 1e-9;
    std::cout << "\nLargest difference: " << maxError << "\n";
    std::cout << "Allowed difference: " << tolerance << "\n";

    if (maxError <= tolerance) {
        std::cout << "DFT vs FFT: PASS\n";
    } else {
        std::cout << "DFT vs FFT: FAIL\n";
        return 1;
    }

    return 0;
}