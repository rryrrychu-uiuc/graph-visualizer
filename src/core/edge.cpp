#include "core/edge.h"

Edge::Edge(Node *start_node, Node *end_node): start_(start_node), end_(end_node), is_two_sided_(false) {}

Edge::Edge(Node* start_node, Node* end_node, bool is_two_sided): start_(start_node), end_(end_node), is_two_sided_(is_two_sided) {}

bool Edge::IsTwoSided() {
    return is_two_sided_;
}

Node* Edge::GetStartNode() {
    return start_;
}

Node* Edge::GetEndNode() {
    return end_;
}

void Edge::SetStartNode(Node* start_node) {
    start_ = start_node;
}

void Edge::SetEndNode(Node* end_node) {
    end_ = end_node;
}

void Edge::ChangeToOneSided() {
    is_two_sided_ = false;
}

void Edge::ChangeToTwoSided() {
    is_two_sided_ = true;
}
