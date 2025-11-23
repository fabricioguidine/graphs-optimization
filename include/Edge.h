/**************************************************************************************************
 * Implementation of the TAD Edge
 * Represents an edge in the graph data structure
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

namespace GraphLib {

class Edge {
private:
    int target_id;
    Edge* next_edge;
    float weight;

public:
    // Constructor
    Edge(int target_id);
    
    // Destructor
    ~Edge();
    
    // Getters
    int getTargetId() const;
    Edge* getNextEdge() const;
    float getWeight() const;
    
    // Setters
    void setNextEdge(Edge* edge);
    void setWeight(float weight);
};

} // namespace GraphLib

#endif // EDGE_H_INCLUDED

