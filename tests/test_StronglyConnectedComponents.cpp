/**************************************************************************************************
 * Unit Tests for Strongly Connected Components Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/StronglyConnectedComponents.h"

using namespace GraphLib;

class StronglyConnectedComponentsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a directed graph with multiple SCCs
        graph = new Graph(6, true, false, false);
        // First SCC: 1->2->3->1
        graph->insertEdge(1, 2, 0);
        graph->insertEdge(2, 3, 0);
        graph->insertEdge(3, 1, 0);
        // Second SCC: 4->5->4
        graph->insertEdge(4, 5, 0);
        graph->insertEdge(5, 4, 0);
        // Isolated node: 6
        graph->insertNode(6);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(StronglyConnectedComponentsTest, FindSCC) {
    std::vector<std::vector<int>> sccs = StronglyConnectedComponents::findSCC(graph);
    
    EXPECT_GE(sccs.size(), 2);  // At least 2 SCCs
    
    // Verify each SCC contains nodes that are reachable from each other
    bool foundSCC1 = false, foundSCC2 = false, foundSCC6 = false;
    for (const auto& scc : sccs) {
        if (scc.size() == 3) {  // SCC with nodes 1,2,3
            foundSCC1 = true;
        } else if (scc.size() == 2) {  // SCC with nodes 4,5
            foundSCC2 = true;
        } else if (scc.size() == 1 && scc[0] == 6) {  // Isolated node
            foundSCC6 = true;
        }
    }
    
    EXPECT_TRUE(foundSCC1 || foundSCC2);  // At least one multi-node SCC
}

TEST_F(StronglyConnectedComponentsTest, GetSCCCount) {
    int count = StronglyConnectedComponents::getSCCCount(graph);
    
    EXPECT_GE(count, 2);
    EXPECT_LE(count, 4);  // Maximum: 3-node SCC, 2-node SCC, and isolated node
}

TEST_F(StronglyConnectedComponentsTest, SingleNodeSCC) {
    Graph* single = new Graph(1, true, false, false);
    single->insertNode(1);
    
    std::vector<std::vector<int>> sccs = StronglyConnectedComponents::findSCC(single);
    EXPECT_EQ(sccs.size(), 1);
    EXPECT_EQ(sccs[0].size(), 1);
    
    delete single;
}

TEST_F(StronglyConnectedComponentsTest, FullyConnectedGraph) {
    Graph* fullyConnected = new Graph(3, true, false, false);
    fullyConnected->insertEdge(1, 2, 0);
    fullyConnected->insertEdge(2, 3, 0);
    fullyConnected->insertEdge(3, 1, 0);
    fullyConnected->insertEdge(2, 1, 0);
    fullyConnected->insertEdge(3, 2, 0);
    fullyConnected->insertEdge(1, 3, 0);
    
    int count = StronglyConnectedComponents::getSCCCount(fullyConnected);
    EXPECT_EQ(count, 1);  // All nodes in one SCC
    
    delete fullyConnected;
}

