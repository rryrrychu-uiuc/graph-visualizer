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
     * Create a node with default values
     */
    Node();
    
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
    Node(const Node &source);

    /**
     * Move constructor 
     */
    Node(Node &&source) noexcept;

    /**
     * Destructor
     */
    ~Node();

    /**
     * Copy operator
     */
    Node &operator=(const Node &source);

    /**
     * Move operator
     */
    Node &operator=(Node &&source) noexcept;

    /**
     * Equals operator
     */
    bool Node::operator==(const Node &rhs) const;

    /**
     * Less than operator
     */
    bool operator<(const Node &ob) const;

    vec2 GetLocation() const;

    int GetValue() const;

    ci::Color GetColor() const;
    
    void SetLocation(vec2 location);

    void SetValue(int value);
    
    void SetColor(ci::Color color);

private:
    int data_;
    vec2 location_;
    ci::Color node_color_;
};

#endif //FINAL_PROJECT_NODE_H
