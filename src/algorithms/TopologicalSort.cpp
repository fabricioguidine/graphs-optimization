/**************************************************************************************************
 * Implementation of Topological Sort (Kahn's Algorithm)
**************************************************************************************************/

#include "../../include/algorithms/TopologicalSort.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <vector>
#include <queue>

namespace GraphLib {

std::vector<int> TopologicalSort::sort(Graph* graph) {
    std::vector<int> result;
    
    if(graph == nullptr || !graph->getDirected()) {
        return result;
    }
    
    int order = graph->getOrder();
    std::vector<int> inDegree(order + 1, 0);
    
    // Calculate in-degrees
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            inDegree[edge->getTargetId()]++;
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    
    // Find all nodes with in-degree 0
    std::queue<int> queue;
    for(int i = 1; i <= order; i++) {
        Node* n = graph->getNode(i);
        if(n != nullptr && inDegree[i] == 0) {
            queue.push(i);
        }
    }
    
    // Process nodes
    while(!queue.empty()) {
        int u = queue.front();
        queue.pop();
        result.push_back(u);
        
        Node* n = graph->getNode(u);
        if(n != nullptr) {
            Edge* edge = n->getFirstEdge();
            while(edge != nullptr) {
                int v = edge->getTargetId();
                inDegree[v]--;
                if(inDegree[v] == 0) {
                    queue.push(v);
                }
                edge = edge->getNextEdge();
            }
        }
    }
    
    // If result size != order, there's a cycle
    if(result.size() != order) {
        result.clear();
    }
    
    return result;
}

bool TopologicalSort::hasTopologicalOrder(Graph* graph) {
    std::vector<int> order = sort(graph);
    return order.size() == graph->getOrder();
}

} // namespace GraphLib

