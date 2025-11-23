/**************************************************************************************************
 * Implementation of Node methods
**************************************************************************************************/

#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <iostream>

namespace GraphLib {

// Constructor
Node::Node(int id) {
    this->id = id;
    this->in_degree = 0;
    this->out_degree = 0;
    this->weight = 0;
    this->first_edge = nullptr;
    this->last_edge = nullptr;
    this->next_node = nullptr;
}

// Destructor
Node::~Node() {
    Edge* next_edge = this->first_edge;
    while(next_edge != nullptr) {
        Edge* aux_edge = next_edge->getNextEdge();
        delete next_edge;
        next_edge = aux_edge;
    }
}

// Getters
Edge* Node::getFirstEdge() const {
    return this->first_edge;
}

Edge* Node::getLastEdge() const {
    return this->last_edge;
}

int Node::getId() const {
    return this->id;
}

int Node::getInDegree() const {
    return this->in_degree;
}

int Node::getOutDegree() const {
    return this->out_degree;
}

float Node::getWeight() const {
    return this->weight;
}

Node* Node::getNextNode() const {
    return this->next_node;
}

// Setters
void Node::setNextNode(Node* next_node) {
    this->next_node = next_node;
}

void Node::setWeight(float weight) {
    this->weight = weight;
}

// Edge operations
void Node::insertEdge(int target_id, float weight) {
    if(this->first_edge != nullptr) {
        Edge* edge = new Edge(target_id);
        edge->setWeight(weight);
        this->last_edge->setNextEdge(edge);
        this->last_edge = edge;
    } else {
        this->first_edge = new Edge(target_id);
        this->first_edge->setWeight(weight);
        this->last_edge = this->first_edge;
    }
}

void Node::removeAllEdges() {
    if(this->first_edge != nullptr) {
        Edge* next = nullptr;
        Edge* aux = this->first_edge;
        while(aux != nullptr) {
            next = aux->getNextEdge();
            delete aux;
            aux = next;
        }
    }
    this->first_edge = this->last_edge = nullptr;
}

int Node::removeEdge(int id, bool directed, Node* target_node) {
    if(this->searchEdge(id)) {
        Edge* aux = this->first_edge;
        Edge* previous = nullptr;
        
        while(aux->getTargetId() != id) {
            previous = aux;
            aux = aux->getNextEdge();
        }
        
        if(previous != nullptr)
            previous->setNextEdge(aux->getNextEdge());
        else
            this->first_edge = aux->getNextEdge();
        
        if(aux == this->last_edge)
            this->last_edge = previous;
        
        if(aux->getNextEdge() == this->last_edge)
            this->last_edge = aux->getNextEdge();
        
        delete aux;
        
        if(directed)
            this->decrementOutDegree();
        else {
            this->decrementInDegree();
            if(target_node != nullptr)
                target_node->decrementInDegree();
        }
        return 1;
    }
    return 0;
}

bool Node::searchEdge(int target_id) const {
    if(this->first_edge != nullptr) {
        for(Edge* aux = this->first_edge; aux != nullptr; aux = aux->getNextEdge()) {
            if(aux->getTargetId() == target_id)
                return true;
        }
    }
    return false;
}

Edge* Node::hasEdgeBetween(int target_id) const {
    for(Edge* auxEdge = this->first_edge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()) {
        if(auxEdge->getTargetId() == target_id)
            return auxEdge;
    }
    return nullptr;
}

// Degree operations
void Node::incrementInDegree() {
    this->in_degree++;
}

void Node::incrementOutDegree() {
    this->out_degree++;
}

void Node::decrementInDegree() {
    if(this->in_degree > 0)
        this->in_degree--;
}

void Node::decrementOutDegree() {
    if(this->out_degree > 0)
        this->out_degree--;
}

} // namespace GraphLib

