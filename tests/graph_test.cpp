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

TEST_CASE("Test Adding Edge to Graph") {
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
        test_graph.AddEdge(test_node1, test_node2, false);
        test_graph.AddEdge(test_node1, test_node3, false);
        test_graph.AddEdge(test_node1, test_node4, false);
        test_graph.AddEdge(test_node1, test_node5, false);

        int expected_values[4]  = {20,30,40,50};
        vector<Node> graph_nodes = test_graph.GetNodes();
        for(auto & graph_node : graph_nodes) {
            vector<Edge> adj_nodes = test_graph.GetAdjacentNodes(graph_node);
            if(adj_nodes.size() != 1) {
                for(size_t expected_index = 0; expected_index < adj_nodes.size(); expected_index++) {
                    REQUIRE(expected_values[expected_index] == adj_nodes.at(expected_index).GetEndNode()->GetValue());
                }
            }
        }
    }

    SECTION("Test One Sided Edge") {
        test_graph.AddEdge(test_node1, test_node2, true);
        vector<Node> graph_nodes = test_graph.GetNodes();
        vector<Edge> node_one_edges = test_graph.GetAdjacentNodes(graph_nodes[0]);
        vector<Edge> node_two_edges = test_graph.GetAdjacentNodes(graph_nodes[1]);

        REQUIRE(node_one_edges.size() == 1);
        REQUIRE(node_two_edges.empty());

        REQUIRE(node_one_edges.at(0).GetEndNode()->GetValue() == 20);
    }

    SECTION("Test Two Sided Edge") {
        test_graph.AddEdge(test_node1, test_node2, false);
        vector<Node> graph_nodes = test_graph.GetNodes();
        vector<Edge> node_one_edges = test_graph.GetAdjacentNodes(graph_nodes[0]);
        vector<Edge> node_two_edges = test_graph.GetAdjacentNodes(graph_nodes[1]);

        REQUIRE(node_one_edges.size() == 1);
        REQUIRE(node_two_edges.size() == 1);

        REQUIRE(node_one_edges.at(0).GetEndNode()->GetValue() == 20);
        REQUIRE(node_two_edges.at(0).GetEndNode()->GetValue() == 10);
    }
}

TEST_CASE("test Adding Edge with Color") {
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
        test_graph.AddEdge(test_node1, test_node2, ci::Color("red"), false);
        test_graph.AddEdge(test_node1, test_node3, ci::Color("red"), false);
        test_graph.AddEdge(test_node1, test_node4, ci::Color("red"), false);
        test_graph.AddEdge(test_node1, test_node5, ci::Color("red"), false);

        int expected_values[4]  = {20,30,40,50};
        vector<Node> graph_nodes = test_graph.GetNodes();
        for(auto & graph_node : graph_nodes) {
            for(auto& adjacent_edge: test_graph.GetAdjacentNodes(graph_node)) {
                REQUIRE(adjacent_edge.GetEdgeColor() == ci::Color("red"));
            }
        }
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
        test_graph.AddEdge(test_node1, test_node2, false);
        test_graph.AddEdge(test_node1, test_node3, false);
        test_graph.AddEdge(test_node1, test_node4, false);
        test_graph.AddEdge(test_node1, test_node5, false);

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

TEST_CASE("Test Deleting an Edge") {
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

    test_graph.AddEdge(test_node1, test_node2, false);
    test_graph.AddEdge(test_node1, test_node3, false);
    test_graph.AddEdge(test_node1, test_node4, false);
    test_graph.AddEdge(test_node1, test_node5, false);
    test_graph.AddEdge(test_node3, test_node4, false);
    test_graph.AddEdge(test_node3, test_node5, false);

    vector<Node> graph_nodes = test_graph.GetNodes();

    SECTION("Test Proper Edge Adding") {
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[0]).size() == 4);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[1]).size() == 1);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[2]).size() == 3);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[3]).size() == 2);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[4]).size() == 2);
    }

    SECTION("Test Proper Edge Deleting") {
        test_graph.DeleteEdge(&test_node1, &test_node2, false);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[0]).size() == 3);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[1]).empty());
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[2]).size() == 3);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[3]).size() == 2);
        REQUIRE(test_graph.GetAdjacentNodes(graph_nodes[4]).size() == 2);
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
    for(auto & graph_node : graph_nodes) {
        if(graph_node.GetValue() != 0) {
            REQUIRE(graph_node.GetValue() == 15);
        }
    }
}

TEST_CASE("Test Setting a new node color") {
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
    
    SECTION("Node does not exist") {
        Node random_node(124, vec2(156,154));
        REQUIRE_FALSE(test_graph.SetNodeColor(random_node, ci::Color("green")));
    }
    
    SECTION("Node successfully changes color") {
        for(auto& graph_node: test_graph.GetNodes()){
            REQUIRE(graph_node.GetColor() == ci::Color("orange"));
        }

        REQUIRE(test_graph.SetNodeColor(test_node3, ci::Color("green")));
        for(auto& graph_node: test_graph.GetNodes()){
            if(graph_node.GetColor() != ci::Color("orange")) {
                REQUIRE(graph_node.GetColor() == ci::Color("green"));
            }
        }
    }
}

