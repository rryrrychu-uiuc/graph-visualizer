#include "../../include/core/node.h"

Node::Node(const Node &source) {
    location_ = source.location_;
    data_ = source.data_;
}

Node::Node(Node &&source) noexcept {
    location_ = source.location_;
    data_ = source.data_;
    
    source.data_ = 0;
    source.location_ = vec2(0,0);
}

Node::~Node() {
    data_ = 0;
    location_ = vec2(0,0);
}

Node &Node::operator=(const Node &source) {
    Node new_node(source);
    location_ = source.location_;
    data_ = source.data_;
    
    return *this;
}

Node &Node::operator=(Node &&source) noexcept {
    if(this == &source) {
        return *this;
    }

    location_ = source.location_;
    data_ = source.data_;
    return *this;
}

Node::Node(int data, vec2 location) {
    location_ = location;
    data_ = data;
}

vec2 Node::GetLocation() {
    return location_;
}

int Node::GetValue() {
    return data_;
}

void Node::SetLocation(vec2 location) {
    location_ = location;
}

void Node::SetValue(int value) {
    data_ = value;
}

