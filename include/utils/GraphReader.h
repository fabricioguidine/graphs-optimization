/**************************************************************************************************
 * Graph File Reader Utility
 * Reads graph instances from files
**************************************************************************************************/

#ifndef GRAPH_READER_H_INCLUDED
#define GRAPH_READER_H_INCLUDED

#include "../Graph.h"
#include <fstream>
#include <string>

namespace GraphLib {

class GraphReader {
public:
    // Read graph from file
    static Graph* readFromFile(const std::string& filename, bool directed, 
                               bool weightedEdge, bool weightedNode);
    
    // Read instance file (with order and numEdges header)
    static Graph* readInstance(const std::string& filename, bool directed, 
                               bool weightedEdge, bool weightedNode);
};

} // namespace GraphLib

#endif // GRAPH_READER_H_INCLUDED

