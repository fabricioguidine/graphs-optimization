/**************************************************************************************************
 * Implementation of Prim's Algorithm
**************************************************************************************************/

#include "../../include/algorithms/Prim.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

namespace GraphLib {

std::vector<std::pair<int, int>> Prim::minimumSpanningTree(Graph* graph) {
    std::vector<std::pair<int, int>> mst;
    
    if(graph == nullptr || graph->getFirstNode() == nullptr) {
        return mst;
    }
    
    if(graph->getDirected()) {
        // Prim's algorithm is for undirected graphs
        return mst;
    }
    
    int order = graph->getOrder();
    std::vector<bool> inMST(order + 1, false);
    std::vector<float> key(order + 1, std::numeric_limits<float>::max());
    std::vector<int> parent(order + 1, -1);
    
    // Priority queue: (weight, (parent, node))
    std::priority_queue<std::pair<float, std::pair<int, int>>, 
                       std::vector<std::pair<float, std::pair<int, int>>>, 
                       std::greater<std::pair<float, std::pair<int, int>>>> pq;
    
    Node* start = graph->getFirstNode();
    if(start == nullptr) return mst;
    
    int startId = start->getId();
    key[startId] = 0;
    pq.push({0, {-1, startId}});
    
    while(!pq.empty()) {
        int u = pq.top().second.second;
        int p = pq.top().second.first;
        pq.pop();
        
        if(inMST[u]) continue;
        inMST[u] = true;
        
        if(p != -1) {
            mst.push_back({p, u});
        }
        
        Node* node = graph->getNode(u);
        if(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                int v = edge->getTargetId();
                float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
                
                if(!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({weight, {u, v}});
                }
                edge = edge->getNextEdge();
            }
        }
    }
    
    return mst;
}

float Prim::getMSTWeight(Graph* graph) {
    std::vector<std::pair<int, int>> mst = minimumSpanningTree(graph);
    float totalWeight = 0.0f;
    
    for(auto& edge : mst) {
        Node* node = graph->getNode(edge.first);
        if(node != nullptr) {
            Edge* e = node->hasEdgeBetween(edge.second);
            if(e != nullptr) {
                totalWeight += graph->getWeightedEdge() ? e->getWeight() : 1.0f;
            }
        }
    }
    
    return totalWeight;
}

} // namespace GraphLib

