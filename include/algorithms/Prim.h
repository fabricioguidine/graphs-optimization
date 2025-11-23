/**************************************************************************************************
 * Prim's Minimum Spanning Tree Algorithm
 * Finds the minimum spanning tree of a connected weighted undirected graph
**************************************************************************************************/

#ifndef PRIM_H_INCLUDED
#define PRIM_H_INCLUDED

#include "../Graph.h"
#include <vector>
#include <utility>

namespace GraphLib {

class Prim {
public:
    // Find minimum spanning tree
    static std::vector<std::pair<int, int>> minimumSpanningTree(Graph* graph);
    
    // Get total weight of MST
    static float getMSTWeight(Graph* graph);
};

} // namespace GraphLib

#endif // PRIM_H_INCLUDED

