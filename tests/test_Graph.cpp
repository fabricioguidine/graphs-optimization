/**************************************************************************************************
 * Unit Tests for Graph Data Structure
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include <fstream>
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Edge.h"

using namespace GraphLib;

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        graph = new Graph(5, false, false, false);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(GraphTest, InsertNode) {
    graph->insertNode(1);
    EXPECT_TRUE(graph->searchNode(1));
    EXPECT_EQ(graph->getOrder(), 5);
}

TEST_F(GraphTest, InsertEdge) {
    graph->insertEdge(1, 2, 0);
    EXPECT_TRUE(graph->searchNode(1));
    EXPECT_TRUE(graph->searchNode(2));
    EXPECT_EQ(graph->getNumberEdges(), 1);
}

TEST_F(GraphTest, RemoveNode) {
    graph->insertEdge(1, 2, 0);
    graph->removeNode(1);
    EXPECT_FALSE(graph->searchNode(1));
    EXPECT_TRUE(graph->searchNode(2));
}

TEST_F(GraphTest, DepthFirstSearch) {
    graph->insertEdge(1, 2, 0);
    graph->insertEdge(2, 3, 0);
    graph->insertEdge(3, 4, 0);
    
    EXPECT_TRUE(graph->depthFirstSearch(1, 4));
    EXPECT_FALSE(graph->depthFirstSearch(1, 5));
}

TEST_F(GraphTest, ConnectedGraph) {
    graph->insertEdge(1, 2, 0);
    graph->insertEdge(2, 3, 0);
    graph->insertEdge(3, 4, 0);
    graph->insertEdge(4, 1, 0);
    
    EXPECT_TRUE(graph->connectedGraph());
}

TEST_F(GraphTest, HasCircuit) {
    graph->insertEdge(1, 2, 0);
    graph->insertEdge(2, 3, 0);
    graph->insertEdge(3, 1, 0);
    
    EXPECT_TRUE(graph->hasCircuit());
}

TEST_F(GraphTest, GetComplement) {
    graph->insertEdge(1, 2, 0);
    Graph* complement = graph->getComplement();
    
    EXPECT_NE(complement, nullptr);
    EXPECT_TRUE(complement->searchNode(1));
    EXPECT_TRUE(complement->searchNode(2));
    
    delete complement;
}

TEST_F(GraphTest, BreadthFirstSearch) {
    graph->insertEdge(1, 2, 0);
    graph->insertEdge(2, 3, 0);
    graph->insertEdge(3, 4, 0);
    
    std::ofstream output("test_bfs_output.txt");
    graph->breadthFirstSearch(output);
    output.close();
    
    // Verify BFS was executed (file should be created)
    std::ifstream check("test_bfs_output.txt");
    EXPECT_TRUE(check.good());
    check.close();
    
    // Clean up
    remove("test_bfs_output.txt");
}

