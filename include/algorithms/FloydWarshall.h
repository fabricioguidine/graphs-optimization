/**************************************************************************************************
 * Floyd-Warshall Algorithm
 * Finds shortest paths between all pairs of nodes in a weighted graph
**************************************************************************************************/

#ifndef FLOYD_WARSHALL_H_INCLUDED
#define FLOYD_WARSHALL_H_INCLUDED

#include "../Graph.h"
#include <vector>

namespace GraphLib {

class FloydWarshall {
public:
    // Compute shortest distances between all pairs
    static std::vector<std::vector<float>> allPairsShortestPath(Graph* graph);
    
    // Get shortest distance from source to target
    static float getDistance(Graph* graph, int sourceId, int targetId);
    
    // Get shortest path from source to target
    static std::vector<int> getPath(Graph* graph, int sourceId, int targetId);
};

} // namespace GraphLib

#endif // FLOYD_WARSHALL_H_INCLUDED

