#include "../../include/core/node.h"

Node::Node(int data) {
    data_ = data;
    location_ = vec2(-1,-1);
}

Node::Node(int data, vec2 location) {
    location_ = location;
    data_ = data;
    adjacent_nodes_.reserve(100);
}

Node::Node(const Node &source) {
    location_ = source.location_;
    data_ = source.data_;
    
    for(size_t index = 0; index < source.adjacent_nodes_.size(); index++) {
        adjacent_nodes_.push_back(source.adjacent_nodes_[index]);
    }
}

Node::Node(Node &&source) noexcept {
    location_ = source.location_;
    data_ = source.data_;
    for(size_t index = 0; index < source.adjacent_nodes_.size(); index++) {
        adjacent_nodes_.push_back(source.adjacent_nodes_[index]);
    }
    
    source.data_ = 0;
    source.location_ = vec2(-1,-1);
    source.adjacent_nodes_.clear();
}

Node::~Node() {
    data_ = 0;
    location_ = vec2(-1,-1);
    adjacent_nodes_.clear();
}

Node &Node::operator=(const Node &source) {
    if(this == &source) {
        return *this;
    }

    for(size_t index = 0; index < source.adjacent_nodes_.size(); index++) {
        adjacent_nodes_.push_back(source.adjacent_nodes_[index]);
    }
    
    location_ = source.location_;
    data_ = source.data_;
    
    return *this;
}

Node &Node::operator=(Node &&source) noexcept {
    if(this == &source) {
        return *this;
    }

    adjacent_nodes_.clear();
    for(size_t index = 0; index < source.adjacent_nodes_.size(); index++) {
        adjacent_nodes_.push_back(source.adjacent_nodes_[index]);
    }
    
    location_ = source.location_;
    data_ = source.data_;

    source.data_ = 0;
    source.location_ = vec2(-1,-1);
    source.adjacent_nodes_.clear();
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

bool Node::operator==( const Node& rhs) const {
    return data_ == rhs.data_ && location_ == rhs.location_;
}