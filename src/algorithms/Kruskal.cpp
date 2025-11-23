/**************************************************************************************************
 * Implementation of Kruskal's Algorithm
**************************************************************************************************/

#include "../../include/algorithms/Kruskal.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <vector>
#include <algorithm>
#include <limits>

namespace GraphLib {

// Union-Find implementation
Kruskal::UnionFind::UnionFind(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 0);
    for(int i = 0; i <= n; i++) {
        parent[i] = i;
    }
}

int Kruskal::UnionFind::find(int x) {
    if(parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void Kruskal::UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if(rootX == rootY) return;
    
    // Union by rank
    if(rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if(rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

bool Kruskal::UnionFind::same(int x, int y) {
    return find(x) == find(y);
}

std::vector<std::pair<int, int>> Kruskal::minimumSpanningTree(Graph* graph) {
    std::vector<std::pair<int, int>> mst;
    
    if(graph == nullptr || graph->getFirstNode() == nullptr) {
        return mst;
    }
    
    if(graph->getDirected()) {
        // Kruskal's algorithm is for undirected graphs
        return mst;
    }
    
    // Collect all edges
    struct EdgeInfo {
        int u, v;
        float weight;
    };
    
    std::vector<EdgeInfo> edges;
    
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        Edge* edge = node->getFirstEdge();
        while(edge != nullptr) {
            int u = node->getId();
            int v = edge->getTargetId();
            // Only add edge once (since graph is undirected)
            if(u < v) {
                float weight = graph->getWeightedEdge() ? edge->getWeight() : 1.0f;
                edges.push_back({u, v, weight});
            }
            edge = edge->getNextEdge();
        }
        node = node->getNextNode();
    }
    
    // Sort edges by weight
    std::sort(edges.begin(), edges.end(), 
              [](const EdgeInfo& a, const EdgeInfo& b) {
                  return a.weight < b.weight;
              });
    
    // Kruskal's algorithm
    UnionFind uf(graph->getOrder());
    
    for(const auto& e : edges) {
        if(!uf.same(e.u, e.v)) {
            uf.unite(e.u, e.v);
            mst.push_back({e.u, e.v});
        }
    }
    
    return mst;
}

float Kruskal::getMSTWeight(Graph* graph) {
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

