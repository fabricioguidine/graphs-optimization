/**************************************************************************************************
 * Implementation of Dijkstra's Algorithm
**************************************************************************************************/

#include "../../include/algorithms/Dijkstra.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

namespace GraphLib {

std::vector<float> Dijkstra::shortestPath(Graph* graph, int sourceId) {
    if(graph == nullptr || !graph->searchNode(sourceId)) {
        return std::vector<float>();
    }
    
    int order = graph->getOrder();
    std::vector<float> distances(order + 1, std::numeric_limits<float>::max());
    std::vector<bool> visited(order + 1, false);
    
    // Priority queue: (distance, node_id)
    std::priority_queue<std::pair<float, int>, 
                       std::vector<std::pair<float, int>>, 
                       std::greater<std::pair<float, int>>> pq;
    
    distances[sourceId] = 0;
    pq.push({0, sourceId});
    
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if(visited[u]) continue;
        visited[u] = true;
        
        Node* node = graph->getNode(u);
        if(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                int v = edge->getTargetId();
                float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
                
                if(!visited[v] && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push({distances[v], v});
                }
                edge = edge->getNextEdge();
            }
        }
    }
    
    return distances;
}

std::vector<int> Dijkstra::shortestPathTo(Graph* graph, int sourceId, int targetId) {
    if(graph == nullptr || !graph->searchNode(sourceId) || !graph->searchNode(targetId)) {
        return std::vector<int>();
    }
    
    int order = graph->getOrder();
    std::vector<float> distances(order + 1, std::numeric_limits<float>::max());
    std::vector<int> previous(order + 1, -1);
    std::vector<bool> visited(order + 1, false);
    
    std::priority_queue<std::pair<float, int>, 
                       std::vector<std::pair<float, int>>, 
                       std::greater<std::pair<float, int>>> pq;
    
    distances[sourceId] = 0;
    pq.push({0, sourceId});
    
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if(visited[u]) continue;
        visited[u] = true;
        
        if(u == targetId) break;
        
        Node* node = graph->getNode(u);
        if(node != nullptr) {
            Edge* edge = node->getFirstEdge();
            while(edge != nullptr) {
                int v = edge->getTargetId();
                float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
                
                if(!visited[v] && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                    pq.push({distances[v], v});
                }
                edge = edge->getNextEdge();
            }
        }
    }
    
    // Reconstruct path
    std::vector<int> path;
    if(distances[targetId] != std::numeric_limits<float>::max()) {
        int current = targetId;
        while(current != -1) {
            path.push_back(current);
            current = previous[current];
        }
        std::reverse(path.begin(), path.end());
    }
    
    return path;
}

float Dijkstra::getDistance(Graph* graph, int sourceId, int targetId) {
    std::vector<float> distances = shortestPath(graph, sourceId);
    if(targetId < distances.size()) {
        return distances[targetId] == std::numeric_limits<float>::max() ? -1 : distances[targetId];
    }
    return -1;
}

} // namespace GraphLib

