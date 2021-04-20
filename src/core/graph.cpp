//
// Created by rryrr on 4/19/2021.
//

#include "../../include/core/graph.h"

vector<Node> Graph::GetNodes() {
    return nodes;
}

void Graph::AddNode(Node target_node) {
    nodes.push_back(target_node);
}

void Graph::AddEdge(Node* start_node, Node* end_node, bool single_direction) {

    start_node->AddAdjacentNode(end_node);
    
    if(!single_direction) {
        end_node->AddAdjacentNode(start_node);
    }
}


