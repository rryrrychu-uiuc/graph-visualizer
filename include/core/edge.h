#pragma once
#ifndef FINAL_PROJECT_EDGE_H
#define FINAL_PROJECT_EDGE_H

#include "node.h"

class Edge {
public:

    /**
     * Create an edge given two node references, default to being two sided edge
     */
    Edge(const Node* start_node, const Node* end_node);

    /**
    * Create an edge given two node references and the directions
    */
    Edge(const Node* start_node, const Node* end_node, bool is_two_sided);
    
    bool IsTwoSided() const;
    
    const Node* GetStartNode();
    
    const Node* GetEndNode();
    
    int GetWeight();
    
    ci::Color GetEdgeColor();
    
    /**
     * Change the first node in the edge
     */
    void SetStartNode(const Node* start_node);

    /**
     * Change the second node in the edge
     */    
    void SetEndNode(const Node* end_node);

    /**
    * Change the weight/value of the edge
    */
    void SetWeight(int new_weight);

    /**
    * Change the color of the edge
    */    
    void SetEdgeColor(ci::Color new_color);
    
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
    const Node* start_;
    const Node* end_;
    int weight_;
    ci::Color edge_color_;
};

#endif //FINAL_PROJECT_EDGE_H
