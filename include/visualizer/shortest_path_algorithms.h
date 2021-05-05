#pragma once
#ifndef FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H
#define FINAL_PROJECT_SHORTEST_PATH_ALGORITHMS_H

#include "core/graph.h"

using namespace graph;

class ShortestPath {
public:
    ShortestPath();
    
    ShortestPath(Graph* target_graph, Node starting_node, Node ending_node);
    
    /**
     * initalize proper values to run algorithm
     */
    void InitalizeValues(Graph* target_graph, Node starting_node, Node ending_node);
    
    /**
     * run one iteration of the algorithm
     */
    bool RunSingleStepDijkstra();

    /**
    * run entire algorithm
    */
    void RunEntireAlgorithm();
    
    /**
     * Find the smallest distance in distances
     */
    Node GetSmallestEdge();
    
    /**
     * Check if node is in visited vector
     */
    bool IsVisited(Node target_node);
    
    /**
     * Get the index of the node in the graph
     */
    int IndexOfNode(Node target_node);
    
    /**
     * Move a node from the unvisited vector the visited vector
     */
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
