/**************************************************************************************************
 * End-to-end tests: full pipeline from an on-disk instance file through the
 * GraphReader to algorithm output, asserting known textbook results.
 *
 * These exercise cross-platform file I/O (std::filesystem temp paths, text
 * streams) in addition to the algorithms, complementing the in-memory unit
 * and invariant tests.
 *
 *   - A weighted directed graph read from file yields the textbook Dijkstra
 *     shortest-path distances.
 *   - A weighted undirected graph read from file yields an MST whose total
 *     weight matches the hand-computed optimum, and Prim and Kruskal agree.
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <memory>
#include <string>

#include "../include/Graph.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/Prim.h"
#include "../include/utils/GraphReader.h"

using GraphLib::Dijkstra;
using GraphLib::Graph;
using GraphLib::GraphReader;
using GraphLib::Kruskal;
using GraphLib::Prim;

namespace {

// RAII helper: writes content to a unique temp file and removes it on scope
// exit. Uses std::filesystem for portable temp-directory and path handling.
class TempInstanceFile {
public:
    TempInstanceFile(const std::string& stem, const std::string& content) {
        const auto dir = std::filesystem::temp_directory_path();
        path_ = dir / (stem + "_" +
                       std::to_string(std::filesystem::hash_value(dir) ^
                                      reinterpret_cast<std::uintptr_t>(this)) +
                       ".txt");
        std::ofstream out(path_, std::ios::out | std::ios::trunc);
        out << content;
    }

    ~TempInstanceFile() {
        std::error_code ec;
        std::filesystem::remove(path_, ec);
    }

    TempInstanceFile(const TempInstanceFile&) = delete;
    TempInstanceFile& operator=(const TempInstanceFile&) = delete;

    std::string path() const { return path_.string(); }

private:
    std::filesystem::path path_;
};

}  // namespace

// readFromFile (weighted edge) format: first token is the order, then one
// "source target weight" triple per line.
TEST(EndToEndTest, DijkstraFromInstanceFile) {
    // Same 5-node weighted DAG as the Dijkstra unit test, but loaded from disk.
    const std::string instance =
        "5\n"
        "1 2 4\n"
        "1 3 2\n"
        "2 3 1\n"
        "2 4 5\n"
        "3 4 8\n"
        "3 5 10\n"
        "4 5 2\n";

    TempInstanceFile file("e2e_dijkstra", instance);
    std::unique_ptr<Graph> graph(GraphReader::readFromFile(
        file.path(), /*directed=*/true, /*weightedEdge=*/true,
        /*weightedNode=*/false));
    ASSERT_NE(graph, nullptr);

    const std::vector<float> dist = Dijkstra::shortestPath(graph.get(), 1);
    EXPECT_FLOAT_EQ(dist[1], 0.0f);
    EXPECT_FLOAT_EQ(dist[2], 4.0f);
    EXPECT_FLOAT_EQ(dist[3], 2.0f);
    EXPECT_FLOAT_EQ(dist[4], 9.0f);   // 1->2->4
    EXPECT_FLOAT_EQ(dist[5], 11.0f);  // 1->2->4->5
}

TEST(EndToEndTest, MstFromInstanceFile) {
    // Undirected weighted graph; hand-computed minimum spanning tree:
    //   edges: (1,2,1) (1,3,4) (2,3,2) (3,4,2) (2,4,5)
    //   MST picks 1-2 (1), 2-3 (2), 3-4 (2)  => total 5
    const std::string instance =
        "4\n"
        "1 2 1\n"
        "1 3 4\n"
        "2 3 2\n"
        "3 4 2\n"
        "2 4 5\n";

    TempInstanceFile file("e2e_mst", instance);
    std::unique_ptr<Graph> graph(GraphReader::readFromFile(
        file.path(), /*directed=*/false, /*weightedEdge=*/true,
        /*weightedNode=*/false));
    ASSERT_NE(graph, nullptr);

    const float kruskalWeight = Kruskal::getMSTWeight(graph.get());
    const float primWeight = Prim::getMSTWeight(graph.get());

    EXPECT_FLOAT_EQ(kruskalWeight, 5.0f);
    EXPECT_FLOAT_EQ(primWeight, 5.0f);

    // MST of a connected graph with V nodes has exactly V-1 edges.
    EXPECT_EQ(Kruskal::minimumSpanningTree(graph.get()).size(), 3u);
}

TEST(EndToEndTest, MissingFileReturnsNull) {
    const auto missing =
        (std::filesystem::temp_directory_path() / "e2e_does_not_exist_42.txt")
            .string();
    std::unique_ptr<Graph> graph(GraphReader::readFromFile(
        missing, /*directed=*/false, /*weightedEdge=*/true,
        /*weightedNode=*/false));
    EXPECT_EQ(graph, nullptr);
}
