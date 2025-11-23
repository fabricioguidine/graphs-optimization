/**************************************************************************************************
 * Unit Tests for GRASP Algorithm
 * Using Google Test Framework
**************************************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include "../include/algorithms/GRASP.h"

using namespace GraphLib;

class GRASPTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a weighted graph for GRASP
        graph = new Graph(5, false, true, true);
        graph->insertEdge(1, 2, 3.0f);
        graph->insertEdge(1, 3, 2.0f);
        graph->insertEdge(2, 3, 1.0f);
        graph->insertEdge(2, 4, 4.0f);
        graph->insertEdge(3, 4, 2.0f);
        graph->insertEdge(3, 5, 3.0f);
        graph->insertEdge(4, 5, 1.0f);
    }
    
    void TearDown() override {
        delete graph;
    }
    
    Graph* graph;
};

TEST_F(GRASPTest, Solve) {
    std::vector<int> solution = GRASP::solve(graph, 10, 0.3f);
    
    EXPECT_GT(solution.size(), 0);
}

TEST_F(GRASPTest, GreedyRandomizedConstruction) {
    std::vector<int> solution = GRASP::greedyRandomizedConstruction(graph, 0.3f);
    
    EXPECT_GT(solution.size(), 0);
}

TEST_F(GRASPTest, LocalSearch) {
    std::vector<int> initial = {1, 2, 3};
    std::vector<int> improved = GRASP::localSearch(graph, initial);
    
    EXPECT_GE(improved.size(), 0);
}

TEST_F(GRASPTest, EvaluateSolution) {
    std::vector<int> solution = {1, 2, 3};
    float quality = GRASP::evaluateSolution(graph, solution);
    
    EXPECT_GE(quality, 0);
}

TEST_F(GRASPTest, MultipleIterations) {
    // Run GRASP with multiple iterations
    std::vector<int> solution1 = GRASP::solve(graph, 5, 0.3f);
    std::vector<int> solution2 = GRASP::solve(graph, 5, 0.3f);
    
    // Solutions may differ due to randomization
    EXPECT_GT(solution1.size(), 0);
    EXPECT_GT(solution2.size(), 0);
}

