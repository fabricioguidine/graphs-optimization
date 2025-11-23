/**************************************************************************************************
 * Main Program
 * Graph Algorithms Implementation
**************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../include/Graph.h"
#include "../include/utils/GraphReader.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/FloydWarshall.h"
#include "../include/algorithms/Prim.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/StronglyConnectedComponents.h"
#include "../include/algorithms/TopologicalSort.h"
#include "../include/algorithms/GRASP.h"

using namespace GraphLib;

int menu() {
    int selection;
    std::cout << "\n=== GRAPH ALGORITHMS MENU ===" << std::endl;
    std::cout << "[1]  Graph Complement" << std::endl;
    std::cout << "[2]  Breadth-First Search (BFS)" << std::endl;
    std::cout << "[3]  Depth-First Search (DFS)" << std::endl;
    std::cout << "[4]  Connected Components" << std::endl;
    std::cout << "[5]  Strongly Connected Components" << std::endl;
    std::cout << "[6]  Topological Sort" << std::endl;
    std::cout << "[7]  GRASP Algorithm" << std::endl;
    std::cout << "[8]  Prim's Minimum Spanning Tree" << std::endl;
    std::cout << "[9]  Kruskal's Minimum Spanning Tree" << std::endl;
    std::cout << "[10] Dijkstra's Shortest Path" << std::endl;
    std::cout << "[11] Floyd-Warshall All Pairs Shortest Path" << std::endl;
    std::cout << "[0]  Exit" << std::endl;
    std::cout << "Select option: ";
    std::cin >> selection;
    return selection;
}

void executeAlgorithm(int selection, Graph* graph, std::ofstream& output_file) {
    switch(selection) {
        case 1: { // Complement
            Graph* complement = graph->getComplement();
            output_file << "Graph Complement:" << std::endl;
            complement->printGraph();
            delete complement;
            break;
        }
        
        case 2: { // BFS
            output_file << "Breadth-First Search:" << std::endl;
            graph->breadthFirstSearch(output_file);
            break;
        }
        
        case 3: { // DFS
            int source, target;
            std::cout << "Enter source node: ";
            std::cin >> source;
            std::cout << "Enter target node: ";
            std::cin >> target;
            bool found = graph->depthFirstSearch(source, target);
            output_file << "DFS from " << source << " to " << target << ": " 
                       << (found ? "Path found" : "No path") << std::endl;
            break;
        }
        
        case 4: { // Connected Components
            bool connected = graph->connectedGraph();
            output_file << "Graph is " << (connected ? "connected" : "disconnected") << std::endl;
            break;
        }
        
        case 5: { // Strongly Connected Components
            std::vector<std::vector<int>> sccs = StronglyConnectedComponents::findSCC(graph);
            output_file << "Strongly Connected Components: " << sccs.size() << std::endl;
            for(size_t i = 0; i < sccs.size(); i++) {
                output_file << "SCC " << i + 1 << ": ";
                for(int node : sccs[i]) {
                    output_file << node << " ";
                }
                output_file << std::endl;
            }
            break;
        }
        
        case 6: { // Topological Sort
            std::vector<int> order = TopologicalSort::sort(graph);
            if(order.empty()) {
                output_file << "Graph has cycles - no topological order exists" << std::endl;
            } else {
                output_file << "Topological Order: ";
                for(int node : order) {
                    output_file << node << " ";
                }
                output_file << std::endl;
            }
            break;
        }
        
        case 7: { // GRASP
            std::vector<int> solution = GRASP::solve(graph, 100, 0.3f);
            output_file << "GRASP Solution: ";
            for(int node : solution) {
                output_file << node << " ";
            }
            output_file << std::endl;
            break;
        }
        
        case 8: { // Prim
            std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(graph);
            output_file << "Prim's MST Edges:" << std::endl;
            for(auto& edge : mst) {
                output_file << edge.first << " - " << edge.second << std::endl;
            }
            output_file << "Total Weight: " << Prim::getMSTWeight(graph) << std::endl;
            break;
        }
        
        case 9: { // Kruskal
            std::vector<std::pair<int, int>> mst = Kruskal::minimumSpanningTree(graph);
            output_file << "Kruskal's MST Edges:" << std::endl;
            for(auto& edge : mst) {
                output_file << edge.first << " - " << edge.second << std::endl;
            }
            output_file << "Total Weight: " << Kruskal::getMSTWeight(graph) << std::endl;
            break;
        }
        
        case 10: { // Dijkstra
            int source;
            std::cout << "Enter source node: ";
            std::cin >> source;
            std::vector<float> distances = Dijkstra::shortestPath(graph, source);
            output_file << "Dijkstra distances from node " << source << ":" << std::endl;
            for(size_t i = 1; i < distances.size(); i++) {
                if(distances[i] != std::numeric_limits<float>::max()) {
                    output_file << "Node " << i << ": " << distances[i] << std::endl;
                }
            }
            break;
        }
        
        case 11: { // Floyd-Warshall
            std::vector<std::vector<float>> dist = FloydWarshall::allPairsShortestPath(graph);
            output_file << "Floyd-Warshall All Pairs Shortest Path:" << std::endl;
            for(size_t i = 1; i < dist.size(); i++) {
                for(size_t j = 1; j < dist[i].size(); j++) {
                    if(dist[i][j] != std::numeric_limits<float>::max()) {
                        output_file << "d(" << i << "," << j << ") = " << dist[i][j] << "  ";
                    }
                }
                output_file << std::endl;
            }
            break;
        }
        
        default:
            break;
    }
}

int main(int argc, char const *argv[]) {
    if(argc != 6) {
        std::cout << "Usage: " << argv[0] 
                  << " <input_file> <output_file> <directed> <weighted_edge> <weighted_node>" 
                  << std::endl;
        std::cout << "  directed: 0 (undirected) or 1 (directed)" << std::endl;
        std::cout << "  weighted_edge: 0 (unweighted) or 1 (weighted)" << std::endl;
        std::cout << "  weighted_node: 0 (unweighted) or 1 (weighted)" << std::endl;
        return 1;
    }
    
    std::string input_file_name(argv[1]);
    std::string output_file_name(argv[2]);
    bool directed = (atoi(argv[3]) == 1);
    bool weightedEdge = (atoi(argv[4]) == 1);
    bool weightedNode = (atoi(argv[5]) == 1);
    
    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name, std::ios::trunc);
    
    if(!input_file.is_open()) {
        std::cerr << "Unable to open input file: " << input_file_name << std::endl;
        return 1;
    }
    
    if(!output_file.is_open()) {
        std::cerr << "Unable to open output file: " << output_file_name << std::endl;
        return 1;
    }
    
    Graph* graph = GraphReader::readInstance(input_file_name, directed, weightedEdge, weightedNode);
    
    if(graph == nullptr) {
        std::cerr << "Failed to read graph from file" << std::endl;
        return 1;
    }
    
    int selection = 1;
    while(selection != 0) {
        selection = menu();
        if(selection != 0) {
            executeAlgorithm(selection, graph, output_file);
            output_file << std::endl;
        }
    }
    
    output_file.close();
    input_file.close();
    delete graph;
    
    return 0;
}

