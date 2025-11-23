/**************************************************************************************************
 * Unit Tests for Dijkstra's Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/Dijkstra.h"
#include <limits>

using namespace GraphLib;

class DijkstraTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a weighted directed graph
        graph = new Graph(5, true, true, false);
        graph->insertEdge(1, 2, 4.0f);
        graph->insertEdge(1, 3, 2.0f);
        graph->insertEdge(2, 3, 1.0f);
        graph->insertEdge(2, 4, 5.0f);
        graph->insertEdge(3, 4, 8.0f);
        graph->insertEdge(3, 5, 10.0f);
        graph->insertEdge(4, 5, 2.0f);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(DijkstraTest, ShortestPathFromSource) {
    std::vector<float> distances = Dijkstra::shortestPath(graph, 1);
    
    EXPECT_EQ(distances[1], 0.0f);  // Distance to itself
    EXPECT_EQ(distances[2], 4.0f);   // Direct edge
    EXPECT_EQ(distances[3], 2.0f);   // Direct edge
    EXPECT_EQ(distances[4], 9.0f);   // Path: 1->2->4 (4+5=9)
    EXPECT_EQ(distances[5], 11.0f);  // Path: 1->2->4->5 (4+5+2=11)
}

TEST_F(DijkstraTest, ShortestPathToTarget) {
    std::vector<int> path = Dijkstra::shortestPathTo(graph, 1, 5);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path[0], 1);  // Start node
    EXPECT_EQ(path[path.size()-1], 5);  // End node
}

TEST_F(DijkstraTest, GetDistance) {
    float dist = Dijkstra::getDistance(graph, 1, 5);
    EXPECT_NE(dist, std::numeric_limits<float>::max());
    EXPECT_GT(dist, 0);
}

TEST_F(DijkstraTest, UnreachableNode) {
    Graph* isolated = new Graph(3, true, true, false);
    isolated->insertEdge(1, 2, 1.0f);
    // Node 3 is isolated
    
    std::vector<float> distances = Dijkstra::shortestPath(isolated, 1);
    EXPECT_EQ(distances[1], 0.0f);
    EXPECT_EQ(distances[2], 1.0f);
    EXPECT_EQ(distances[3], std::numeric_limits<float>::max());
    
    delete isolated;
}

TEST_F(DijkstraTest, SingleNodeGraph) {
    Graph* single = new Graph(1, true, true, false);
    single->insertNode(1);
    
    std::vector<float> distances = Dijkstra::shortestPath(single, 1);
    EXPECT_EQ(distances[1], 0.0f);
    
    delete single;
}

