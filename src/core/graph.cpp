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

    vector<const Node *> Graph::GetAdjacentNodes(const Node& target_node) {
        return graph_mappings_.at(target_node);
    }

    void Graph::AddNode(const Node& target_node) {
        vector<const Node *> adjacent_nodes;
        graph_mappings_.insert({target_node, adjacent_nodes});
        graph_mappings_[target_node].reserve(100);
        map_size += 1;
    }

    void Graph::AddEdge(Node *start_node, Node *end_node, bool single_direction) {
        if (graph_mappings_.empty() || &start_node == &end_node) {
            return;
        }

        const Node *start_node_loc;
        const Node *end_node_loc;

        for (auto & graph_mapping : graph_mappings_) {
            if (graph_mapping.first == *start_node) {
                start_node_loc = &(graph_mapping.first);
            }
            if (graph_mapping.first == *end_node) {
                end_node_loc = &(graph_mapping.first);
            }
        }

        graph_mappings_[*start_node].emplace_back(end_node_loc);

        if (!single_direction) {
            graph_mappings_[*end_node].emplace_back(start_node_loc);
        }
    }

    bool Graph::DeleteNode(const Node& target_node) {
        if (!IsInGraph(target_node)) {
            return false;
        }

        //for every adjacent node, add all nodes that aren't the target node to adjacency list
        for (auto & adjacent_node : graph_mappings_.at(target_node)) {
            vector<const Node *> new_adjacent_nodes;
            for(auto & node_to_check : graph_mappings_.at(*adjacent_node)) {
                if(static_cast<Node>(*node_to_check) == target_node) {
                    continue;
                }
                new_adjacent_nodes.push_back(node_to_check);
            }
            graph_mappings_.at(*adjacent_node) = new_adjacent_nodes;
        }

        graph_mappings_.erase(target_node);
        map_size--;
        return true;
    }
    
    //TODO: add helper method that removes node from vector
    void Graph::DeleteEdge(Node *start_node, Node *end_node, bool single_direction) {
        vector<const Node *> new_start_adjacent_nodes;
        for (auto & adjacent_node : graph_mappings_.at(*start_node)) {
            if(*adjacent_node == *end_node) {
                continue;
            }
            new_start_adjacent_nodes.push_back(adjacent_node);
        }
        graph_mappings_.at(*start_node) = new_start_adjacent_nodes;
        
        if(!single_direction) {
            vector<const Node *> new_end_adjacent_nodes;
            for (auto & adjacent_node : graph_mappings_.at(*end_node)) {
                if(*adjacent_node == *start_node) {
                    continue;
                }
                new_end_adjacent_nodes.push_back(adjacent_node);
            }
            graph_mappings_.at(*end_node) = new_end_adjacent_nodes;
        }
    }
    
    bool Graph::SetLocation(const Node& target_node, vec2 new_location) {
        if (!IsInGraph(target_node)) {
            return false;
        }

        //get the adjacent nodes from the target then delete the target
        vector<const Node *> adjacent_nodes = graph_mappings_.at(target_node);
        DeleteNode(target_node);

        //re-add the node with a new location
        Node to_add(target_node.GetValue(), new_location);
        AddNode(to_add);
        
        //re-add all the edges to the node
        for (auto & adjacent_node : adjacent_nodes) {
            Node adj_node = *adjacent_node;
            AddEdge(&to_add, &adj_node, false);
        }
        return true;
    }

    bool Graph::SetValue(const Node& target_node, int new_value) {
        if (!IsInGraph(target_node)) {
            return false;
        }

        //get the adjacent nodes from the target then delete the target
        vector<const Node *> adjacent_nodes = graph_mappings_.at(target_node);
        DeleteNode(target_node);

        //re-add the node with a new location
        Node to_add(new_value, target_node.GetLocation());
        AddNode(to_add);
        
        graph_mappings_.at(to_add) = adjacent_nodes;
        return true;
    }

    bool Graph::IsInGraph(const Node& to_check) {
        for (auto & graph_mapping : graph_mappings_) {
            if (to_check == graph_mapping.first) {
                return true;
            }
        }
        return false;
    }

    bool Graph::EdgeExists(const Node& start_node, const Node end_node) {
        for(auto& adj_node: graph_mappings_.at(start_node)) {
            if(*adj_node == end_node) {
                return true;
            }
        }
        for(auto& adj_node: graph_mappings_.at(end_node)) {
            if(*adj_node == start_node) {
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