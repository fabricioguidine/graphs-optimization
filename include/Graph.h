/**************************************************************************************************
 * Implementation of the TAD Graph
 * Main graph data structure with support for directed/undirected and weighted graphs
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Node.h"
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <limits>
#include <string>

namespace GraphLib {

class Graph {
private:
    int order;
    int number_edges;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node* first_node;
    Node* last_node;

public:
    // Constructor
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    
    // Destructor
    ~Graph();
    
    // Getters
    int getOrder() const;
    int getNumberEdges() const;
    bool getDirected() const;
    bool getWeightedEdge() const;
    bool getWeightedNode() const;
    Node* getFirstNode() const;
    Node* getLastNode() const;
    
    // Node operations
    void insertNode(int id);
    void removeNode(int id);
    bool searchNode(int id) const;
    Node* getNode(int id) const;
    
    // Edge operations
    void insertEdge(int id, int target_id, float weight);
    
    // Graph analysis
    bool depthFirstSearch(int initialId, int targetId) const;
    void breadthFirstSearch(std::ofstream& output_file) const;
    Graph* getComplement() const;
    Graph* getSubjacent() const;
    bool hasCircuit() const;
    bool connectedGraph() const;
    
    // Output
    void printGraph() const;
    void generateOutput(const std::string& filename) const;
};

} // namespace GraphLib

#endif // GRAPH_H_INCLUDED

