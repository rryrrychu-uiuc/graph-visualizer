#include "../../include/core/node.h"

Node::Node() {
    data_ = -1;
    location_ = vec2(-1,-1);
    node_color_ = ci::Color("orange");
}

Node::Node(int data) {
    data_ = data;
    location_ = vec2(-1,-1);
    node_color_ = ci::Color("orange");
}

Node::Node(int data, vec2 location) {
    location_ = location;
    data_ = data;
    node_color_ = ci::Color("orange");
}

Node::Node(const Node &source) {
    location_ = source.location_;
    data_ = source.data_;
    node_color_ = source.node_color_;
    
}

Node::Node(Node &&source) noexcept {
    location_ = source.location_;
    data_ = source.data_;
    node_color_ = source.node_color_;
    
    source.data_ = 0;
    source.location_ = vec2(-1,-1);
}

Node::~Node() {
    data_ = 0;
    location_ = vec2(-1,-1);

}

Node &Node::operator=(const Node &source) {
    if(this == &source) {
        return *this;
    }
    
    location_ = source.location_;
    data_ = source.data_;
    node_color_ = source.node_color_;
    
    return *this;
}

Node &Node::operator=(Node &&source) noexcept {
    if(this == &source) {
        return *this;
    }
    
    location_ = source.location_;
    data_ = source.data_;
    node_color_ = source.node_color_;

    source.data_ = 0;
    source.location_ = vec2(-1,-1);
    return *this;
}

vec2 Node::GetLocation() const {
    return location_;
}

int Node::GetValue() const {
    return data_;
}

ci::Color Node::GetColor() const {
    return node_color_;
}


void Node::SetLocation(vec2 location) {
    location_ = location;
}

void Node::SetValue(int value) {
    data_ = value;
}

void Node::SetColor(ci::Color color) {
    node_color_ = color;
}

bool Node::operator==( const Node& rhs) const {
    return data_ == rhs.data_ && location_ == rhs.location_;
}

bool Node::operator<(const Node &ob) const {
    return data_ < ob.data_ || (data_ == ob.data_ && location_.x < ob.location_.x) || (data_ == ob.data_ && location_.x == ob.location_.x && location_.y < ob.location_.y);
}
