/**************************************************************************************************
 * Implementation of Graph methods
**************************************************************************************************/

#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

namespace GraphLib {

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node) {
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph() {
    Node* next_node = this->first_node;
    while(next_node != nullptr) {
        next_node->removeAllEdges();
        Node* aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder() const {
    return this->order;
}

int Graph::getNumberEdges() const {
    return this->number_edges;
}

bool Graph::getDirected() const {
    return this->directed;
}

bool Graph::getWeightedEdge() const {
    return this->weighted_edge;
}

bool Graph::getWeightedNode() const {
    return this->weighted_node;
}

Node* Graph::getFirstNode() const {
    return this->first_node;
}

Node* Graph::getLastNode() const {
    return this->last_node;
}

// Node operations
void Graph::insertNode(int id) {
    if(!this->searchNode(id)) {
        Node* node = new Node(id);
        if(this->first_node == nullptr) {
            this->first_node = this->last_node = node;
        } else {
            this->last_node->setNextNode(node);
            this->last_node = node;
        }
    }
}

void Graph::removeNode(int id) {
    if(this->searchNode(id)) {
        Node* node = this->getNode(id);
        Node* previous = nullptr;
        Node* current = this->first_node;
        
        // Find the node and its previous
        while(current != nullptr && current->getId() != id) {
            previous = current;
            current = current->getNextNode();
        }
        
        if(current != nullptr) {
            // Remove all edges connected to this node
            Node* aux = this->first_node;
            while(aux != nullptr) {
                if(aux->getId() != id) {
                    aux->removeEdge(id, this->directed, node);
                }
                aux = aux->getNextNode();
            }
            
            // Remove the node from the list
            if(previous != nullptr) {
                previous->setNextNode(current->getNextNode());
            } else {
                this->first_node = current->getNextNode();
            }
            
            if(current == this->last_node) {
                this->last_node = previous;
            }
            
            current->removeAllEdges();
            delete current;
        }
    }
}

bool Graph::searchNode(int id) const {
    Node* node = this->first_node;
    while(node != nullptr) {
        if(node->getId() == id)
            return true;
        node = node->getNextNode();
    }
    return false;
}

Node* Graph::getNode(int id) const {
    Node* node = this->first_node;
    while(node != nullptr) {
        if(node->getId() == id)
            return node;
        node = node->getNextNode();
    }
    return nullptr;
}

// Edge operations
void Graph::insertEdge(int id, int target_id, float weight) {
    if(!this->searchNode(id))
        this->insertNode(id);
    if(!this->searchNode(target_id))
        this->insertNode(target_id);
    
    Node* source_node = this->getNode(id);
    Node* target_node = this->getNode(target_id);
    
    if(source_node != nullptr && !source_node->searchEdge(target_id)) {
        source_node->insertEdge(target_id, weight);
        source_node->incrementOutDegree();
        target_node->incrementInDegree();
        this->number_edges++;
        
        if(!this->directed && !target_node->searchEdge(id)) {
            target_node->insertEdge(id, weight);
            target_node->incrementOutDegree();
            source_node->incrementInDegree();
        }
    }
}

// Graph analysis
bool Graph::depthFirstSearch(int initialId, int targetId) const {
    if(!this->searchNode(initialId) || !this->searchNode(targetId))
        return false;
    
    std::vector<bool> visited(this->order + 1, false);
    std::stack<int> stack;
    stack.push(initialId);
    
    while(!stack.empty()) {
        int current = stack.top();
        stack.pop();
        
        if(current == targetId)
            return true;
        
        if(!visited[current]) {
            visited[current] = true;
            Node* node = this->getNode(current);
            if(node != nullptr) {
                Edge* edge = node->getFirstEdge();
                while(edge != nullptr) {
                    if(!visited[edge->getTargetId()]) {
                        stack.push(edge->getTargetId());
                    }
                    edge = edge->getNextEdge();
                }
            }
        }
    }
    return false;
}

void Graph::breadthFirstSearch(std::ofstream& output_file) const {
    if(this->first_node == nullptr)
        return;
    
    std::vector<bool> visited(this->order + 1, false);
    std::queue<int> queue;
    
    Node* start = this->first_node;
    queue.push(start->getId());
    visited[start->getId()] = true;
    
    while(!queue.empty()) {
        int current = queue.front();
        queue.pop();
        output_file << current << " ";
        
        Node* node = this->getNode(current);
        if(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                if(!visited[edge->getTargetId()]) {
                    visited[edge->getTargetId()] = true;
                    queue.push(edge->getTargetId());
                }
                edge = edge->getNextEdge();
            }
        }
    }
    output_file << std::endl;
}

Graph* Graph::getComplement() const {
    Graph* complement = new Graph(this->order, this->directed, 
                                   this->weighted_edge, this->weighted_node);
    
    // Insert all nodes
    Node* node = this->first_node;
    while(node != nullptr) {
        complement->insertNode(node->getId());
        node = node->getNextNode();
    }
    
    // Add edges that don't exist in the original graph
    node = this->first_node;
    while(node != nullptr) {
        Node* other_node = this->first_node;
        while(other_node != nullptr) {
            if(node->getId() != other_node->getId()) {
                if(!node->searchEdge(other_node->getId())) {
                    complement->insertEdge(node->getId(), other_node->getId(), 0);
                }
            }
            other_node = other_node->getNextNode();
        }
        node = node->getNextNode();
    }
    
    return complement;
}

Graph* Graph::getSubjacent() const {
    if(!this->directed)
        return nullptr;
    
    Graph* subjacent = new Graph(this->order, false, this->weighted_edge, this->weighted_node);
    
    // Insert all nodes
    Node* node = this->first_node;
    while(node != nullptr) {
        subjacent->insertNode(node->getId());
        node = node->getNextNode();
    }
    
    // Add edges in both directions
    node = this->first_node;
    while(node != nullptr) {
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            subjacent->insertEdge(node->getId(), edge->getTargetId(), edge->getWeight());
            subjacent->insertEdge(edge->getTargetId(), node->getId(), edge->getWeight());
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    
    return subjacent;
}

bool Graph::hasCircuit() const {
    if(!this->directed) {
        // For undirected graphs, check if there are cycles using DFS
        std::vector<bool> visited(this->order + 1, false);
        Node* start = this->first_node;
        if(start == nullptr) return false;
        
        std::stack<std::pair<int, int>> stack; // (current, parent)
        stack.push({start->getId(), -1});
        
        while(!stack.empty()) {
            auto [current, parent] = stack.top();
            stack.pop();
            
            if(visited[current])
                return true;
            
            visited[current] = true;
            Node* node = this->getNode(current);
            if(node != nullptr) {
                Edge* edge = node->getFirstEdge();
                while(edge != nullptr) {
                    if(edge->getTargetId() != parent) {
                        if(visited[edge->getTargetId()])
                            return true;
                        stack.push({edge->getTargetId(), current});
                    }
                    edge = edge->getNextEdge();
                }
            }
        }
    } else {
        // For directed graphs, use DFS to detect back edges
        std::vector<int> color(this->order + 1, 0); // 0=white, 1=gray, 2=black
        
        Node* node = this->first_node;
        while(node != nullptr) {
            if(color[node->getId()] == 0) {
                std::stack<int> stack;
                stack.push(node->getId());
                
                while(!stack.empty()) {
                    int current = stack.top();
                    
                    if(color[current] == 0) {
                        color[current] = 1; // gray
                        Node* n = this->getNode(current);
                        if(n != nullptr) {
                            Edge* edge = n->getFirstEdge();
                            while(edge != nullptr) {
                                if(color[edge->getTargetId()] == 1)
                                    return true; // back edge found
                                if(color[edge->getTargetId()] == 0)
                                    stack.push(edge->getTargetId());
                                edge = edge->getNextEdge();
                            }
                        }
                    } else {
                        color[current] = 2; // black
                        stack.pop();
                    }
                }
            }
            node = node->getNextNode();
        }
    }
    return false;
}

bool Graph::connectedGraph() const {
    if(this->first_node == nullptr)
        return false;
    
    std::vector<bool> visited(this->order + 1, false);
    std::queue<int> queue;
    
    Node* start = this->first_node;
    queue.push(start->getId());
    visited[start->getId()] = true;
    int count = 1;
    
    while(!queue.empty()) {
        int current = queue.front();
        queue.pop();
        
        Node* node = this->getNode(current);
        if(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                if(!visited[edge->getTargetId()]) {
                    visited[edge->getTargetId()] = true;
                    queue.push(edge->getTargetId());
                    count++;
                }
                edge = edge->getNextEdge();
            }
        }
    }
    
    return count == this->order;
}

// Output
void Graph::printGraph() const {
    Node* node = this->first_node;
    while(node != nullptr) {
        std::cout << "Node " << node->getId() << ": ";
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            std::cout << "->" << edge->getTargetId();
            if(this->weighted_edge)
                std::cout << "(" << edge->getWeight() << ")";
            std::cout << " ";
            edge = edge->getNextEdge();
        }
        std::cout << std::endl;
        node = node->getNextNode();
    }
}

void Graph::generateOutput(const std::string& filename) const {
    std::ofstream file(filename);
    if(file.is_open()) {
        file << this->order << std::endl;
        Node* node = this->first_node;
        while(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                file << node->getId() << " " << edge->getTargetId();
                if(this->weighted_edge)
                    file << " " << edge->getWeight();
                file << std::endl;
                edge = edge->getNextEdge();
            }
            node = node->getNextNode();
        }
        file.close();
    }
}

} // namespace GraphLib

