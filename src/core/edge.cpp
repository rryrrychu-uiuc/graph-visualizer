#include "core/edge.h"

Edge::Edge(const Node *start_node, const Node *end_node):
    start_(start_node), 
    end_(end_node), 
    is_two_sided_(true),
    edge_color_(ci::Color("blue")), 
    weight_(-1) {}

Edge::Edge(const Node *start_node, const Node *end_node, bool is_two_sided): 
    start_(start_node), end_(end_node),
    is_two_sided_(is_two_sided),
    edge_color_(ci::Color("blue")), 
    weight_(-1) {}

Edge::Edge(const Node *start_node, const Node *end_node, bool is_two_sided, ci::Color target_color): 
    start_(start_node), 
    end_(end_node),
    is_two_sided_(is_two_sided),
    edge_color_(target_color), 
    weight_(-1)  {}

Edge::Edge(const Node *start_node, const Node *end_node, bool is_two_sided, ci::Color target_color, int weight):
        start_(start_node),
        end_(end_node),
        is_two_sided_(is_two_sided),
        edge_color_(target_color),
        weight_(weight)  {}
    
bool Edge::IsTwoSided() const {
    return is_two_sided_;
}

const Node* Edge::GetStartNode() const{
    return start_;
}

const Node* Edge::GetEndNode() const{
    return end_;
}

int Edge::GetWeight() const{
    return weight_;
}

ci::Color Edge::GetEdgeColor() const{
    return edge_color_;
}

void Edge::SetStartNode(const Node *start_node) {
    start_ = start_node;
}

void Edge::SetEndNode(const Node *end_node) {
    end_ = end_node;
}

void Edge::SetWeight(int new_weight) {
    weight_ = new_weight;
}

void Edge::SetEdgeColor(ci::Color new_color) {
    edge_color_ = new_color;
}

void Edge::ChangeToOneSided() {
    is_two_sided_ = false;
}

void Edge::ChangeToTwoSided() {
    is_two_sided_ = true;
}

bool Edge::operator<(const Edge &ob) const {
    return weight_ < ob.weight_;
}
