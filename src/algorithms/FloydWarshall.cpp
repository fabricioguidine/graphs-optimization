/**************************************************************************************************
 * Implementation of Floyd-Warshall Algorithm
**************************************************************************************************/

#include "../../include/algorithms/FloydWarshall.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <vector>
#include <limits>
#include <algorithm>

namespace GraphLib {

std::vector<std::vector<float>> FloydWarshall::allPairsShortestPath(Graph* graph) {
    if(graph == nullptr) {
        return std::vector<std::vector<float>>();
    }
    
    int order = graph->getOrder();
    std::vector<std::vector<float>> dist(order + 1, 
                                         std::vector<float>(order + 1, 
                                         std::numeric_limits<float>::max()));
    std::vector<std::vector<int>> next(order + 1, 
                                      std::vector<int>(order + 1, -1));
    
    // Initialize distances
    for(int i = 1; i <= order; i++) {
        dist[i][i] = 0;
    }
    
    // Initialize with direct edges
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            int u = node->getId();
            int v = edge->getTargetId();
            float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
            
            dist[u][v] = weight;
            next[u][v] = v;
            
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    
    // Floyd-Warshall algorithm
    for(int k = 1; k <= order; k++) {
        for(int i = 1; i <= order; i++) {
            for(int j = 1; j <= order; j++) {
                if(dist[i][k] != std::numeric_limits<float>::max() && 
                   dist[k][j] != std::numeric_limits<float>::max()) {
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
    
    return dist;
}

float FloydWarshall::getDistance(Graph* graph, int sourceId, int targetId) {
    std::vector<std::vector<float>> dist = allPairsShortestPath(graph);
    if(sourceId < dist.size() && targetId < dist[sourceId].size()) {
        return dist[sourceId][targetId] == std::numeric_limits<float>::max() ? -1 : 
               dist[sourceId][targetId];
    }
    return -1;
}

std::vector<int> FloydWarshall::getPath(Graph* graph, int sourceId, int targetId) {
    if(graph == nullptr || !graph->searchNode(sourceId) || !graph->searchNode(targetId)) {
        return std::vector<int>();
    }
    
    int order = graph->getOrder();
    std::vector<std::vector<float>> dist(order + 1, 
                                         std::vector<float>(order + 1, 
                                         std::numeric_limits<float>::max()));
    std::vector<std::vector<int>> next(order + 1, 
                                      std::vector<int>(order + 1, -1));
    
    // Initialize
    for(int i = 1; i <= order; i++) {
        dist[i][i] = 0;
    }
    
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            int u = node->getId();
            int v = edge->getTargetId();
            float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
            
            dist[u][v] = weight;
            next[u][v] = v;
            
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    
    // Floyd-Warshall
    for(int k = 1; k <= order; k++) {
        for(int i = 1; i <= order; i++) {
            for(int j = 1; j <= order; j++) {
                if(dist[i][k] != std::numeric_limits<float>::max() && 
                   dist[k][j] != std::numeric_limits<float>::max()) {
                    if(dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
    
    // Reconstruct path
    std::vector<int> path;
    if(next[sourceId][targetId] == -1) {
        return path; // No path exists
    }
    
    path.push_back(sourceId);
    int u = sourceId;
    while(u != targetId) {
        u = next[u][targetId];
        path.push_back(u);
    }
    
    return path;
}

} // namespace GraphLib

