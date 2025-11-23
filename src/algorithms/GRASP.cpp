/**************************************************************************************************
 * Implementation of GRASP Algorithm
**************************************************************************************************/

#include "../../include/algorithms/GRASP.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <limits>

namespace GraphLib {

std::mt19937 GRASP::rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::vector<int> GRASP::greedyRandomizedConstruction(Graph* graph, float alpha) {
    std::vector<int> solution;
    
    if(graph == nullptr) {
        return solution;
    }
    
    // Collect all nodes
    std::vector<int> candidates;
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        candidates.push_back(node->getId());
        node = node->getNextNode();
    }
    
    // Greedy randomized selection
    while(!candidates.empty()) {
        // Calculate benefits for each candidate
        std::vector<std::pair<float, int>> benefits;
        for(int candidate : candidates) {
            float benefit = evaluateSolution(graph, solution);
            // Add candidate temporarily
            solution.push_back(candidate);
            float newBenefit = evaluateSolution(graph, solution);
            solution.pop_back();
            benefits.push_back({newBenefit - benefit, candidate});
        }
        
        // Sort by benefit
        std::sort(benefits.begin(), benefits.end(), 
                  [](const std::pair<float, int>& a, const std::pair<float, int>& b) {
                      return a.first > b.first;
                  });
        
        // Create restricted candidate list (RCL)
        int rclSize = std::max(1, (int)(alpha * benefits.size()));
        std::vector<int> rcl;
        for(int i = 0; i < rclSize; i++) {
            rcl.push_back(benefits[i].second);
        }
        
        // Randomly select from RCL
        std::uniform_int_distribution<int> dist(0, rcl.size() - 1);
        int selected = rcl[dist(rng)];
        
        solution.push_back(selected);
        candidates.erase(std::remove(candidates.begin(), candidates.end(), selected), 
                        candidates.end());
    }
    
    return solution;
}

std::vector<int> GRASP::localSearch(Graph* graph, const std::vector<int>& solution) {
    std::vector<int> bestSolution = solution;
    float bestValue = evaluateSolution(graph, bestSolution);
    bool improved = true;
    
    while(improved) {
        improved = false;
        
        // Try removing each element
        for(size_t i = 0; i < bestSolution.size(); i++) {
            std::vector<int> candidate = bestSolution;
            candidate.erase(candidate.begin() + i);
            float candidateValue = evaluateSolution(graph, candidate);
            
            if(candidateValue > bestValue) {
                bestSolution = candidate;
                bestValue = candidateValue;
                improved = true;
                break;
            }
        }
        
        // Try adding elements not in solution
        if(!improved) {
            std::vector<int> notInSolution;
            Node* node = graph->getFirstNode();
            while(node != nullptr) {
                if(std::find(bestSolution.begin(), bestSolution.end(), node->getId()) == 
                   bestSolution.end()) {
                    notInSolution.push_back(node->getId());
                }
                node = node->getNextNode();
            }
            
            for(int candidate : notInSolution) {
                std::vector<int> newSolution = bestSolution;
                newSolution.push_back(candidate);
                float newValue = evaluateSolution(graph, newSolution);
                
                if(newValue > bestValue) {
                    bestSolution = newSolution;
                    bestValue = newValue;
                    improved = true;
                    break;
                }
            }
        }
    }
    
    return bestSolution;
}

float GRASP::evaluateSolution(Graph* graph, const std::vector<int>& solution) {
    if(solution.empty()) {
        return 0.0f;
    }
    
    // Example evaluation: maximize coverage or minimize cost
    // This is a placeholder - adjust based on specific problem
    float value = 0.0f;
    
    for(int nodeId : solution) {
        Node* node = graph->getNode(nodeId);
        if(node != nullptr) {
            value += 1.0f; // Base value
            if(graph->getWeightedNode()) {
                value += node->getWeight();
            }
        }
    }
    
    return value;
}

std::vector<int> GRASP::solve(Graph* graph, int maxIterations, float alpha) {
    std::vector<int> bestSolution;
    float bestValue = std::numeric_limits<float>::lowest();
    
    for(int iter = 0; iter < maxIterations; iter++) {
        // Construction phase
        std::vector<int> solution = greedyRandomizedConstruction(graph, alpha);
        
        // Local search phase
        solution = localSearch(graph, solution);
        
        // Update best solution
        float value = evaluateSolution(graph, solution);
        if(value > bestValue) {
            bestValue = value;
            bestSolution = solution;
        }
    }
    
    return bestSolution;
}

} // namespace GraphLib

