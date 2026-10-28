# FFT vs. Direct DFT

## 1. Project overview

This project implements a direct DFT and a recursive radix-2 Cooley–Tukey FFT in C++. Both convert sampled signals into complex frequency-bin values. Generated sine waves with known frequencies and amplitudes are used to check correctness, followed by a runtime comparison.

## 2. Files I used and how to run them

- `Fourier.h`: DFT and FFT implementations.
- `main.cpp`: Two-frequency demonstration.
- `tests.cpp`: Automated correctness tests.
- `benchmark.cpp`: Runtime measurements.

With `g++` installed, run these commands in PowerShell from the `DSA-2026` repository root. Compile each program separately and run it only if compilation succeeds.

```powershell
g++ -std=c++17 .\Assignment06\main.cpp -o .\Assignment06\main.exe
.\Assignment06\main.exe

g++ -std=c++17 .\Assignment06\tests.cpp -o .\Assignment06\tests.exe
.\Assignment06\tests.exe

g++ -std=c++17 -O2 .\Assignment06\benchmark.cpp -o .\Assignment06\benchmark.exe
.\Assignment06\benchmark.exe
```

The demonstration in the amin uses `signal.push_back(firstWave + secondWave);`. No external C++ libraries are required to run these files.

## 3. How the algorithms work

**DFT:** For every frequency bin, my algorithm will visit every sample and accumulates the cosine and negative sine contributions into a complex result. There are $N$ bins and $N$ samples per bin, giving $\Theta(N^2)$ runtime.

**FFT:** This algorithm is aquite different since it splits even and odd indexed samples into smaller groups and recursively transforms them until each group contains one sample. It combines the results using twiddle factors, sums, and differences. The twiddle factors adjust the phase of the odd group's contribution since in these smaller groups the odd and even start at index 0 so we have to add the offset of the odd numbers back in. Overall there are $\log_2 N$ splitting levels, with $\Theta(N)$ total work per level, giving $\Theta(N\log N)$ runtime. This radix-2 implementation requires power of two input lengths.

## 4. Correctness tests

In my tests they use 64 samples at 64 samples per second, so bins 5 and 12 would represent 5 Hz and 12 Hz. For these sine wave peaks, amplitude is calculated as `2 * abs(X[k]) / N`.

The tests would check output sizes, compare every complex DFT/FFT bin using an absolute tolerance of `1e-9`, and verify both transforms expected amplitudes. The zero input test also checks that every output bin is near zero.

This is a quick table of the three scenarios I use in my tests
| Input | Expected amplitudes: 5 Hz, 12 Hz | Largest DFT/FFT difference | Result |
|---|---|---:|---|
| Zero input | 0, 0 | 0 | PASS |
| One frequency | 1, 0 | `3.23598e-13` | PASS |
| Two frequencies | 1, 0.5 | `3.72085e-13` | PASS |

Both transforms recovered amplitudes 1 at 5 Hz and 0.5 at 12 Hz for the combined signal. There was tiny numerical differences but are to be expected from floating point rounding.

## 5. Benchmark results

Both algorithms receive the same signal at each size. For tracking the time I used `std::chrono::steady_clock` which excludes signal generation and printing, and then reports the median of five runs. Speedup is DFT time divided by FFT time jsut to see how many times faster the FFT was than the DFT.

| Samples | DFT median (ms) | FFT median (ms) | FFT speedup |
|---:|---:|---:|---:|
| 64 | 0.089400 | 0.027300 | 3.27× |
| 128 | 0.343000 | 0.056700 | 6.05× |
| 256 | 1.420200 | 0.119100 | 11.92× |
| 512 | 6.897700 | 0.279700 | 24.66× |
| 1024 | 24.089500 | 0.616600 | 39.07× |
| 2048 | 91.888500 | 1.233000 | 74.52× |
| 4096 | 379.134300 | 2.261600 | 167.64× |

At 4096 samples, FFT was about 168 times faster in this Windows benchmark. Doubling from 2048 to 4096 samples increased DFT runtime about 4.13 times, close to the fourfold increase expected from quadratic growth. FFT runtime increased about 1.83 times. The results show clearly the slower growth of FFT, but timings are not a proof of complexity. Overhead and measurement variation would also affect the observed ratios.

## 6. What I learned and limitations

I understood the different runtimes we discussed in class, but actually seeing the DFT and FFT scale made the differences much easier to picture. Doubling the DFT’s input meant twice as many frequency bins and twice as many samples per bin, which explained the roughly 4x increase in runtime. I also got more practice applying recursion and divide and conquer in C++, especially with splitting the input into smaller groups and combining their results correctly.

## 7. Sources and acknowledgments

I used ChatGPT to explain the DFT and FFT in simpler terms so I could understand each step while working through the C++ implementation.

Further learning resources:
- Brian Douglas, MathWorks: [Understanding the Discrete Fourier Transform and the FFT](https://www.mathworks.com/videos/understanding-the-discrete-fourier-transform-and-the-fft-1700042348737.html) — video I used that explains DFT/FFT, frequency bins, and amplitudes.
- Brian McFee: [Radix-2 Cooley-Tukey](https://brianmcfee.net/dstbook-site/content/ch08-fft/FFT.html) — written walkthrough of even/odd splitting, twiddle factors, recursion, and runtime.