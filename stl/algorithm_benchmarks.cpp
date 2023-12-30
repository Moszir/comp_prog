#include <algorithm>
#include <numeric> // std::iota
#include <iterator> // std::back_inserter

#include "benchmark/benchmark.h"

int times2(int x) { return 2*x; }

auto generateNumbers(const int size)
{
    std::vector<int> a(size, 0);
    std::iota(a.begin(), a.end(), 1);
    return a;
}

const auto lotOfNumbers = generateNumbers(1'000'000);

// region transform
static void benchmarkTransformNormal(benchmark::State& state)
{
    std::vector<int> results{};
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), std::back_inserter(results), times2);
    }
}
BENCHMARK(benchmarkTransformNormal);

static void benchmarkTransformRanges(benchmark::State& state)
{
    std::vector<int> results{};
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, std::back_inserter(results), times2);
    }
}
BENCHMARK(benchmarkTransformRanges);
// endregion transform

BENCHMARK_MAIN();

/** Benchmark results

Run on (12 X 3192 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)

-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
benchmarkTransformNormal    3893505 ns      3452035 ns          172
benchmarkTransformRanges    3595494 ns      2399554 ns          280

 */
