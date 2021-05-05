#include "../../include/core/graph.h"
#include <algorithm>

namespace graph {

    Graph::Graph() : map_size(0) {
    }

    vector<Node> Graph::GetNodes() {
        vector<Node> keys;

        for (auto & graph_mapping : graph_mappings_) {
            keys.push_back(graph_mapping.first);
        }

        return keys;
    }

    vector<Edge> Graph::GetAdjacentNodes(const Node& target_node) {
        return graph_mappings_.at(target_node);
    }

    void Graph::AddNode(const Node& target_node) {
        vector<Edge> adjacent_nodes;
        graph_mappings_.insert({target_node, adjacent_nodes});
        graph_mappings_[target_node].reserve(100);
        map_size += 1;
    }

    void Graph::AddEdge(Node start_node, Node end_node, bool single_direction) {
        AddEdge(start_node, end_node, ci::Color("blue"), single_direction);
    }
    
    void Graph::AddEdge(Node start_node, Node end_node, ci::Color new_color, bool single_direction) {
        AddEdge(start_node, end_node, new_color, -1, single_direction);
    }

    void Graph::AddEdge(Node start_node, Node end_node, ci::Color new_color, int weight, bool single_direction) {
        if (graph_mappings_.empty() || &start_node == &end_node) {
            return;
        }

        const Node* start_node_loc = &start_node;
        const Node* end_node_loc = &end_node;

        for (auto & graph_mapping : graph_mappings_) {
            if (graph_mapping.first == start_node) {
                start_node_loc = &(graph_mapping.first);
            }
            if (graph_mapping.first == end_node) {
                end_node_loc = &(graph_mapping.first);
            }
        }

        graph_mappings_[*start_node_loc].emplace_back(Edge(start_node_loc, end_node_loc, true, new_color, weight));

        if (!single_direction) {
            graph_mappings_[*end_node_loc].emplace_back(Edge(end_node_loc, start_node_loc, true, new_color, weight));
        }
    }
    
    bool Graph::DeleteNode(const Node& target_node) {
        if (!NodeExists(target_node)) {
            return false;
        }

        //for every adjacent node, add all nodes that aren't the target node to adjacency list
        for (auto & adjacent_edge : graph_mappings_.at(target_node)) {
            vector<Edge> new_adjacent_nodes;
            Node target_node(adjacent_edge.GetEndNode()->GetValue(), adjacent_edge.GetEndNode()->GetLocation());
            for(auto & other_edges : graph_mappings_.at(target_node)) {
                if(*other_edges.GetEndNode() == *adjacent_edge.GetStartNode()) {
                    continue;
                }
                new_adjacent_nodes.push_back(other_edges);
            }
            graph_mappings_.at(target_node) = new_adjacent_nodes;
        }

        graph_mappings_.erase(target_node);
        map_size--;
        return true;
    }
    
    void Graph::DeleteEdge(const Node *start_node, const Node *end_node, bool single_direction) {
        DeleteNodeFromEdges(start_node, end_node);
        
        if(!single_direction) {
            DeleteNodeFromEdges(end_node, start_node);
        }
    }

    void Graph::DeleteNodeFromEdges(const Node *start_node, const Node *end_node) {
        vector<Edge> new_start_adjacent_nodes;
        for (auto & adjacent_edge : graph_mappings_.at(*start_node)) {
            if(*adjacent_edge.GetEndNode() == *end_node) {
                continue;
            }
            new_start_adjacent_nodes.push_back(adjacent_edge);
        }
        graph_mappings_.at(*start_node) = new_start_adjacent_nodes;
    }
    
    bool Graph::SetLocation(const Node& target_node, vec2 new_location) {
        if (!NodeExists(target_node)) {
            return false;
        }

        //get the adjacent nodes from the target then delete the target
        vector<Edge> adjacent_edges = graph_mappings_.at(target_node);
        DeleteNode(target_node);

        //re-add the node with a new location
        Node to_add(target_node.GetValue(), new_location);
        AddNode(to_add);
        
        //re-add all the edges to the node
        for (auto & target_edge : adjacent_edges) {
            AddEdge(to_add, *target_edge.GetEndNode(), false);
        }
        return true;
    }

    bool Graph::SetValue(const Node& target_node, int new_value) {
        if (!NodeExists(target_node)) {
            return false;
        }

        //get the adjacent nodes from the target then delete the target
        vector<Edge> adjacent_edges = graph_mappings_.at(target_node);
        DeleteNode(target_node);

        //re-add the node with a new location
        Node to_add(new_value, target_node.GetLocation());
        AddNode(to_add);

        //re-add all the edges to the node
        for (auto & target_edge : adjacent_edges) {
            AddEdge(to_add, *target_edge.GetEndNode(), false);
        }
        return true;
    }

    bool Graph::SetNodeColor(const Node &target_node, ci::Color new_color) {
        if(!NodeExists(target_node)) {
            return false;
        }

        vector<Edge> adjacent_edges = graph_mappings_.at(target_node);
        DeleteNode(target_node);

        //re-add the node with a new location
        Node to_add(target_node.GetValue(), target_node.GetLocation());
        to_add.SetColor(new_color);
        AddNode(to_add);
        
        //re-add all the edges to the node
        for (auto & target_edge : adjacent_edges) {
            AddEdge(to_add, *target_edge.GetEndNode(), false);
        }
        return true;
    }

    bool Graph::SetEdgeColor(const Node &start_node, const Node &end_node, const ci::Color new_color) {
        if(!EdgeExists(start_node, end_node)) {
           return false; 
        }

        DeleteEdge(&start_node, &end_node, false);
        AddEdge(start_node, end_node, new_color, false);
        return true;
    }
    
    bool Graph::NodeExists(const Node& to_check) {
        for (auto & graph_mapping : graph_mappings_) {
            if (to_check == graph_mapping.first) {
                return true;
            }
        }
        return false;
    }

    bool Graph::EdgeExists(const Node& start_node, const Node end_node) {
        if(!NodeExists(start_node) || !NodeExists(end_node)) {
            return false;
        }
        
        for(auto& adj_node: graph_mappings_.at(start_node)) {
            if(*adj_node.GetEndNode() == end_node) {
                return true;
            }
        }
        
        for(auto& adj_node: graph_mappings_.at(end_node)) {
            if(*adj_node.GetEndNode() == start_node) {
                return true;
            }
        }
        return false;
    }

    size_t Graph::size() const {
        return map_size;
    }

    bool Graph::empty() const {
        return map_size == 0;
    }
    
    void Graph::clear() {
        graph_mappings_.clear();
        map_size = 0;
    }
}