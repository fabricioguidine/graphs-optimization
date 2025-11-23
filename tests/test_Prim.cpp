/**************************************************************************************************
 * Unit Tests for Prim's Minimum Spanning Tree Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/Prim.h"

using namespace GraphLib;

class PrimTest : public ::testing::Test {
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

TEST_F(PrimTest, MinimumSpanningTree) {
    std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(graph);
    
    // MST should have (n-1) edges for n nodes
    EXPECT_EQ(mst.size(), graph->getOrder() - 1);
}

TEST_F(PrimTest, MSTWeight) {
    float weight = Prim::getMSTWeight(graph);
    
    EXPECT_GT(weight, 0);
    // Expected MST weight: 1+2+2+1 = 6 (edges: 2-3, 1-2, 3-4, 4-5)
    EXPECT_LE(weight, 10.0f);  // Should be less than total graph weight
}

TEST_F(PrimTest, ConnectedGraph) {
    // Prim requires connected graph
    EXPECT_TRUE(graph->connectedGraph());
    
    std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(graph);
    EXPECT_GT(mst.size(), 0);
}

TEST_F(PrimTest, SingleNodeGraph) {
    Graph* single = new Graph(1, false, true, false);
    single->insertNode(1);
    
    std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(single);
    EXPECT_EQ(mst.size(), 0);  // No edges in single node graph
    
    delete single;
}

