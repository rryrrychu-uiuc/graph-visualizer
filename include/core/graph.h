#pragma once
#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H

#include "node.h"
#include "edge.h"
#include <vector>

using std::vector;
using std::map;

namespace graph {
    class Graph {
    public:
        /**
         * Default constructor for a graph
         */
        Graph();

        /**
         * Returns list of nodes in the graph
         */
        vector<Node> GetNodes();

        /**
        * Returns list of references to the nodes in the graph
        */
        vector<const Node *> GetAdjacentNodes(const Node& target_node);

        /**
         * Add a node to the graph 
         */
        void AddNode(const Node& target_node);

        /**
         * Add adjacent node to a certain node
         * @param start_node node to add adjacent node to 
         * @param end_node node to be added
         * @param single_direction false if both nodes should be added to each other's adjacency list
         */
        void AddEdge(Node *start_node, Node *end_node, bool single_direction);

        /**
         * Delete a node an all existences of edges from graph (including adjacencies)
         * @return true if the node is successfully deleted
         */
        bool DeleteNode(const Node& target_node);

        /**
        * Delete an edge between two nodes (including adjacencies)
        * @return true if the node is successfully deleted
        */
        void DeleteEdge(Node *start_node, Node *end_node, bool single_direction);

        /**
         * Changes the location of a node
         * @param target_node the node to change location
         * @param new_location new location of a node
         * @return true if node is changed successfully, false if it fails
         */
        bool SetLocation(const Node& target_node, vec2 new_location);

        /**
        * Changes the value of a node
        * @param target_node the node to change value
        * @param new_value new value of a node
        * @return true if node is changed successfully, false if it fails
        */
        bool SetValue(const Node& target_node, int new_value);

        /**
         * Check if the node exists in the graph
         * @param to_check node to check
         * @return true if the node is in the graph
         */
        bool NodeExists(const Node& to_check);
        
        /**
         * Check if an edge already exists in the graph
         */
        bool EdgeExists(const Node& start_node, const Node end_node);
        
        /**
         * Delete every node from the graph
         */
        void clear();
        
        /**
         * Checks if a graph is empty
         * @return true if the graph has no nodes
         */
        bool empty() const;

        /**
        * Returns number of nodes in the map
        */
        size_t size() const;

    private:
        map<Node, vector<const Node *>> graph_mappings_;
        size_t map_size;
    };
}

#endif //FINAL_PROJECT_GRAPH_H
