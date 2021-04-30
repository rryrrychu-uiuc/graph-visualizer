#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/graph.h>

using graph::Graph;

TEST_CASE("Test Adding Nodes to Graph") {
    Graph test_graph;
    Node test_node1(0);
    Node test_node2(1);
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    REQUIRE(test_graph.GetNodes().size() == 2);
    
    SECTION("Check correct values") {
        vector<Node> test_nodes = test_graph.GetNodes();
        for(int index = 0; index < 2; index++) {
            REQUIRE(test_nodes[index].GetValue() == index);
        }
    }
}

TEST_CASE("Test Setting a New Location") {
    Graph test_graph;
    Node test_node1(0, vec2(1,1));
    Node test_node2(1, vec2(1,1));
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    REQUIRE(test_graph.GetNodes().size() == 2);

    SECTION("Check correct values") {
        vector<Node> test_nodes = test_graph.GetNodes();
        for(size_t index = 0; index < 2; index++) {
            REQUIRE(test_graph.SetLocation(test_nodes[index], vec2(15,15)));
        }

        vector<Node> test_nodes2 = test_graph.GetNodes();
        for(size_t index = 0; index < 2; index++) {
            REQUIRE(test_nodes2[index].GetLocation() == vec2(15,15));
        }
    }
    
    SECTION("Check that returns false if node does not exist") {
        Node target_node(0, vec2(14,14));
        REQUIRE_FALSE(test_graph.SetLocation(target_node, vec2(5,5)));
    }
}

TEST_CASE("Test Setting a New Value") {
    Graph test_graph;
    Node test_node1(0, vec2(1,2));
    Node test_node2(0, vec2(1,3));
    Node test_node3(0, vec2(1,4));
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    
    test_graph.SetValue(test_node2, 15);
    
    vector<Node> graph_nodes = test_graph.GetNodes();
    for(size_t index = 0; index < graph_nodes.size(); index++) {
        if(graph_nodes[index].GetValue() != 0) {
            REQUIRE(graph_nodes[index] == 15);
        }
    }
}

TEST_CASE("Test AddEdge") {
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
    
    SECTION("Test Multiple Edges") {
        test_graph.AddEdge(&test_node1, &test_node2, false);
        test_graph.AddEdge(&test_node1, &test_node3, false);
        test_graph.AddEdge(&test_node1, &test_node4, false);
        test_graph.AddEdge(&test_node1, &test_node5, false);

        int expected_values[4]  = {20,30,40,50};
        vector<Node> graph_nodes = test_graph.GetNodes();
        for(auto & graph_node : graph_nodes) {
            vector<const Node*> adj_nodes = test_graph.GetAdjacentNodes(graph_node);
            if(adj_nodes.size() != 1) {
                for(size_t expected_index = 0; expected_index < adj_nodes.size(); expected_index++) {
                    REQUIRE(expected_values[expected_index] == adj_nodes.at(expected_index)->GetValue());
                }
            }
        }
    }
    
    SECTION("Test One Sided Edge") {
        test_graph.AddEdge(&test_node1, &test_node2, true);
        vector<Node> graph_nodes = test_graph.GetNodes();
        vector<const Node*> node_one_edges = test_graph.GetAdjacentNodes(graph_nodes[0]);
        vector<const Node*> node_two_edges = test_graph.GetAdjacentNodes(graph_nodes[1]);
        
        REQUIRE(node_one_edges.size() == 1);
        REQUIRE(node_two_edges.empty());
        
        REQUIRE(node_one_edges.at(0)->GetValue() == 20);
    }

    SECTION("Test Two Sided Edge") {
        test_graph.AddEdge(&test_node1, &test_node2, false);
        vector<Node> graph_nodes = test_graph.GetNodes();
        vector<const Node*> node_one_edges = test_graph.GetAdjacentNodes(graph_nodes[0]);
        vector<const Node*> node_two_edges = test_graph.GetAdjacentNodes(graph_nodes[1]);

        REQUIRE(node_one_edges.size() == 1);
        REQUIRE(node_two_edges.size() == 1);

        REQUIRE(node_one_edges.at(0)->GetValue() == 20);
        REQUIRE(node_two_edges.at(0)->GetValue() == 10);
    }
}

TEST_CASE("Test Deleting a Node") {
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

    SECTION("Erase from the list of nodes") {
        test_graph.DeleteNode(test_node3);
        
        vector<Node> graph_nodes = test_graph.GetNodes();
        REQUIRE(graph_nodes.size() == 4);
        
        for(size_t index = 0; index < test_graph.size(); index++) {
            REQUIRE(graph_nodes[index].GetValue() != 30);
        }
    }
    
    SECTION("Erases node from adjacency list") {
        REQUIRE(test_graph.size() == 5);
        test_graph.AddEdge(&test_node1, &test_node2, false);
        test_graph.AddEdge(&test_node1, &test_node3, false);
        test_graph.AddEdge(&test_node1, &test_node4, false);
        test_graph.AddEdge(&test_node1, &test_node5, false);

        REQUIRE(test_graph.DeleteNode(test_node1));
        REQUIRE(test_graph.size() == 4);

        vector<Node> graph_nodes = test_graph.GetNodes();
        for(auto & graph_node : graph_nodes) {
            REQUIRE(test_graph.GetAdjacentNodes(graph_node).empty());
        }
    }
    
    SECTION("Node does not exist") {
        Node to_delete(60, vec2(35,35));
        REQUIRE_FALSE(test_graph.DeleteNode(to_delete));
    }
}

//TODO: add test cases for deleting an edge
TEST_CASE("Test Deleting an Edge") {
    
}

TEST_CASE("Test Clearing Map") {
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

    REQUIRE(test_graph.size() == 5);
    
    test_graph.clear();

    REQUIRE(test_graph.size() == 0);
    REQUIRE(test_graph.GetNodes().empty());
}

//TODO: add test cases for one sided and two sided edges and edges that don't already exist
TEST_CASE("Test Edge Already Exists") {
    
}

