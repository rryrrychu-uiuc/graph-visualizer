#include "visualizer/shortest_path_algorithms.h"
#include <queue>

using std::priority_queue;

ShortestPath::ShortestPath() {

}

ShortestPath::ShortestPath(Graph *target_graph, Node starting_node, Node ending_node) {
    InitalizeValues(target_graph, starting_node, ending_node);
}

void ShortestPath::InitalizeValues(Graph* target_graph, Node starting_node, Node ending_node) {
    ResetClass();
    target_graph_ = target_graph;
    previous_nodes_ = vector<Node>(target_graph->GetNodes().size());
    starting_node_ = starting_node;
    ending_node_ = ending_node;
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
        if(previous_node_.GetValue() != -1) {
            target_graph_->SetNodeColor(previous_node_, ci::Color("orange"));
        }
        return true;
    }
    
    if(previous_node_.GetValue() != -1) {
        target_graph_->SetNodeColor(previous_node_, ci::Color("orange"));
        target_graph_->SetEdgeColor(starting_node_, previous_node_, ci::Color("blue"));
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
    previous_node_ = starting_node_;
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
    if (new_distance <= distances_[node_index]) {
        distances_[node_index] = new_distance;
        previous_nodes_[node_index] = starting_node_;
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

void ShortestPath::ResetClass() {
    visited_nodes_.clear();
    unvisited_nodes_.clear();
    distances_.clear();
    previous_nodes_.clear();
    starting_index_ = 0;
    ending_index_ = 0;
}

void ShortestPath::ColorShortestPath() {
    
    int build_edge_loc = ending_index_;
    Node previous_node = ending_node_;
    while(previous_nodes_[build_edge_loc].GetValue() != -1) {
        Node to_edge = previous_nodes_[build_edge_loc];
        target_graph_->SetEdgeColor(previous_node, to_edge, ci::Color("yellow"));
        previous_node = to_edge;
        build_edge_loc = IndexOfNode(previous_node);
    }
}

vector<Node> ShortestPath::GetUnvisitedNodes() {
    return unvisited_nodes_;
}

vector<Node> ShortestPath::GetVisitedNodes() {
    return visited_nodes_;
}

vector<Node> ShortestPath::GetPreviousNodes() {
    return previous_nodes_;
}

vector<int> ShortestPath::GetDistances() {
    return distances_;
}

Node ShortestPath::GetStartingNode() {
    return starting_node_;
}



