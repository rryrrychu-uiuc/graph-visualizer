#pragma once
#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H

#include <glm/vec2.hpp>
#include "cinder/gl/gl.h"

using ci::vec2;
using std::vector;

class Node {
public:
    /**
     * Constructor that only takes the value stored in the node
     * @param data value to be stored in the node
     */
    Node(int data);
    
    /**
     * Constructor that takes the location and data of a node
     * @param data value stored in node
     * @param location on the graph
     */
    Node(int data, vec2 location);
    
    /**
     * Copy constructor 
     */
    Node(const Node& source);

    /**
     * Move constructor 
     */
    Node(Node&& source) noexcept;

    /**
     * Destructor
     */
    ~Node();

    /**
     * Copy operator
     */    
    Node& operator=(const Node& source);

    /**
     * Move operator
     */
    Node& operator=(Node&& source) noexcept;
    
    vec2 GetLocation();
    
    int GetValue();

    vector<Node*> GetAdjacentNodes();
    
    void SetLocation(vec2 location);
    
    void SetValue(int value);
    
    /**
     * Add mem location of node to the adjacency list
     * @param adj_node node location to add
     */
    void AddAdjacentNode(Node* adj_node);

    /**
     * Checks if current node is adjacent to current node
     * @param adj_node location of node to check
     */    
    bool IsAdjacentTo(Node* target_node);
    
private:
    int data_;
    vec2 location_;
    vector<Node*> adjacent_nodes_;
};

#endif //FINAL_PROJECT_NODE_H
