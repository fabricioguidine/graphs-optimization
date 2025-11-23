/**************************************************************************************************
 * Strongly Connected Components (Kosaraju's Algorithm)
 * Finds all strongly connected components in a directed graph
**************************************************************************************************/

#ifndef STRONGLY_CONNECTED_COMPONENTS_H_INCLUDED
#define STRONGLY_CONNECTED_COMPONENTS_H_INCLUDED

#include "../Graph.h"
#include <vector>

namespace GraphLib {

class StronglyConnectedComponents {
public:
    // Find all strongly connected components
    static std::vector<std::vector<int>> findSCC(Graph* graph);
    
    // Get number of strongly connected components
    static int getSCCCount(Graph* graph);
};

} // namespace GraphLib

#endif // STRONGLY_CONNECTED_COMPONENTS_H_INCLUDED

