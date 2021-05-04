#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/graph.h>
#include <visualizer/graph_editor.h>

TEST_CASE("Test CreateNode") {
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
        REQUIRE(test_graph.size() == 5);
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

TEST_CASE("Test CreateEdge") {
    Node test_node1(10, vec2(200, 200));
    Node test_node2(20, vec2(300, 300));
    Node test_node3(30, vec2(400, 400));
    Node test_node4(40, vec2(500, 500));
    Node test_node5(50, vec2(600, 600));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    GraphEditor test_editor(30, 1000, 150);
    
    SECTION("No node at initial click location") {
        test_editor.CreateEdge(&test_graph, vec2(700, 100));
        REQUIRE(test_editor.empty());
    }
    
    SECTION("Valid initial click location") {
        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }
    
    SECTION("No node at followup click location") {
        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        test_editor.CreateEdge(&test_graph, vec2(700, 100));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }
    
    SECTION("Followup click same location as initial") {
        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }
    
    SECTION("Edge already exists") {
        test_graph.AddEdge(&test_node1, &test_node2, false);
        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
        test_editor.CreateEdge(&test_graph, vec2(300, 300));
        REQUIRE(test_editor.empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).size() == 1);
    }
    
    SECTION("Successful edge creation") {
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).empty());

        test_editor.CreateEdge(&test_graph, vec2(210, 210));
        test_editor.CreateEdge(&test_graph, vec2(300, 300));
        REQUIRE(test_editor.empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).at(0)->GetValue() == 20);
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).at(0)->GetValue() == 10);
    }
}

TEST_CASE("Test DeleteNode") {
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

TEST_CASE("Test DeleteEdge") {
    Node test_node1(10, vec2(200, 200));
    Node test_node2(20, vec2(300, 300));
    Node test_node3(30, vec2(400, 400));
    Node test_node4(40, vec2(500, 500));
    Node test_node5(50, vec2(600, 600));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    GraphEditor test_editor(30, 1000, 150);

    SECTION("No node at initial click location") {
        test_editor.DeleteEdge(&test_graph, vec2(900,900));
        REQUIRE(test_editor.empty());
    }

    SECTION("Valid initial click location") {
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }

    SECTION("No node at followup click location") {
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        test_editor.DeleteEdge(&test_graph, vec2(900,900));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }

    SECTION("Follow-up click same location as initial") {
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        REQUIRE_FALSE(test_editor.empty());
        REQUIRE(test_editor.GetVectorValues().find("10") != std::string::npos);
    }

    SECTION("No edge exists") {
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).empty());
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        test_editor.DeleteEdge(&test_graph, vec2(300,300));
        REQUIRE(test_editor.empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).empty());
    }

    SECTION("Successful edge deletion") {
        test_graph.AddEdge(&test_node1, &test_node2, false);
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).at(0)->GetValue() == 20);
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).at(0)->GetValue() == 10);
        test_editor.DeleteEdge(&test_graph, vec2(200,200));
        test_editor.DeleteEdge(&test_graph, vec2(300,300));
        REQUIRE(test_editor.empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node1).empty());
        REQUIRE(test_graph.GetAdjacentNodes(test_node2).empty());
    }
}

TEST_CASE("Test GetNodeAtLocation") {
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

TEST_CASE("Test NodeExistsInGraph") {
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

TEST_CASE("Test IsOutOfBounds") {
    GraphEditor test_editor(30, 1000, 150);

    SECTION("In bounds left") {
        REQUIRE_FALSE(test_editor.IsOutOfBounds(vec2(151, 500)));
    }

    SECTION("In bounds right") {
        REQUIRE_FALSE(test_editor.IsOutOfBounds(vec2(849, 500)));
    }

    SECTION("In bounds top") {
        REQUIRE_FALSE(test_editor.IsOutOfBounds(vec2(500, 151)));
    }

    SECTION("In bounds bottom") {
        REQUIRE_FALSE(test_editor.IsOutOfBounds(vec2(500, 849)));
    }

    SECTION("Out of bounds left") {
        REQUIRE(test_editor.IsOutOfBounds(vec2(150, 500)));
    }

    SECTION("Out of bounds right") {
        REQUIRE(test_editor.IsOutOfBounds(vec2(850, 500)));
    }

    SECTION("Out of bounds up") {
        REQUIRE(test_editor.IsOutOfBounds(vec2(500, 150)));
    }

    SECTION("Out of bounds down") {
        REQUIRE(test_editor.IsOutOfBounds(vec2(500, 850)));
    }    
}

TEST_CASE("Test empty") {
    Node test_node1(10, vec2(200, 200));
    Node test_node2(20, vec2(300, 300));
    Node test_node3(30, vec2(400, 400));
    Node test_node4(40, vec2(500, 500));
    Node test_node5(50, vec2(600, 600));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    GraphEditor test_editor(30, 1000, 150);
    
    SECTION("Is empty") {
        REQUIRE(test_editor.empty());
    }

    SECTION("Is not empty") {
        test_editor.CreateEdge(&test_graph, vec2(200,200));
        REQUIRE_FALSE(test_editor.empty());
    }
}

TEST_CASE("Test Clear editor") {
    Node test_node1(10, vec2(200, 200));
    Node test_node2(20, vec2(300, 300));
    Node test_node3(30, vec2(400, 400));
    Node test_node4(40, vec2(500, 500));
    Node test_node5(50, vec2(600, 600));

    Graph test_graph;
    test_graph.AddNode(test_node1);
    test_graph.AddNode(test_node2);
    test_graph.AddNode(test_node3);
    test_graph.AddNode(test_node4);
    test_graph.AddNode(test_node5);

    GraphEditor test_editor(30, 1000, 150);

    REQUIRE(test_editor.empty());
    test_editor.CreateEdge(&test_graph, vec2(200,200));
    REQUIRE_FALSE(test_editor.empty());
    test_editor.clear();
    REQUIRE(test_editor.empty());
}