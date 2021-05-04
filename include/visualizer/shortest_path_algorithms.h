#pragma once
#ifndef FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H
#define FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H

#include "core/graph.h"

using namespace graph;

class ShortestPath {
public:
    ShortestPath(Graph* target_graph, Node starting_node, Node ending_node);
    
    bool RunSingleStepDijkstra();
    
private:
    Graph* target_graph_;
    Node starting_node_;
    Node ending_node_;
    
    vector<Node> visited_nodes;
    vector<Node> unvisited_nodes;
};


#endif //FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H
