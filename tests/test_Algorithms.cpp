/**************************************************************************************************
 * Unit Tests for Graph Algorithms
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/FloydWarshall.h"
#include "../include/algorithms/Prim.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/TopologicalSort.h"
#include "../include/algorithms/StronglyConnectedComponents.h"

using namespace GraphLib;

class AlgorithmsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a weighted undirected graph for MST tests
        mstGraph = new Graph(4, false, true, false);
        mstGraph->insertEdge(1, 2, 1.0f);
        mstGraph->insertEdge(2, 3, 2.0f);
        mstGraph->insertEdge(3, 4, 1.0f);
        mstGraph->insertEdge(1, 4, 3.0f);
        
        // Create a weighted directed graph for shortest path tests
        shortestPathGraph = new Graph(4, true, true, false);
        shortestPathGraph->insertEdge(1, 2, 1.0f);
        shortestPathGraph->insertEdge(2, 3, 2.0f);
        shortestPathGraph->insertEdge(1, 4, 4.0f);
        shortestPathGraph->insertEdge(4, 3, 1.0f);
        
        // Create a directed acyclic graph for topological sort
        dagGraph = new Graph(5, true, false, false);
        dagGraph->insertEdge(1, 2, 0);
        dagGraph->insertEdge(1, 3, 0);
        dagGraph->insertEdge(2, 4, 0);
        dagGraph->insertEdge(3, 4, 0);
        dagGraph->insertEdge(4, 5, 0);
    }
    
    void TearDown() override {
        delete mstGraph;
        delete shortestPathGraph;
        delete dagGraph;
    }
    
    Graph* mstGraph;
    Graph* shortestPathGraph;
    Graph* dagGraph;
};

TEST_F(AlgorithmsTest, DijkstraShortestPath) {
    std::vector<float> distances = Dijkstra::shortestPath(shortestPathGraph, 1);
    EXPECT_NE(distances[3], std::numeric_limits<float>::max());
    EXPECT_GT(distances[3], 0);
}

TEST_F(AlgorithmsTest, FloydWarshallAllPairs) {
    std::vector<std::vector<float>> dist = FloydWarshall::allPairsShortestPath(shortestPathGraph);
    EXPECT_NE(dist[1][3], std::numeric_limits<float>::max());
}

TEST_F(AlgorithmsTest, PrimMST) {
    std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(mstGraph);
    EXPECT_GT(mst.size(), 0);
    EXPECT_LT(mst.size(), mstGraph->getNumberEdges());
    
    float weight = Prim::getMSTWeight(mstGraph);
    EXPECT_GT(weight, 0);
}

TEST_F(AlgorithmsTest, KruskalMST) {
    std::vector<std::pair<int, int>> mst = Kruskal::minimumSpanningTree(mstGraph);
    EXPECT_GT(mst.size(), 0);
    
    float weight = Kruskal::getMSTWeight(mstGraph);
    EXPECT_GT(weight, 0);
}

TEST_F(AlgorithmsTest, TopologicalSort) {
    std::vector<int> order = TopologicalSort::sort(dagGraph);
    EXPECT_EQ(order.size(), dagGraph->getOrder());
    EXPECT_TRUE(TopologicalSort::hasTopologicalOrder(dagGraph));
}

TEST_F(AlgorithmsTest, StronglyConnectedComponents) {
    // Create a graph with SCCs
    Graph* sccGraph = new Graph(5, true, false, false);
    sccGraph->insertEdge(1, 2, 0);
    sccGraph->insertEdge(2, 3, 0);
    sccGraph->insertEdge(3, 1, 0);
    sccGraph->insertEdge(4, 5, 0);
    sccGraph->insertEdge(5, 4, 0);
    
    std::vector<std::vector<int>> sccs = StronglyConnectedComponents::findSCC(sccGraph);
    EXPECT_GE(sccs.size(), 2);
    
    delete sccGraph;
}

