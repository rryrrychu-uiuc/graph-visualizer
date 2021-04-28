#pragma once
#ifndef FINAL_PROJECT_GRAPH_EDITOR_H
#define FINAL_PROJECT_GRAPH_EDITOR_H

#include "core/graph.h"

using namespace graph;

class GraphEditor {
public:
    
    explicit GraphEditor(float radius);
    
    void CreateNode(Graph *target_graph, vec2 location);
    
    void CreateEdge(Graph *target_graph, vec2 location);
    
    void DeleteNode(Graph *target_graph, vec2 location);
    
    Node GetNodeAtLocation(Graph *target_graph, vec2 location);
    
    bool NodeExistsInGraph(Node test_node);
    
    void clear();
    
private:
    const float kDefaultRadius;
    vector<Node> nodes_to_bridge;

};


#endif //FINAL_PROJECT_GRAPH_EDITOR_H
