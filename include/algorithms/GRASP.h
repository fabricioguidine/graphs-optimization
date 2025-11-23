/**************************************************************************************************
 * GRASP (Greedy Randomized Adaptive Search Procedure)
 * Metaheuristic algorithm for optimization problems on graphs
**************************************************************************************************/

#ifndef GRASP_H_INCLUDED
#define GRASP_H_INCLUDED

#include "../Graph.h"
#include <vector>
#include <random>

namespace GraphLib {

class GRASP {
private:
    static std::mt19937 rng;
    
public:
    // GRASP algorithm for graph problems
    static std::vector<int> solve(Graph* graph, int maxIterations = 100, 
                                   float alpha = 0.3f);
    
    // Greedy randomized construction
    static std::vector<int> greedyRandomizedConstruction(Graph* graph, float alpha);
    
    // Local search improvement
    static std::vector<int> localSearch(Graph* graph, const std::vector<int>& solution);
    
    // Evaluate solution quality
    static float evaluateSolution(Graph* graph, const std::vector<int>& solution);
};

} // namespace GraphLib

#endif // GRASP_H_INCLUDED

