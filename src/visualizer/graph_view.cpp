#include "visualizer/graph_view.h"

GraphView::GraphView(double window_size, double margin) : kWindowSize(window_size), kMargin(margin),
                                                          kDefaultColor(ci::Color("orange")),
                                                          kFontColor(ci::Color("black")),
                                                          kDefaultRadius(30) {
}

void GraphView::Draw(const Graph &visualized_graph) {
    ci::gl::clear();
    DrawEdges(visualized_graph);
    DrawNodes(visualized_graph);
}

void GraphView::MoveNode(Graph *visualized_graph, vec2 new_location) {
    if (IsOutOfBounds(new_location)) {
        return;
    }

    //check every node to see if it is at the location passed in and change its value
    for (auto &target_node : visualized_graph->GetNodes()) {
        if (glm::distance(new_location, target_node.GetLocation()) <= kDefaultRadius) {
            //ensures that two nodes don't overlap
            if (!TouchesOtherNodes(visualized_graph, target_node, new_location)) {
                visualized_graph->SetLocation(target_node, new_location);
            }
        }
    }
}

bool GraphView::TouchesOtherNodes(Graph *visualized_graph, Node current_node, vec2 current_location) const {
    //checks every node in the graph (aside from the current node) to see if any overlaps with the current node
    for (auto &target_node: visualized_graph->GetNodes()) {
        if(target_node == current_node) {
            continue;
        }
        if (glm::distance(current_location, target_node.GetLocation()) <= 2 * kDefaultRadius) {
            return true;
        }
    }
    return false;
}

void GraphView::DrawNodes(Graph visualized_graph) {
    for (auto &target_node : visualized_graph.GetNodes()) {
        ci::gl::color(target_node.GetColor());
        ci::gl::drawSolidCircle(target_node.GetLocation(), kDefaultRadius);
        DrawLabel(target_node);
    }
}

void GraphView::DrawEdges(Graph visualized_graph) {
    //for every node, draw a line to the location of every adjacent nodes
    for (auto &current_node : visualized_graph.GetNodes()) {
        for (auto &adjacent_edge : visualized_graph.GetAdjacentNodes(current_node)) {
            ci::gl::color(adjacent_edge.GetEdgeColor());
            ci::gl::lineWidth(5);
            ci::gl::drawLine(current_node.GetLocation(), adjacent_edge.GetEndNode()->GetLocation());
        }
    }
}

void GraphView::DrawLabel(const Node &target_node) {
    vec2 location = target_node.GetLocation();
    location[0] = location[0] - kDefaultRadius / 2;
    location[1] = location[1] - kDefaultRadius / 2;
    ci::gl::drawString(std::to_string(target_node.GetValue()), location, kFontColor,
                       ci::Font("Times New Roman", 40));
}

bool GraphView::IsOutOfBounds(vec2 location) const {
    float x = location[0];
    float y = location[1];
    return x >= kWindowSize - kMargin || y >= kWindowSize - kMargin || x <= kMargin || y <= kMargin;
}