/**************************************************************************************************
 * Topological Sort (Kahn's Algorithm)
 * Finds a topological ordering of nodes in a directed acyclic graph
**************************************************************************************************/

#ifndef TOPOLOGICAL_SORT_H_INCLUDED
#define TOPOLOGICAL_SORT_H_INCLUDED

#include "../Graph.h"
#include <vector>

namespace GraphLib {

class TopologicalSort {
public:
    // Perform topological sort
    static std::vector<int> sort(Graph* graph);
    
    // Check if graph has a valid topological ordering
    static bool hasTopologicalOrder(Graph* graph);
};

} // namespace GraphLib

#endif // TOPOLOGICAL_SORT_H_INCLUDED

