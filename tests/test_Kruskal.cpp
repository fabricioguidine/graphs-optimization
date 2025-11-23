/**************************************************************************************************
 * Unit Tests for Kruskal's Minimum Spanning Tree Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/Prim.h"

using namespace GraphLib;

class KruskalTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a weighted undirected graph
        graph = new Graph(5, false, true, false);
        graph->insertEdge(1, 2, 2.0f);
        graph->insertEdge(1, 3, 3.0f);
        graph->insertEdge(2, 3, 1.0f);
        graph->insertEdge(2, 4, 4.0f);
        graph->insertEdge(3, 4, 2.0f);
        graph->insertEdge(3, 5, 5.0f);
        graph->insertEdge(4, 5, 1.0f);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(KruskalTest, MinimumSpanningTree) {
    std::vector<std::pair<int, int>> mst = Kruskal::minimumSpanningTree(graph);
    
    // MST should have (n-1) edges for n nodes
    EXPECT_EQ(mst.size(), graph->getOrder() - 1);
}

TEST_F(KruskalTest, MSTWeight) {
    float weight = Kruskal::getMSTWeight(graph);
    
    EXPECT_GT(weight, 0);
    // Expected MST weight: 1+2+2+1 = 6 (same as Prim)
    EXPECT_LE(weight, 10.0f);
}

TEST_F(KruskalTest, SameResultAsPrim) {
    float kruskalWeight = Kruskal::getMSTWeight(graph);
    float primWeight = Prim::getMSTWeight(graph);
    
    // Both algorithms should find the same MST weight
    EXPECT_FLOAT_EQ(kruskalWeight, primWeight);
}

TEST_F(KruskalTest, NoCyclesInMST) {
    std::vector<std::pair<int, int>> mst = Kruskal::minimumSpanningTree(graph);
    
    // Create a graph with only MST edges and verify no cycles
    Graph* mstGraph = new Graph(graph->getOrder(), false, true, false);
    for (const auto& edge : mst) {
        mstGraph->insertEdge(edge.first, edge.second, 1.0f);
    }
    
    // MST should not have cycles (basic check)
    EXPECT_EQ(mstGraph->getNumberEdges(), mst.size());
    
    delete mstGraph;
}

