#include "visualizer/graph_editor.h"

GraphEditor::GraphEditor(float radius): kDefaultRadius(radius) {
    
}

void GraphEditor::CreateNode(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if(NodeExistsInGraph(target_node)) {
        return;
    }
    
    Node newNode(-1, vec2(location));
    target_graph->AddNode(newNode);
}

void GraphEditor::CreateEdge(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if(!NodeExistsInGraph(target_node)) {
        return;
    }
    
    if(!nodes_to_bridge.empty() && target_node == nodes_to_bridge[0]) {
        return;
    }
    
    if(nodes_to_bridge.empty()) {
        nodes_to_bridge.push_back(target_node);
    } else {
        if(!target_graph->EdgeExists(nodes_to_bridge[0], target_node)) {
            target_graph->AddEdge(&nodes_to_bridge[0], &target_node, false);
        }
        nodes_to_bridge.clear();
    }
}

void GraphEditor::DeleteNode(Graph *target_graph, vec2 location) {
    Node target_node = GetNodeAtLocation(target_graph, location);
    if(!NodeExistsInGraph(target_node)) {
        return;
    }
    
    target_graph->DeleteNode(target_node);
}

Node GraphEditor::GetNodeAtLocation(Graph *target_graph, vec2 location) {
    Node target_node;
    for(auto& to_check: target_graph->GetNodes()) {
        if(glm::distance(to_check.GetLocation(), location) <= 2*kDefaultRadius) {
            target_node = to_check;
        }
    }
    return target_node;
}

bool GraphEditor::NodeExistsInGraph(Node test_node) {
    return test_node.GetLocation() != vec2(-1,-1) && test_node.GetValue() != -1;
}

void GraphEditor::clear() {
    nodes_to_bridge.clear();
}

