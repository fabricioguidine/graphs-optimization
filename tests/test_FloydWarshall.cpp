/**************************************************************************************************
 * Unit Tests for Floyd-Warshall Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/FloydWarshall.h"
#include <limits>

using namespace GraphLib;

class FloydWarshallTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a weighted directed graph
        graph = new Graph(4, true, true, false);
        graph->insertEdge(1, 2, 3.0f);
        graph->insertEdge(1, 3, 6.0f);
        graph->insertEdge(2, 3, 2.0f);
        graph->insertEdge(3, 4, 1.0f);
        graph->insertEdge(4, 1, 2.0f);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(FloydWarshallTest, AllPairsShortestPath) {
    std::vector<std::vector<float>> dist = FloydWarshall::allPairsShortestPath(graph);
    
    EXPECT_EQ(dist[1][1], 0.0f);  // Distance to itself
    EXPECT_EQ(dist[1][2], 3.0f);  // Direct edge
    EXPECT_EQ(dist[1][3], 5.0f);  // Path: 1->2->3 (3+2=5)
    EXPECT_EQ(dist[1][4], 6.0f);  // Path: 1->2->3->4 (3+2+1=6)
}

TEST_F(FloydWarshallTest, GetDistance) {
    float dist = FloydWarshall::getDistance(graph, 1, 4);
    EXPECT_NE(dist, std::numeric_limits<float>::max());
    EXPECT_GT(dist, 0);
}

TEST_F(FloydWarshallTest, GetPath) {
    std::vector<int> path = FloydWarshall::getPath(graph, 1, 4);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path[0], 1);
    EXPECT_EQ(path[path.size()-1], 4);
}

