#include "visualizer/shortest_path_algorithms.h"

ShortestPath::ShortestPath(Graph *target_graph, Node starting_node, Node ending_node): target_graph_(target_graph) {
    unvisited_nodes = target_graph->GetNodes();
}

bool ShortestPath::RunSingleStepDijkstra() {
    if(unvisited_nodes.size() == 0) {
        return true;
    }
    
    return false;
    
}
