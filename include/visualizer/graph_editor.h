#pragma once
#ifndef FINAL_PROJECT_GRAPH_EDITOR_H
#define FINAL_PROJECT_GRAPH_EDITOR_H

#include "core/graph.h"

using namespace graph;

class GraphEditor {
public:
    
    explicit GraphEditor(float radius, double window_size, double margin);
    
    /**
     * Add a node to the graph with the GUI
     */
    void CreateNode(Graph *target_graph, vec2 location);

    /**
    * Add an edge to the graph with the GUI
    */
    void CreateEdge(Graph *target_graph, vec2 location);

    /**
    * Delete a node to the graph with the GUI
    */
    void DeleteNode(Graph *target_graph, vec2 location);

    /**
    * Delete an edge to the graph with the GUI
    */
    void DeleteEdge(Graph *target_graph, vec2 location);

    /**
    * Select two nodes
    */    
    void MarkNode(Graph *target_graph, vec2 location);

    /**
    * Get the node at a certain location
    */
    Node GetNodeAtLocation(Graph *target_graph, vec2 location) const;

    /**
    * Check if a node exists in the graph
    */    
    bool NodeExistsInGraph(const Node& test_node);

    /**
    * Check if location in bounds of GUI
    */
    bool IsOutOfBounds(vec2 location) const;
    
    vector<Node> GetNodes();
    
    std::string GetVectorValues() const;
    
    bool empty();
    
    size_t size();
    
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
