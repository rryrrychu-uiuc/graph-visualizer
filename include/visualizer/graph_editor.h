#pragma once
#ifndef FINAL_PROJECT_GRAPH_EDITOR_H
#define FINAL_PROJECT_GRAPH_EDITOR_H

#include "core/graph.h"

using namespace graph;

class GraphEditor {
public:
    
    explicit GraphEditor(float radius, double window_size, double margin);
    
    void CreateNode(Graph *target_graph, vec2 location);
    
    void CreateEdge(Graph *target_graph, vec2 location);
    
    void DeleteNode(Graph *target_graph, vec2 location);
    
    void DeleteEdge(Graph *target_graph, vec2 location);
    
    Node GetNodeAtLocation(Graph *target_graph, vec2 location) const;
    
    bool NodeExistsInGraph(const Node& test_node);
    
    bool IsOutOfBounds(vec2 location) const;
    
    std::string GetVectorValues() const;
    
    bool empty();
    
    void clear();
    
private:
    const double kWindowSize;
    const double kMargin;
    
    const int kMaxNodeValue;
    const int kMinNodeValue;
    const float kDefaultRadius;
    vector<Node> nodes_to_bridge;
    
};


#endif //FINAL_PROJECT_GRAPH_EDITOR_H
