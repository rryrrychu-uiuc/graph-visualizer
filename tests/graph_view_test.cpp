#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/graph.h>
#include <visualizer/graph_view.h>

TEST_CASE("Test Move Node") {
    Node test_node1(10, vec2(700,700));
    Node test_node2(20, vec2(100,100));
    Node test_node3(30, vec2(200, 200));
    Node test_node4(40, vec2(300, 300));
    Node test_node5(50, vec2(400, 400));

    graph::Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    double kWindowSize = 1000.0;
    double kMargin = 150.0;
    GraphView test_visualizer(kWindowSize, kMargin);
    
    SECTION("Successfully move node") {
        test_visualizer.MoveNode(&test_graph, vec2(706,715));
        REQUIRE(test_graph.GetNodes().at(0).GetLocation() == vec2(706,715));
    }
    
    SECTION("No node moved") {
        test_visualizer.MoveNode(&test_graph, vec2(516,12));
        for(auto& node: test_graph.GetNodes()) {
            REQUIRE(node.GetLocation() != vec2(516, 12)); 
        }
    }
}

TEST_CASE("Test TouchesOtherNodes") {
    Node test_node1(10, vec2(700,700));
    Node test_node2(20, vec2(100,100));
    Node test_node3(30, vec2(131, 100));
    Node test_node4(40, vec2(300, 300));
    Node test_node5(50, vec2(400, 400));

    graph::Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    double kWindowSize = 1000.0;
    double kMargin = 150.0;
    GraphView test_visualizer(kWindowSize, kMargin);
    
    SECTION("Does touch") {
        REQUIRE(test_visualizer.TouchesOtherNodes(&test_graph, test_node2, vec2(130, 100)));
    }

    SECTION("Does not touch") {
        REQUIRE(test_visualizer.TouchesOtherNodes(&test_graph, test_node2, vec2(132, 101)));
    }
}

TEST_CASE("Test IsOutOfBounds GraphView") {
    GraphView test_visualizer(1000, 150);
    
    SECTION("In bounds left") {
        REQUIRE_FALSE(test_visualizer.IsOutOfBounds(vec2(151, 500)));
    }

    SECTION("In bounds right") {
        REQUIRE_FALSE(test_visualizer.IsOutOfBounds(vec2(849, 500)));
    }

    SECTION("In bounds top") {
        REQUIRE_FALSE(test_visualizer.IsOutOfBounds(vec2(500, 151)));
    }

    SECTION("In bounds bottom") {
        REQUIRE_FALSE(test_visualizer.IsOutOfBounds(vec2(500, 849)));
    }
    
    SECTION("Out of bounds left") {
        REQUIRE(test_visualizer.IsOutOfBounds(vec2(150, 500)));
    }

    SECTION("Out of bounds right") {
        REQUIRE(test_visualizer.IsOutOfBounds(vec2(850, 500)));
    }

    SECTION("Out of bounds up") {
        REQUIRE(test_visualizer.IsOutOfBounds(vec2(500, 150)));
    }

    SECTION("Out of bounds down") {
        REQUIRE(test_visualizer.IsOutOfBounds(vec2(500, 850)));
    }
}
