#include "visualizer/graph_editor.h"
#include <random>

GraphEditor::GraphEditor(float radius, double window_size, double margin) : kDefaultRadius(radius), kMaxNodeValue(99),
                                                                            kMinNodeValue(1), kWindowSize(window_size),
                                                                            kMargin(margin) {}

void GraphEditor::CreateNode(Graph *target_graph, vec2 location) {
    if(IsOutOfBounds(location)) {
        return; 
    }
    
    Node target_node = GetNodeAtLocation(target_graph, location);
    if (NodeExistsInGraph(target_node)) {
        return;
    }

    //Code reference: https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 99);
    
    Node newNode(dist(mt) % kMaxNodeValue + kMinNodeValue, vec2(location));
    target_graph->AddNode(newNode);
}

void GraphEditor::CreateEdge(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if (!NodeExistsInGraph(target_node)) {
        return;
    }

    //checks to make sure node is not trying to be removed from itself
    if (!nodes_to_bridge.empty() && target_node == nodes_to_bridge[0]) {
        return;
    }

    if (nodes_to_bridge.empty()) {
        nodes_to_bridge.push_back(target_node);
    } else {
        if (!target_graph->EdgeExists(nodes_to_bridge[0], target_node)) {
            target_graph->AddEdge(nodes_to_bridge[0], target_node, false);
        }
        nodes_to_bridge.clear();
    }
}

void GraphEditor::DeleteNode(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if (!NodeExistsInGraph(target_node)) {
        return;
    }

    target_graph->DeleteNode(target_node);
}

void GraphEditor::DeleteEdge(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if (!NodeExistsInGraph(target_node)) {
        return;
    }

    //checks to make sure node is not trying to be removed from itself
    if (!nodes_to_bridge.empty() && target_node == nodes_to_bridge[0]) {
        return;
    }

    if (nodes_to_bridge.empty()) {
        nodes_to_bridge.push_back(target_node);
    } else {
        target_graph->DeleteEdge(&nodes_to_bridge[0], &target_node, false);
        nodes_to_bridge.clear();
    }
}

Node GraphEditor::GetNodeAtLocation(Graph *target_graph, vec2 location) const {
    Node target_node;
    for (auto &to_check: target_graph->GetNodes()) {
        if (glm::distance(to_check.GetLocation(), location) <= 2 * kDefaultRadius) {
            target_node = to_check;
        }
    }
    return target_node;
}

bool GraphEditor::NodeExistsInGraph(const Node& test_node) {
    return test_node.GetLocation() != vec2(-1, -1) && test_node.GetValue() != -1;
}

bool GraphEditor::IsOutOfBounds(vec2 location) const {
    float x = location[0];
    float y = location[1];
    return x >= kWindowSize - kMargin || y >= kWindowSize - kMargin || x <= kMargin || y <= kMargin;
}

std::string GraphEditor::GetVectorValues() const {
    if(nodes_to_bridge.empty()) {
        return "{}";
    } else {
        return "{" + std::to_string(nodes_to_bridge[0].GetValue()) + "}";
    }
}

bool GraphEditor::empty() {
    return nodes_to_bridge.empty();
}

void GraphEditor::clear() {
    nodes_to_bridge.clear();
}
