#include "visualizer/shortest_path_algorithms.h"
#include <queue>

using std::priority_queue;

ShortestPath::ShortestPath(Graph *target_graph, Node starting_node, Node ending_node) :
    target_graph_(target_graph),
    previous_node_(target_graph->GetNodes().size()),
    starting_node_(starting_node),
    ending_node_(ending_node) {
    
    unvisited_nodes_ = target_graph->GetNodes();
    for (size_t index = 0; index < unvisited_nodes_.size(); index++) {
        distances_.push_back(std::numeric_limits<int>::max());
    }

    starting_index_ = IndexOfNode(starting_node);
    ending_index_ = IndexOfNode(ending_node);
    distances_[starting_index_] = 0;
}

bool ShortestPath::RunSingleStepDijkstra() {
    if (unvisited_nodes_.size() == 0) {
        return true;
    }
    
    if(previous_node_[starting_index_].GetValue() != -1) {
        target_graph_->SetNodeColor(previous_node_[starting_index_], ci::Color("orange"));
    }
    target_graph_->SetNodeColor(starting_node_, ci::Color(50, 205, 50));
    
    for (auto &adjacent_edge: target_graph_->GetAdjacentNodes(starting_node_)) {
        if(IsVisited(*adjacent_edge.GetEndNode())) {
            continue;
        }
        
        ChangeDistances(adjacent_edge);
    }

    MoveNodeToVisited(starting_node_);
    Node new_starting_node = GetSmallestEdge();
    target_graph_->SetEdgeColor(starting_node_, new_starting_node, ci::Color("red"));
    starting_node_ = new_starting_node;
    starting_index_ = IndexOfNode(starting_node_);
    return false;
}

void ShortestPath::RunEntireAlgorithm() {
    while(!RunSingleStepDijkstra()) {
        
    }
}

void ShortestPath::ChangeDistances(Edge target_edge) {
    int node_index = IndexOfNode(*target_edge.GetEndNode());
    int new_distance = distances_[starting_index_] + target_edge.GetWeight();
    if (new_distance < distances_[node_index]) {
        distances_[node_index] = new_distance;
        previous_node_[node_index] = starting_node_;
    }
}

Node ShortestPath::GetSmallestEdge() {

    Node next_starting_node;
    int min_distance = std::numeric_limits<int>::max();
    size_t index = 0;
    for (auto &distance: distances_) {
        if (distance < min_distance) {
            if (!IsVisited(target_graph_->GetNodes().at(index))) {
                min_distance = distance;
                next_starting_node = target_graph_->GetNodes().at(index);
            }
        }
        index++;
    }

    return next_starting_node;
}

bool ShortestPath::IsVisited(Node target_node) {
    for (auto &visited_node: visited_nodes_) {
        if (target_node == visited_node) {
            return true;
        }
    }
    return false;
}

int ShortestPath::IndexOfNode(Node target_node) {
    int index = 0;
    for (auto &node: target_graph_->GetNodes()) {
        if (target_node == node) {
            return index;
        }
        index++;
    }

    return -1;
}

void ShortestPath::MoveNodeToVisited(Node target_node) {
    vector<Node> new_unvisited;
    for (auto &unvisited_node: unvisited_nodes_) {
        if (target_node == unvisited_node) {
            continue;
        }
        new_unvisited.push_back(unvisited_node);
    }

    unvisited_nodes_ = new_unvisited;
    visited_nodes_.push_back(target_node);
}

vector<Node> ShortestPath::GetUnvisitedNodes() {
    return unvisited_nodes_;
}

vector<Node> ShortestPath::GetVisitedNodes() {
    return visited_nodes_;
}

vector<Node> ShortestPath::GetPreviousNodes() {
    return previous_node_;
}

vector<int> ShortestPath::GetDistances() {
    return distances_;
}

Node ShortestPath::GetStartingNode() {
    return starting_node_;
}

