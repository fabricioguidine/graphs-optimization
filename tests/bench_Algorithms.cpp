/**************************************************************************************************
 * Microbenchmarks for graph algorithms using Google Benchmark.
 *
 * Build with:
 *   cmake -S . -B build -DGRAPHS_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
 *   cmake --build build --target graph_benchmarks
 *   ./build/bin/graph_benchmarks
 **************************************************************************************************/

#include <benchmark/benchmark.h>

#include <memory>
#include <random>
#include <set>
#include <utility>

#include "../include/Graph.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/FloydWarshall.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/Prim.h"

namespace {

std::unique_ptr<GraphLib::Graph> buildSparseConnectedWeighted(int n,
                                                              int extra,
                                                              bool directed,
                                                              unsigned seed) {
    auto g = std::make_unique<GraphLib::Graph>(n, directed, true, false);
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> w(1.0f, 100.0f);

    // Spanning path.
    for (int i = 1; i < n; ++i) {
        g->insertEdge(i, i + 1, w(rng));
    }
    std::uniform_int_distribution<int> v(1, n);
    std::set<std::pair<int, int>> seen;
    for (int i = 1; i < n; ++i) {
        seen.emplace(std::min(i, i + 1), std::max(i, i + 1));
    }
    int added = 0;
    int guard = 0;
    while (added < extra && guard < extra * 10 + 100) {
        int a = v(rng);
        int b = v(rng);
        ++guard;
        if (a == b) continue;
        auto key = std::make_pair(std::min(a, b), std::max(a, b));
        if (seen.count(key)) continue;
        seen.insert(key);
        g->insertEdge(a, b, w(rng));
        ++added;
    }
    return g;
}

}  // namespace

static void BM_Dijkstra(benchmark::State& state) {
    const int n = static_cast<int>(state.range(0));
    auto g = buildSparseConnectedWeighted(n, n * 2, /*directed=*/true, 1234);
    for (auto _ : state) {
        auto d = GraphLib::Dijkstra::shortestPath(g.get(), 1);
        benchmark::DoNotOptimize(d);
    }
    state.SetComplexityN(n);
}
BENCHMARK(BM_Dijkstra)->RangeMultiplier(2)->Range(64, 1024)->Complexity();

static void BM_Prim(benchmark::State& state) {
    const int n = static_cast<int>(state.range(0));
    auto g = buildSparseConnectedWeighted(n, n * 2, /*directed=*/false, 2345);
    for (auto _ : state) {
        auto m = GraphLib::Prim::minimumSpanningTree(g.get());
        benchmark::DoNotOptimize(m);
    }
    state.SetComplexityN(n);
}
BENCHMARK(BM_Prim)->RangeMultiplier(2)->Range(64, 1024)->Complexity();

static void BM_Kruskal(benchmark::State& state) {
    const int n = static_cast<int>(state.range(0));
    auto g = buildSparseConnectedWeighted(n, n * 2, /*directed=*/false, 3456);
    for (auto _ : state) {
        auto m = GraphLib::Kruskal::minimumSpanningTree(g.get());
        benchmark::DoNotOptimize(m);
    }
    state.SetComplexityN(n);
}
BENCHMARK(BM_Kruskal)->RangeMultiplier(2)->Range(64, 1024)->Complexity();

static void BM_FloydWarshall(benchmark::State& state) {
    const int n = static_cast<int>(state.range(0));
    auto g = buildSparseConnectedWeighted(n, n * 2, /*directed=*/true, 4567);
    for (auto _ : state) {
        auto fw = GraphLib::FloydWarshall::allPairsShortestPath(g.get());
        benchmark::DoNotOptimize(fw);
    }
    state.SetComplexityN(n);
}
BENCHMARK(BM_FloydWarshall)->RangeMultiplier(2)->Range(32, 256)->Complexity();

BENCHMARK_MAIN();
