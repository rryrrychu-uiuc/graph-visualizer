#include "core/edge.h"

Edge::Edge(const Node *start_node, const Node *end_node) : start_(start_node), end_(end_node), is_two_sided_(true),
                                               edge_color_(ci::Color("blue")), weight_(-1) {}

Edge::Edge(const Node *start_node, const Node *end_node, bool is_two_sided) : start_(start_node), end_(end_node),
                                                                  is_two_sided_(is_two_sided),
                                                                  edge_color_(ci::Color("blue")), weight_(-1) {}

bool Edge::IsTwoSided() const {
    return is_two_sided_;
}

const Node* Edge::GetStartNode() {
    return start_;
}

const Node* Edge::GetEndNode() {
    return end_;
}

int Edge::GetWeight() {
    return weight_;
}

ci::Color Edge::GetEdgeColor() {
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
