/**************************************************************************************************
 * Dijkstra's Shortest Path Algorithm
 * Finds the shortest path from a source node to all other nodes in a weighted graph
**************************************************************************************************/

#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "../Graph.h"
#include <vector>
#include <limits>

namespace GraphLib {

class Dijkstra {
public:
    // Find shortest distances from source to all nodes
    static std::vector<float> shortestPath(Graph* graph, int sourceId);
    
    // Find shortest path from source to target
    static std::vector<int> shortestPathTo(Graph* graph, int sourceId, int targetId);
    
    // Get distance from source to target
    static float getDistance(Graph* graph, int sourceId, int targetId);
};

} // namespace GraphLib

#endif // DIJKSTRA_H_INCLUDED

