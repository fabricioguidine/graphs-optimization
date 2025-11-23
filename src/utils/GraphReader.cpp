/**************************************************************************************************
 * Implementation of Graph Reader
**************************************************************************************************/

#include "../../include/utils/GraphReader.h"
#include "../../include/Graph.h"
#include <fstream>
#include <iostream>

namespace GraphLib {

Graph* GraphReader::readFromFile(const std::string& filename, bool directed, 
                                 bool weightedEdge, bool weightedNode) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }
    
    int order;
    file >> order;
    
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);
    
    int idNodeSource, idNodeTarget;
    float edgeWeight;
    
    if(!weightedEdge && !weightedNode) {
        while(file >> idNodeSource >> idNodeTarget) {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    } else if(weightedEdge && !weightedNode) {
        while(file >> idNodeSource >> idNodeTarget >> edgeWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    } else if(weightedNode && !weightedEdge) {
        float nodeSourceWeight, nodeTargetWeight;
        while(file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    } else {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;
        while(file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight >> edgeWeight) {
            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    
    file.close();
    return graph;
}

Graph* GraphReader::readInstance(const std::string& filename, bool directed, 
                                 bool weightedEdge, bool weightedNode) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return nullptr;
    }
    
    int order, numEdges;
    file >> order >> numEdges;
    
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);
    
    int idNodeSource, idNodeTarget;
    while(file >> idNodeSource >> idNodeTarget) {
        graph->insertEdge(idNodeSource, idNodeTarget, 0);
    }
    
    file.close();
    return graph;
}

} // namespace GraphLib

