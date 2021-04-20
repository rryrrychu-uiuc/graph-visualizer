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
    
    Node(const Node& source);

    //
    Node(Node&& source) noexcept;

    ~Node();

    Node& operator=(const Node& source);

    Node& operator=(Node&& source) noexcept;

    
    vec2 GetLocation();
    
    int GetValue();

    vector<Node*> GetAdjacentNodes();
    
    void SetLocation(vec2 location);
    
    void SetValue(int value);
    
    void AddAdjacentNode(Node* adj_node);
    
    bool IsAdjacentTo(Node* target_node);
    
private:
    int data_;
    vec2 location_;
    vector<Node*> adjacent_nodes_;
};

#endif //FINAL_PROJECT_NODE_H
