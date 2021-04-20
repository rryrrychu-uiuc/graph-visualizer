#pragma once
#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H


#include "node.h"
#include <vector>
using std::vector;

class Graph {
public:
    vector<Node> GetNodes();
    
    void AddNode(Node target_node);
    
    void AddEdge(Node* start_node, Node* end_node, bool single_direction);
    
private:
    vector<Node> nodes;
};


#endif //FINAL_PROJECT_GRAPH_H
