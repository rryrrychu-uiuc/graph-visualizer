#pragma once
#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H

#include <glm/vec2.hpp>
#include "cinder/gl/gl.h"

using ci::vec2;
using std::vector;

class Node {
public:
    
    Node(const Node& source);

    Node(Node&& source) noexcept;

    ~Node();

    Node& operator=(const Node& source);

    Node& operator=(Node&& source) noexcept;
    
    Node(int data, vec2 location);
    
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
