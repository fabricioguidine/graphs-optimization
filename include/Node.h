/**************************************************************************************************
 * Implementation of the TAD Node
 * Represents a node (vertex) in the graph data structure
**************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "Edge.h"

namespace GraphLib {

class Node {
private:
    Edge* first_edge;
    Edge* last_edge;
    int id;
    unsigned int in_degree;
    unsigned int out_degree;
    float weight;
    Node* next_node;

public:
    // Constructor
    Node(int id);
    
    // Destructor
    ~Node();
    
    // Getters
    Edge* getFirstEdge() const;
    Edge* getLastEdge() const;
    int getId() const;
    int getInDegree() const;
    int getOutDegree() const;
    float getWeight() const;
    Node* getNextNode() const;
    
    // Setters
    void setNextNode(Node* node);
    void setWeight(float weight);
    
    // Edge operations
    bool searchEdge(int target_id) const;
    void insertEdge(int target_id, float weight);
    void removeAllEdges();
    int removeEdge(int id, bool directed, Node* target_node);
    Edge* hasEdgeBetween(int target_id) const;
    
    // Degree operations
    void incrementOutDegree();
    void decrementOutDegree();
    void incrementInDegree();
    void decrementInDegree();
};

} // namespace GraphLib

#endif // NODE_H_INCLUDED

