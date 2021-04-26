#pragma once
#ifndef FINAL_PROJECT_EDGE_H
#define FINAL_PROJECT_EDGE_H

#include "node.h"

class Edge {
public:

    /**
     * Create an edge given two node references, default to being two sided edge
     */
    Edge(Node* start_node, Node* end_node);

    /**
    * Create an edge given two node references and the directions
    */
    Edge(Node* start_node, Node* end_node, bool is_two_sided);
    
    bool IsTwoSided();
    
    Node* GetStartNode();
    
    Node* GetEndNode();
    
    void SetStartNode(Node* start_node);
    
    void SetEndNode(Node* end_node);
    
    /**
     * Change edge to be one sided
     */
    void ChangeToOneSided();

    /**
    * Change edge to be two sided
    */
    void ChangeToTwoSided();
    
private:
    bool is_two_sided_;
    Node* start_;
    Node* end_;
};

#endif //FINAL_PROJECT_EDGE_H
