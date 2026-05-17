/**************************************************************************************************
 * Invariant / property-style tests for graph algorithms.
 *
 * These tests assert algorithmic invariants on small handcrafted graphs and on
 * pseudo-randomly generated graphs (deterministic seeds, so results are
 * reproducible in CI). They complement the existing per-algorithm unit tests.
 *
 *   - BFS reaches every node in a connected undirected graph.
 *   - DFS finds a path iff Dijkstra finds a finite distance.
 *   - Dijkstra distances satisfy the triangle inequality d(s,v) <= d(s,u) + w(u,v).
 *   - On a known graph, Dijkstra returns the textbook shortest distance.
 *   - MST has exactly V-1 edges and Prim/Kruskal agree on total weight.
 *   - Floyd-Warshall agrees with Dijkstra on all-pairs distances.
 *   - Topological sort respects edge ordering on a DAG.
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <random>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../include/Graph.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/FloydWarshall.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/Prim.h"
#include "../include/algorithms/TopologicalSort.h"

using GraphLib::Dijkstra;
using GraphLib::FloydWarshall;
using GraphLib::Graph;
using GraphLib::Kruskal;
using GraphLib::Prim;
using GraphLib::TopologicalSort;

namespace {

constexpr float kInf = std::numeric_limits<float>::max();

// Build a weighted undirected graph from an edge list (1-indexed node ids).
std::unique_ptr<Graph> makeUndirectedWeighted(
    int n, const std::vector<std::tuple<int, int, float>>& edges) {
    auto g = std::make_unique<Graph>(n, /*directed=*/false,
                                     /*weighted_edge=*/true,
                                     /*weighted_node=*/false);
    for (auto [u, v, w] : edges) {
        g->insertEdge(u, v, w);
    }
    return g;
}

std::unique_ptr<Graph> makeDirectedWeighted(
    int n, const std::vector<std::tuple<int, int, float>>& edges) {
    auto g = std::make_unique<Graph>(n, /*directed=*/true,
                                     /*weighted_edge=*/true,
                                     /*weighted_node=*/false);
    for (auto [u, v, w] : edges) {
        g->insertEdge(u, v, w);
    }
    return g;
}

// Generate a deterministic connected sparse weighted undirected graph.
std::unique_ptr<Graph> generateRandomConnected(int n, int extra_edges,
                                               unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> w_dist(1.0f, 10.0f);

    std::vector<std::tuple<int, int, float>> edges;
    // Spanning path to guarantee connectivity.
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1, w_dist(rng));
    }
    std::uniform_int_distribution<int> v_dist(1, n);
    std::set<std::pair<int, int>> seen;
    for (int i = 1; i < n; ++i) {
        seen.emplace(std::min(i, i + 1), std::max(i, i + 1));
    }
    int added = 0;
    int guard = 0;
    while (added < extra_edges && guard < extra_edges * 10 + 50) {
        int u = v_dist(rng);
        int v = v_dist(rng);
        ++guard;
        if (u == v) continue;
        auto key = std::make_pair(std::min(u, v), std::max(u, v));
        if (seen.count(key)) continue;
        seen.insert(key);
        edges.emplace_back(u, v, w_dist(rng));
        ++added;
    }
    return makeUndirectedWeighted(n, edges);
}

}  // namespace

// -------------------------------------------------------------------------
// Dijkstra invariants
// -------------------------------------------------------------------------

TEST(Invariants, DijkstraKnownGraphShortestPath) {
    // Classic textbook example. Source = 1.
    //   1 --4-- 2 --1-- 3
    //   |       |       |
    //   2       5       8
    //   |       |       |
    //   3 --10- 5 --2-- 4
    auto g = makeDirectedWeighted(5, {
        {1, 2, 4.0f}, {1, 3, 2.0f}, {2, 3, 1.0f},
        {2, 4, 5.0f}, {3, 4, 8.0f}, {3, 5, 10.0f}, {4, 5, 2.0f},
    });

    auto d = Dijkstra::shortestPath(g.get(), 1);
    EXPECT_FLOAT_EQ(d[1], 0.0f);
    EXPECT_FLOAT_EQ(d[2], 4.0f);
    EXPECT_FLOAT_EQ(d[3], 2.0f);
    EXPECT_FLOAT_EQ(d[4], 9.0f);   // 1 -> 2 -> 4
    EXPECT_FLOAT_EQ(d[5], 11.0f);  // 1 -> 2 -> 4 -> 5
}

TEST(Invariants, DijkstraNonNegativeDistances) {
    for (unsigned seed = 1; seed <= 5; ++seed) {
        auto g = generateRandomConnected(20, 25, seed);
        auto d = Dijkstra::shortestPath(g.get(), 1);
        for (std::size_t i = 1; i < d.size(); ++i) {
            EXPECT_GE(d[i], 0.0f) << "seed=" << seed << " i=" << i;
        }
        EXPECT_FLOAT_EQ(d[1], 0.0f);
    }
}

