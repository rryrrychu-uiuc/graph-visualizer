#pragma once
#ifndef FINAL_PROJECT_GRAPH_VIEW_H
#define FINAL_PROJECT_GRAPH_VIEW_H

#include <core/graph.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using graph::Graph;

class GraphView {
public:
    /**
     * Initialize the possible range of locations to draw the graph 
     */
    GraphView(double window_size, double margin);

    /**
     * Draw all of the nodes and edges of a certain graph
     * @param visualized_graph 
     */
    void Draw(const Graph& visualized_graph);

    /**
     * Change the location of a node
     * @param visualized_graph the graph that the node is in 
     * @param new_location the new location of the node
     */
    void MoveNode(Graph* visualized_graph, vec2 new_location);

    /**
     * Checks if two nodes overlap
     */
    bool TouchesOtherNodes(Graph* visualized_graph, Node current_node, vec2 current_location) const;

    /**
     * Draw the nodes of a given graph represented by circles
     */

    void DrawNodes(Graph visualized_graph);

    /**
     * Draw the edges of a given graph represented by lines
     */
    void DrawEdges(Graph visualized_graph);

    /**
     * Write the value of the label on the node
     */
    void DrawLabel(const Node& target_node);

    /**
     * Check if a location is not in the bounds of the GraphView
     */
    bool IsOutOfBounds(vec2 location) const;

private:
    const double kWindowSize;
    const double kMargin;
    const float kDefaultRadius;

    const ci::Color kDefaultColor;
    const ci::Color kFontColor;
};

#endif 
