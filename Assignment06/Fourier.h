#pragma once
#include <vector>
#include <complex>
#include <cmath>

std::vector<std::complex<double>> dft(const std::vector<double>& signal) {
    int sampleCount = signal.size();
    double pi = 3.141592653589793;
    std::vector<std::complex<double>> result(sampleCount);

    // First check each possible frequency bin
    for (int k = 0; k < sampleCount; k++) {
        double cosineTotal = 0.0;
        double sineTotal = 0.0;
        // Compare every sample with the reference wave to see how much they match
        for (int i = 0; i < sampleCount; i++) {
            double angle = 2 * pi * k * i / sampleCount;
            cosineTotal += signal[i] * std::cos(angle);
            sineTotal += signal[i] * std::sin(angle);
        }
        
        // Store both totals
        result[k] = std::complex<double>(cosineTotal, -sineTotal);
    }
    return result;
}

std::vector<std::complex<double>> fft(const std::vector<double>& signal) {
    int sampleCount = signal.size();
    double pi = 3.141592653589793;

    // Check if there is an empty input fo we have reached base case
    if (sampleCount == 0) {
        return {};
    }
    if (sampleCount == 1) {
        return {std::complex<double>(signal[0], 0.0)};
    }

    // Check that the sample count is a power of two
    int sizeCheck = sampleCount;
    while (sizeCheck > 1) {
        if (sizeCheck % 2 != 0) {
            return {};
        }
        sizeCheck = sizeCheck / 2;
    }

    // Then we split the samples by index
    std::vector<double> even;
    std::vector<double> odd;
    for (int i = 0; i < sampleCount; i++) {
        if (i % 2 == 0) {
            even.push_back(signal[i]);
        } else {
            odd.push_back(signal[i]);
        }
    }

    // Recursive call of fft function to get teh fft value of the smaller groups
    auto evenResult = fft(even);
    auto oddResult = fft(odd);
    // Combine the smaller Fourier results.
    std::vector<std::complex<double>> result(sampleCount);
    for (int k = 0; k < sampleCount / 2; k++) {
        double angle = 2 * pi * k / sampleCount;
        std::complex<double> w(std::cos(angle),-std::sin(angle));
        std::complex<double> adjustedOdd = w * oddResult[k];
        result[k] = evenResult[k] + adjustedOdd;
        result[k + sampleCount / 2] = evenResult[k] - adjustedOdd;
    }

    return result;
}