TEST_CASE("Test Setting a new edge color") {
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

    test_graph.AddEdge(test_node1, test_node2, false);
    test_graph.AddEdge(test_node1, test_node3, false);
    test_graph.AddEdge(test_node1, test_node4, false);
    test_graph.AddEdge(test_node1, test_node5, false);
    
    SECTION("Edge does not exist") {
        REQUIRE_FALSE(test_graph.SetEdgeColor(test_node2, test_node3, ci::Color("yellow")));
    }
    
    SECTION("Node for edge doesn't exist") {
        Node random_node(124, vec2(156,154));
        REQUIRE_FALSE(test_graph.SetEdgeColor(random_node, test_node3, ci::Color("yellow")));
    }
    
    SECTION("Edge correctly changes color") {
        REQUIRE(test_graph.SetEdgeColor(test_node1, test_node2, ci::Color("yellow")));
        for(auto& adjacent_edge: test_graph.GetAdjacentNodes(test_node1)) {
            if(adjacent_edge.GetEdgeColor() != ci::Color("blue")) {
                REQUIRE(adjacent_edge.GetEdgeColor() == ci::Color("yellow"));
            }
        }

        for(auto& adjacent_edge: test_graph.GetAdjacentNodes(test_node2)) {
            if(adjacent_edge.GetEdgeColor() != ci::Color("blue")) {
                REQUIRE(adjacent_edge.GetEdgeColor() == ci::Color("yellow"));
            }
        }
    }
}

TEST_CASE("Test Node Exists") {
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

    SECTION("Node with non-matching parameters") {
        REQUIRE_FALSE(test_graph.NodeExists(Node(14, vec2(15,16))));
    }
    
    SECTION("Node with non-matching value") {
        REQUIRE_FALSE(test_graph.NodeExists(Node(12, vec2(0,0))));
    }

    SECTION("Node with non-matching location") {
        REQUIRE_FALSE(test_graph.NodeExists(Node(10, vec2(15,16))));
    }
    
    SECTION("Node exists") {
        REQUIRE(test_graph.NodeExists(Node(10, vec2(0,0))));
    }
}

TEST_CASE("Test Edge Exists") {
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
    
    test_graph.AddEdge(test_node1, test_node2, false);
    test_graph.AddEdge(test_node1, test_node3, false);
    test_graph.AddEdge(test_node1, test_node4, false);
    test_graph.AddEdge(test_node1, test_node5, false);
    
    SECTION("Edge exists") {
        REQUIRE(test_graph.EdgeExists(test_node1, test_node2));
    }
    
    SECTION("Edge doesn't exist") {
        REQUIRE_FALSE(test_graph.EdgeExists(test_node2, test_node3));
    }
    
    SECTION("Edge doesn't exist when single node doesn't exist") {
        REQUIRE_FALSE(test_graph.EdgeExists(test_node2, Node(12, vec2(12,12))));
        REQUIRE_FALSE(test_graph.EdgeExists(Node(12, vec2(12,12)), test_node2));
        REQUIRE_FALSE(test_graph.EdgeExists(Node(12, vec2(12,12)),Node(12, vec2(12,12))));
    }
}

TEST_CASE("Test Size") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;
    SECTION("Graph changes size on adding") {
        test_graph.AddNode(test_node1);
        REQUIRE(test_graph.size() == 1);
        test_graph.AddNode(test_node2);
        REQUIRE(test_graph.size() == 2);
        test_graph.AddNode(test_node3);
        REQUIRE(test_graph.size() == 3);
    }

    SECTION("Graph changes size on deleting") {
        test_graph.AddNode(test_node1);
        test_graph.AddNode(test_node2);
        test_graph.AddNode(test_node3);
        test_graph.AddNode(test_node4);
        test_graph.AddNode(test_node5);
        REQUIRE(test_graph.size() == 5);

        test_graph.DeleteNode(test_node1);
        REQUIRE(test_graph.size() == 4);
        test_graph.DeleteNode(test_node2);
        REQUIRE(test_graph.size() == 3);
        test_graph.DeleteNode(test_node3);
        REQUIRE(test_graph.size() == 2);
    }
}

TEST_CASE("Test Empty") {
    Node test_node1(10, vec2(0,0));
    Node test_node2(20, vec2(1,1));
    Node test_node3(30, vec2(2, 2));
    Node test_node4(40, vec2(3, 3));
    Node test_node5(50, vec2(4, 4));

    Graph test_graph;

    SECTION("Graph is empty") {
        REQUIRE(test_graph.empty());
    }

    SECTION("Graph is not-empty") {
        test_graph.AddNode(test_node1);
        REQUIRE_FALSE(test_graph.empty());
    }
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

    REQUIRE(test_graph.empty());
    REQUIRE(test_graph.GetNodes().empty());
}