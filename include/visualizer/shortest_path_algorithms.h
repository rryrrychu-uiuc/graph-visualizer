#pragma once
#ifndef FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H
#define FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H

#include "core/graph.h"

using namespace graph;

class ShortestPath {
public:
    ShortestPath();
    
    ShortestPath(Graph* target_graph, Node starting_node, Node ending_node);
    
    void InitalizeValues(Graph* target_graph, Node starting_node, Node ending_node);
    
    bool RunSingleStepDijkstra();
    
    void RunEntireAlgorithm();
    
    Node GetSmallestEdge();
    
    bool IsVisited(Node target_node);
    
    int IndexOfNode(Node target_node);
    
    void MoveNodeToVisited(Node target_node);
    
    vector<Node> GetUnvisitedNodes();
    
    vector<Node> GetVisitedNodes();
    
    vector<Node> GetPreviousNodes();
    
    vector<int> GetDistances();
    
    Node GetStartingNode();
    
    void ColorShortestPath();
    
private:
    Graph* target_graph_;
    Node starting_node_;
    Node ending_node_;
    Node previous_node_;
    
    vector<Node> visited_nodes_;
    vector<Node> unvisited_nodes_;
    
    vector<int> distances_;
    vector<Node> previous_nodes_;
    
    int starting_index_;
    int ending_index_;
    
    void ChangeDistances(Edge target_edge);
    
    void ResetClass();
};


#endif //FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H
