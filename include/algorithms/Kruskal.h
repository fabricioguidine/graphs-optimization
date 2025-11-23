/**************************************************************************************************
 * Kruskal's Minimum Spanning Tree Algorithm
 * Finds the minimum spanning tree using union-find data structure
**************************************************************************************************/

#ifndef KRUSKAL_H_INCLUDED
#define KRUSKAL_H_INCLUDED

#include "../Graph.h"
#include <vector>
#include <utility>

namespace GraphLib {

class Kruskal {
private:
    // Union-Find data structure
    class UnionFind {
    private:
        std::vector<int> parent;
        std::vector<int> rank;
        
    public:
        UnionFind(int n);
        int find(int x);
        void unite(int x, int y);
        bool same(int x, int y);
    };

public:
    // Find minimum spanning tree
    static std::vector<std::pair<int, int>> minimumSpanningTree(Graph* graph);
    
    // Get total weight of MST
    static float getMSTWeight(Graph* graph);
};

} // namespace GraphLib

#endif // KRUSKAL_H_INCLUDED

