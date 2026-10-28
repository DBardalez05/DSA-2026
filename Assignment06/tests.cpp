#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <string>
#include "Fourier.h"

// Run both transforms and check their results.
bool runTest(const std::string& name, const std::vector<double>& signal, double expected5Hz, double expected12Hz) {
    double tolerance = 1e-9;
    int sampleCount = signal.size();

    auto dftResult = dft(signal);
    auto fftResult = fft(signal);

    // Tests use 64 sample at 64 Hz sample rate
    if (sampleCount != 64 ||
        dftResult.size() != signal.size() ||
        fftResult.size() != signal.size()) {
        std::cout << name << ": FAIL (unexpected result size)\n";
        return false;
    }

    bool passed = true;
    double maxError = 0.0;

    // Compare every complex frequency bin
    for (int k = 0; k < sampleCount; k++) {
        double error = std::abs(dftResult[k] - fftResult[k]);
        if (error > maxError) {
            maxError = error;
        }
        if (!(error <= tolerance)) {
            passed = false;
        }

        // Each bin must be at zero for the zero input case
        if (expected5Hz == 0.0 && expected12Hz == 0.0) {
            if (!(std::abs(dftResult[k]) <= tolerance &&
                  std::abs(fftResult[k]) <= tolerance)) {
                passed = false;
            }
        }
    }

    // Check the amplitudes against the known input waves
    double dft5Hz = 2.0 * std::abs(dftResult[5]) / sampleCount;
    double dft12Hz = 2.0 * std::abs(dftResult[12]) / sampleCount;
    double fft5Hz = 2.0 * std::abs(fftResult[5]) / sampleCount;
    double fft12Hz = 2.0 * std::abs(fftResult[12]) / sampleCount;

    bool correctDFT = std::abs(dft5Hz - expected5Hz) <= tolerance && std::abs(dft12Hz - expected12Hz) <= tolerance;

    bool correctFFT = std::abs(fft5Hz - expected5Hz) <= tolerance && std::abs(fft12Hz - expected12Hz) <= tolerance;

    //CHeck if all the tests have passed
    passed = passed && correctDFT && correctFFT;
    std::cout << name << ": ";

    if (passed) {
        std::cout << "PASS";
    } else {
        std::cout << "FAIL";
    }

    std::cout << " | The largest DFT/FFT difference: "
              << maxError << "\n";

    return passed;
}

int main() {
    int sampleCount = 64;
    double sampleRate = 64.0;
    double pi = 3.141592653589793;

    // Create 64 zero samples
    std::vector<double> zeroSignal(sampleCount, 0.0);

    std::vector<double> singleSignal;
    std::vector<double> twoSignal;

    for (int i = 0; i < sampleCount; i++) {
        double time = i / sampleRate;

        double firstWave = std::sin(2 * pi * 5 * time);
        double secondWave = 0.5 * std::sin(2 * pi * 12 * time);

        singleSignal.push_back(firstWave);
        twoSignal.push_back(firstWave + secondWave);
    }

    // The final two arguments are the expected amplitudes for 5 and 12 Hz
    bool zeroPassed = runTest("Zero input", zeroSignal, 0.0, 0.0);
    bool singlePassed = runTest("One frequency", singleSignal, 1.0, 0.0);
    bool twoPassed = runTest("Two frequencies", twoSignal, 1.0, 0.5);

    if (zeroPassed && singlePassed && twoPassed) {
        std::cout << "\nAll three tests passed!\n";
        return 0;
    }

    std::cout << "\nSome tests failed. :(\n";
    return 1;
}