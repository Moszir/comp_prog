#include "benchmark/benchmark.h"
#include "moszir_lib/string.hpp"

const std::string bmInputSingle = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += ',';
    }
    return s;
}();

const std::string bmInputMulti = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += (i % 3 == 0 ? ',' : i % 3 == 1 ? ';' : '.');
    }
    return s;
}();

std::vector<std::string_view> splitSvPtr(std::string_view str, std::string_view delims)
{
    std::vector<std::string_view> output;
    for (auto first = str.data(), second = str.data(), last = first + str.size();
         second != last && first != last; first = second + 1)
    {
        second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));
        if (first != second) output.emplace_back(first, second - first);
    }
    return output;
}

std::vector<std::string> split(const std::string& str, const std::string& delims = " ")
{
    std::vector<std::string> output;
    auto first = std::cbegin(str);
    while (first != std::cend(str))
    {
        const auto second = std::find_first_of(first, std::cend(str), std::cbegin(delims), std::cend(delims));
        if (first != second) output.emplace_back(first, second);
        if (second == std::cend(str)) break;
        first = std::next(second);
    }
    return output;
}

std::vector<std::string_view> splitSv(std::string_view strv, std::string_view delims = " ")
{
    std::vector<std::string_view> output;
    size_t first = 0;
    while (first < strv.size())
    {
        const auto second = strv.find_first_of(delims, first);
        if (first != second) output.emplace_back(strv.substr(first, second-first));
        if (second == std::string_view::npos) break;
        first = second + 1;
    }
    return output;
}

static void benchmarkStringVector(benchmark::State& state)
{
    ::moszir::StringVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputSingle, ",");
    }
}
BENCHMARK(benchmarkStringVector);

static void benchmarkStringViewVector(benchmark::State& state)
{
    ::moszir::StringViewVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputSingle, ",");
    }
}
BENCHMARK(benchmarkStringViewVector);

static void benchmarkSplitSvPtr(benchmark::State& state)
{
    std::vector<std::string_view> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitSvPtr(bmInputSingle, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitSvPtr);

static void benchmarkSplit(benchmark::State& state)
{
    std::vector<std::string> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(bmInputSingle, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplit);

static void benchmarkSplitSv(benchmark::State& state)
{
    std::vector<std::string_view> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitSv(bmInputSingle, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitSv);

static void benchmarkStringVectorMulti(benchmark::State& state)
{
    ::moszir::StringVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputMulti, ",;.");
    }
}
BENCHMARK(benchmarkStringVectorMulti);

static void benchmarkStringViewVectorMulti(benchmark::State& state)
{
    ::moszir::StringViewVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputMulti, ",;.");
    }
}
BENCHMARK(benchmarkStringViewVectorMulti);

static void benchmarkSplitSvPtrMulti(benchmark::State& state)
{
    std::vector<std::string_view> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitSvPtr(bmInputMulti, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitSvPtrMulti);

static void benchmarkSplitMulti(benchmark::State& state)
{
    std::vector<std::string> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(bmInputMulti, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitMulti);

static void benchmarkSplitSvMulti(benchmark::State& state)
{
    std::vector<std::string_view> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitSv(bmInputMulti, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitSvMulti);

BENCHMARK_MAIN();

/*

Run on (12 X 3192 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)

-------------------------------------------------------------------------
Benchmark                               Time             CPU   Iterations
-------------------------------------------------------------------------
benchmarkStringVector             1721223 ns      1196289 ns          640
benchmarkStringViewVector          937559 ns       823103 ns         1120
benchmarkSplitSvPtr               2068655 ns      1759383 ns          373
benchmarkSplit                    4520031 ns      3227700 ns          213
benchmarkSplitSv                  1924140 ns      1360212 ns          448
benchmarkStringVectorMulti        1632563 ns      1255020 ns          498
benchmarkStringViewVectorMulti     954852 ns       711496 ns         1120
benchmarkSplitSvPtrMulti          1641341 ns      1227679 ns          560
benchmarkSplitMulti               4714623 ns      4059436 ns          204
benchmarkSplitSvMulti             2381297 ns      2001953 ns          640

*/
