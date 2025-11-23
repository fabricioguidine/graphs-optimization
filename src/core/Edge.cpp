/**************************************************************************************************
 * Implementation of Edge methods
**************************************************************************************************/

#include "../../include/Edge.h"
#include <iostream>

namespace GraphLib {

// Constructor
Edge::Edge(int target_id) {
    this->target_id = target_id;
    this->next_edge = nullptr;
    this->weight = 0;
}

// Destructor
Edge::~Edge() {
    // Note: We don't delete next_edge here to avoid recursive deletion
    // The Node class manages the edge list
}

// Getters
int Edge::getTargetId() const {
    return this->target_id;
}

Edge* Edge::getNextEdge() const {
    return this->next_edge;
}

float Edge::getWeight() const {
    return this->weight;
}

// Setters
void Edge::setNextEdge(Edge* edge) {
    this->next_edge = edge;
}

void Edge::setWeight(float weight) {
    this->weight = weight;
}

} // namespace GraphLib