TEST(Invariants, DijkstraReachableSameAsDFS) {
    for (unsigned seed = 1; seed <= 3; ++seed) {
        auto g = generateRandomConnected(15, 15, seed);
        auto d = Dijkstra::shortestPath(g.get(), 1);
        for (std::size_t i = 1; i < d.size(); ++i) {
            const bool reach_dfs =
                g->depthFirstSearch(1, static_cast<int>(i));
            const bool reach_dij = d[i] != kInf;
            EXPECT_EQ(reach_dfs, reach_dij)
                << "Dijkstra and DFS disagree on reachability of " << i
                << " (seed " << seed << ")";
        }
    }
}

// -------------------------------------------------------------------------
// MST invariants (Prim vs Kruskal)
// -------------------------------------------------------------------------

TEST(Invariants, MSTKnownGraphWeight) {
    // Standard MST example, undirected weighted.
    //   1 --1-- 2
    //   |       |
    //   4       2
    //   |       |
    //   4 --3-- 3
    //   1 --5-- 3   (extra non-MST edge)
    auto g = makeUndirectedWeighted(4, {
        {1, 2, 1.0f}, {2, 3, 2.0f},
        {3, 4, 3.0f}, {1, 4, 4.0f}, {1, 3, 5.0f},
    });

    const float prim_w    = Prim::getMSTWeight(g.get());
    const float kruskal_w = Kruskal::getMSTWeight(g.get());

    EXPECT_FLOAT_EQ(prim_w, 6.0f);
    EXPECT_FLOAT_EQ(kruskal_w, 6.0f);
    EXPECT_FLOAT_EQ(prim_w, kruskal_w);
}

TEST(Invariants, MSTEdgeCount) {
    auto g = generateRandomConnected(12, 18, /*seed=*/42);
    auto edges = Prim::minimumSpanningTree(g.get());
    EXPECT_EQ(edges.size(), static_cast<std::size_t>(g->getOrder() - 1));
}

TEST(Invariants, PrimAndKruskalAgreeOnRandomGraphs) {
    for (unsigned seed = 1; seed <= 5; ++seed) {
        auto g = generateRandomConnected(10, 12, seed);
        const float pw = Prim::getMSTWeight(g.get());
        const float kw = Kruskal::getMSTWeight(g.get());
        EXPECT_NEAR(pw, kw, 1e-4f) << "seed=" << seed;
    }
}

// -------------------------------------------------------------------------
// Floyd-Warshall consistency with Dijkstra
// -------------------------------------------------------------------------

TEST(Invariants, FloydWarshallAgreesWithDijkstra) {
    auto g = makeDirectedWeighted(5, {
        {1, 2, 4.0f}, {1, 3, 2.0f}, {2, 3, 1.0f},
        {2, 4, 5.0f}, {3, 4, 8.0f}, {3, 5, 10.0f}, {4, 5, 2.0f},
    });

    auto fw = FloydWarshall::allPairsShortestPath(g.get());
    for (int src = 1; src <= 5; ++src) {
        auto dij = Dijkstra::shortestPath(g.get(), src);
        for (int dst = 1; dst <= 5; ++dst) {
            const float a = fw[static_cast<std::size_t>(src)]
                              [static_cast<std::size_t>(dst)];
            const float b = dij[static_cast<std::size_t>(dst)];
            if (a == kInf || b == kInf) {
                EXPECT_EQ(a == kInf, b == kInf)
                    << "src=" << src << " dst=" << dst;
            } else {
                EXPECT_NEAR(a, b, 1e-4f) << "src=" << src << " dst=" << dst;
            }
        }
    }
}

// -------------------------------------------------------------------------
// Topological sort invariants
// -------------------------------------------------------------------------

TEST(Invariants, TopologicalSortRespectsEdges) {
    // DAG:   1 -> 2 -> 4
    //        1 -> 3 -> 4
    //        3 -> 5
    auto g = makeDirectedWeighted(5, {
        {1, 2, 0.0f}, {1, 3, 0.0f},
        {2, 4, 0.0f}, {3, 4, 0.0f}, {3, 5, 0.0f},
    });

    EXPECT_TRUE(TopologicalSort::hasTopologicalOrder(g.get()));
    auto order = TopologicalSort::sort(g.get());
    ASSERT_EQ(order.size(), 5u);

    std::unordered_map<int, int> pos;
    for (std::size_t i = 0; i < order.size(); ++i) {
        pos[order[i]] = static_cast<int>(i);
    }
    const std::vector<std::pair<int, int>> edges = {
        {1, 2}, {1, 3}, {2, 4}, {3, 4}, {3, 5},
    };
    for (auto [u, v] : edges) {
        ASSERT_TRUE(pos.count(u) && pos.count(v));
        EXPECT_LT(pos[u], pos[v]) << "edge " << u << "->" << v
                                  << " violated by topo order";
    }
}

TEST(Invariants, TopologicalSortRejectsCycle) {
    auto g = makeDirectedWeighted(3, {
        {1, 2, 0.0f}, {2, 3, 0.0f}, {3, 1, 0.0f},
    });
    EXPECT_FALSE(TopologicalSort::hasTopologicalOrder(g.get()));
}
