#pragma once
#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H


#include "node.h"
#include <vector>
using std::vector;

namespace graph {
class Graph {
public:
    /**
     * Returns list of nodes from the graph
     */
    vector<Node> GetNodes();

    /**
     * Add a node to the graph 
     */    
    void AddNode(Node target_node);
    
    /**
     * Add adjacent nodes to a certain node
     * @param start_node node to add adjacent node to 
     * @param end_node node to be added
     * @param single_direction false if both nodes should be added to each other's adjacency list
     */
    void AddEdge(Node* start_node, Node* end_node, bool single_direction);
    
    /**
     * Delete every node from the graph
     */
    void ClearGraph();
    
private:
    vector<Node> nodes;
};
}

#endif //FINAL_PROJECT_GRAPH_H
