#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/graph.h>
#include <visualizer/graph_editor.h>

TEST_CASE("CreateNode Test") {
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
    
    SECTION("Valid Location") {
        GraphEditor test_editor(30, 1000, 150);
        test_editor.CreateNode(&test_graph, vec2(100, 100));
        REQUIRE(test_graph.size() == 6);
        for(auto& node: test_graph.GetNodes()) {
            if(node.GetValue() < 0){
                REQUIRE(node.GetLocation() == vec2(100,100));
            }
        }
    }
    
    SECTION("Invalid Location") {
        GraphEditor test_editor(30, 1000, 150);
        test_editor.CreateNode(&test_graph, vec2(5, 5));
        REQUIRE(test_graph.size() == 5);
    }
    
}

TEST_CASE("CreateEdge Test") {

}

TEST_CASE("DeleteNode Test") {
    Node test_node1(10, vec2(200,200));
    Node test_node2(20, vec2(500,100));
    Node test_node3(30, vec2(100, 800));
    Node test_node4(40, vec2(300, 500));
    Node test_node5(50, vec2(600, 400));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);
    
    SECTION("No node at location") {
        GraphEditor test_editor(30, 1000, 150);
        test_editor.DeleteNode(&test_graph, vec2(800,800));
        REQUIRE(test_graph.size() == 5);
    }
    
    SECTION("Properly removes node") {
        GraphEditor test_editor(30, 1000, 150);
        test_editor.DeleteNode(&test_graph, vec2(190,200));
        REQUIRE(test_graph.size() == 4);
        for(auto& graph_nodes: test_graph.GetNodes()) {
            REQUIRE_FALSE(graph_nodes.GetValue() == 10);
        }
    }
}

//TODO: Write test cases for DeleteEdge
TEST_CASE("DeleteEdge Test") {
    
}

TEST_CASE("GetNodeAtLocation Test") {
    Node test_node1(10, vec2(200,200));
    Node test_node2(20, vec2(500,100));
    Node test_node3(30, vec2(100, 800));
    Node test_node4(40, vec2(300, 500));
    Node test_node5(50, vec2(600, 400));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);
    
    SECTION("Location of a node") {
        GraphEditor test_editor(30, 1000, 150);
        Node returned_node = test_editor.GetNodeAtLocation(&test_graph, vec2(100, 829));
        REQUIRE(returned_node.GetValue() == 30);
        REQUIRE(returned_node.GetLocation() == vec2(100, 800));
    }

    SECTION("Location that does not contain a node") {
        GraphEditor test_editor(30, 1000, 150);
        Node returned_node = test_editor.GetNodeAtLocation(&test_graph, vec2(10, 10));
        REQUIRE(returned_node.GetValue() == -1);
        REQUIRE(returned_node.GetLocation() == vec2(-1, -1));
    }
}

TEST_CASE("NodeExistsInGraph Test") {
    Node test_node1(10, vec2(200,200));
    Node test_node2(20, vec2(500,100));
    Node test_node3(30, vec2(100, 800));
    Node test_node4(40, vec2(300, 500));
    Node test_node5(50, vec2(600, 400));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);
    
    SECTION("Invalid node") {
        Node invalid_node;
        GraphEditor test_editor(30, 1000, 150);
        REQUIRE_FALSE(test_editor.NodeExistsInGraph(invalid_node));
    }

    SECTION("Valid node") {
        Node valid_node(20, vec2(1,1));
        GraphEditor test_editor(30, 1000, 150);
        REQUIRE(test_editor.NodeExistsInGraph(valid_node));
    }
}

//TODO: Write test cases for clear
TEST_CASE("Clear editor") {
    
}