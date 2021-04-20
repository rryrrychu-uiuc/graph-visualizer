#include "../../include/core/node.h"

Node::Node(int data) {
    data_ = data;
    location_ = vec2(-1,-1);
}

Node::Node(int data, vec2 location) {
    location_ = location;
    data_ = data;
}

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

void Node::AddAdjacentNode(Node* adj_node) {
    adjacent_nodes_.push_back(adj_node);
}

vector<Node*> Node::GetAdjacentNodes() {
    return adjacent_nodes_;
}

bool Node::IsAdjacentTo(Node* target_node) {
    for(size_t index = 0; index < adjacent_nodes_.size(); index++) {
        if (adjacent_nodes_[index] == target_node) {
            return true;
        }
    }
    return false;
}

