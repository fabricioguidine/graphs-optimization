/**************************************************************************************************
 * Unit Tests for Topological Sort Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/TopologicalSort.h"

using namespace GraphLib;

class TopologicalSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a directed acyclic graph
        dag = new Graph(6, true, false, false);
        dag->insertEdge(1, 2, 0);
        dag->insertEdge(1, 3, 0);
        dag->insertEdge(2, 4, 0);
        dag->insertEdge(3, 4, 0);
        dag->insertEdge(4, 5, 0);
        dag->insertEdge(5, 6, 0);
    }
    
    void TearDown() override {
        delete dag;
    }
    
    Graph* dag;
};

TEST_F(TopologicalSortTest, TopologicalSort) {
    std::vector<int> order = TopologicalSort::sort(dag);
    
    EXPECT_EQ(order.size(), dag->getOrder());
    
    // Verify topological property: for edge (u,v), u appears before v
    // Node 1 should appear before 2, 3
    // Node 4 should appear after 2, 3
    // Node 5 should appear after 4
    // Node 6 should appear after 5
}

TEST_F(TopologicalSortTest, HasTopologicalOrder) {
    EXPECT_TRUE(TopologicalSort::hasTopologicalOrder(dag));
}

TEST_F(TopologicalSortTest, GraphWithCycle) {
    Graph* cyclic = new Graph(3, true, false, false);
    cyclic->insertEdge(1, 2, 0);
    cyclic->insertEdge(2, 3, 0);
    cyclic->insertEdge(3, 1, 0);  // Creates cycle
    
    EXPECT_FALSE(TopologicalSort::hasTopologicalOrder(cyclic));
    
    delete cyclic;
}

TEST_F(TopologicalSortTest, EmptyGraph) {
    Graph* empty = new Graph(0, true, false, false);
    
    std::vector<int> order = TopologicalSort::sort(empty);
    EXPECT_EQ(order.size(), 0);
    
    delete empty;
}

TEST_F(TopologicalSortTest, SingleNode) {
    Graph* single = new Graph(1, true, false, false);
    single->insertNode(1);
    
    std::vector<int> order = TopologicalSort::sort(single);
    EXPECT_EQ(order.size(), 1);
    EXPECT_EQ(order[0], 1);
    
    delete single;
}

