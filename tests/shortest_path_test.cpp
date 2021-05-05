#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/graph.h>
#include <visualizer/shortest_path_algorithms.h>

TEST_CASE("Test RunSingleStepDijkstra") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    test_graph.AddEdge(test_node1, test_node2, ci::Color("blue"), 6,false);
    test_graph.AddEdge(test_node1, test_node4, ci::Color("blue"), 1, false);
    test_graph.AddEdge(test_node2, test_node3, ci::Color("blue"), 5, false);
    test_graph.AddEdge(test_node2, test_node4, ci::Color("blue"), 2, false);
    test_graph.AddEdge(test_node2, test_node5, ci::Color("blue"), 2, false);
    test_graph.AddEdge(test_node5, test_node3, ci::Color("blue"), 5, false);
    test_graph.AddEdge(test_node5, test_node4, ci::Color("blue"), 1, false);

    ShortestPath target_algorithm(&test_graph, test_node1, test_node3);
    target_algorithm.RunSingleStepDijkstra();
    
    vector<int> distances = target_algorithm.GetDistances();
    REQUIRE(distances[1] == 6);
    REQUIRE(distances[3] == 1);
    REQUIRE(target_algorithm.GetStartingNode().GetValue() == 40);
}

TEST_CASE("Test RunEntireAlgorithm") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    test_graph.AddEdge(test_node1, test_node2, ci::Color("blue"), 6,false);
    test_graph.AddEdge(test_node1, test_node4, ci::Color("blue"), 1, false);
    test_graph.AddEdge(test_node2, test_node3, ci::Color("blue"), 5, false);
    test_graph.AddEdge(test_node2, test_node4, ci::Color("blue"), 2, false);
    test_graph.AddEdge(test_node2, test_node5, ci::Color("blue"), 2, false);
    test_graph.AddEdge(test_node5, test_node3, ci::Color("blue"), 5, false);
    test_graph.AddEdge(test_node5, test_node4, ci::Color("blue"), 1, false);

    ShortestPath target_algorithm(&test_graph, test_node1, test_node3);
    target_algorithm.RunEntireAlgorithm();
    
    vector<int> distances = target_algorithm.GetDistances();
    vector<Node> previous_nodes = target_algorithm.GetPreviousNodes();
    
    REQUIRE(distances[0] == 0);
    REQUIRE(distances[1] == 3);
    REQUIRE(distances[2] == 7);
    REQUIRE(distances[3] == 1);
    REQUIRE(distances[4] == 2);
    REQUIRE(previous_nodes[1] == test_node4);
    REQUIRE(previous_nodes[2] == test_node5);
    REQUIRE(previous_nodes[3] == test_node1);
    REQUIRE(previous_nodes[4] == test_node4);
}

TEST_CASE("Test GetSmallest Edge") {
}

TEST_CASE("Test IsVisited") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    ShortestPath target_algorithm(&test_graph, test_node1, test_node2);
    target_algorithm.MoveNodeToVisited(test_node2);
    target_algorithm.MoveNodeToVisited(test_node4);
    
    REQUIRE(target_algorithm.GetVisitedNodes().size() == 2);
    REQUIRE(target_algorithm.GetUnvisitedNodes().size() == 3);
    REQUIRE(target_algorithm.IsVisited(test_node2));
    REQUIRE(target_algorithm.IsVisited(test_node4));
    REQUIRE_FALSE(target_algorithm.IsVisited(test_node1));
    
}

TEST_CASE("Test IndexOfNode") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    ShortestPath target_algorithm(&test_graph, test_node1, test_node2);
    REQUIRE(target_algorithm.IndexOfNode(test_node3) == 2);
    REQUIRE(target_algorithm.IndexOfNode(test_node1) == 0);
}

TEST_CASE("Test RemoveNodeFromUnvisited") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);
    
    ShortestPath target_algorithm(&test_graph, test_node1, test_node2);
    target_algorithm.MoveNodeToVisited(test_node3);
    REQUIRE(target_algorithm.GetUnvisitedNodes().size() == 4);
    REQUIRE(target_algorithm.GetVisitedNodes().size() == 1);
    REQUIRE(target_algorithm.GetVisitedNodes().at(0).GetValue() == 30);
}