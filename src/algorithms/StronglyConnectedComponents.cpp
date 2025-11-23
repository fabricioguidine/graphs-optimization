/**************************************************************************************************
 * Implementation of Kosaraju's Algorithm for Strongly Connected Components
**************************************************************************************************/

#include "../../include/algorithms/StronglyConnectedComponents.h"
#include "../../include/Graph.h"
#include "../../include/Node.h"
#include "../../include/Edge.h"
#include <vector>
#include <stack>
#include <algorithm>

namespace GraphLib {

std::vector<std::vector<int>> StronglyConnectedComponents::findSCC(Graph* graph) {
    std::vector<std::vector<int>> sccs;
    
    if(graph == nullptr || !graph->getDirected()) {
        return sccs;
    }
    
    int order = graph->getOrder();
    std::vector<bool> visited(order + 1, false);
    std::stack<int> finishStack;
    
    // First DFS: fill finish times
    auto dfs1 = [&](int start) {
        std::stack<int> stack;
        stack.push(start);
        
        while(!stack.empty()) {
            int u = stack.top();
            
            if(visited[u]) {
                stack.pop();
                finishStack.push(u);
                continue;
            }
            
            visited[u] = true;
            Node* node = graph->getNode(u);
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
    };
    
    Node* node = graph->getFirstNode();
    while(node != nullptr) {
        if(!visited[node->getId()]) {
            dfs1(node->getId());
        }
        node = node->getNextNode();
    }
    
    // Get transpose graph
    Graph* transpose = graph->getSubjacent();
    if(transpose == nullptr) {
        return sccs;
    }
    
    // Second DFS: process in reverse order of finish times
    std::fill(visited.begin(), visited.end(), false);
    
    while(!finishStack.empty()) {
        int u = finishStack.top();
        finishStack.pop();
        
        if(!visited[u]) {
            std::vector<int> component;
            std::stack<int> stack;
            stack.push(u);
            
            while(!stack.empty()) {
                int v = stack.top();
                stack.pop();
                
                if(visited[v]) continue;
                visited[v] = true;
                component.push_back(v);
                
                Node* n = transpose->getNode(v);
                if(n != nullptr) {
                    Edge* edge = n->getFirstEdge();
                    while(edge != nullptr) {
                        if(!visited[edge->getTargetId()]) {
                            stack.push(edge->getTargetId());
                        }
                        edge = edge->getNextEdge();
                    }
                }
            }
            
            if(!component.empty()) {
                sccs.push_back(component);
            }
        }
    }
    
    delete transpose;
    return sccs;
}

int StronglyConnectedComponents::getSCCCount(Graph* graph) {
    std::vector<std::vector<int>> sccs = findSCC(graph);
    return sccs.size();
}

} // namespace GraphLib

