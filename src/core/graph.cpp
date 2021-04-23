#include "../../include/core/graph.h"

namespace graph {
    
Graph::Graph() {
    nodes.reserve(100);    
}
    
vector<Node> Graph::GetNodes() {
    return nodes;
}

void Graph::AddNode(Node target_node) {
    nodes.push_back(target_node);
}

void Graph::AddEdge(int start_node, int end_node, bool single_direction) {
    
    nodes[start_node].AddAdjacentNode(&nodes[end_node]);
    
    if(!single_direction) {
        nodes[end_node].AddAdjacentNode(&nodes[start_node]);
    }
}

void Graph::SetLocation(size_t index, vec2 location) {
    nodes[index].SetLocation(location);
}

void Graph::ClearGraph() {
    nodes.clear();
}
}
