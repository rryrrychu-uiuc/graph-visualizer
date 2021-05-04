#include <catch2/catch.hpp>
#include <core/node.h>
#include <core/edge.h>

TEST_CASE("Two Constructor Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2);

    SECTION("Proper Assignment") {
        REQUIRE(test_edge.GetStartNode()->GetValue() == 12);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 13);
        REQUIRE_FALSE(test_edge.IsTwoSided());
    }

    SECTION("Changing Initial Nodes") {
        node_1.SetValue(45);
        node_2.SetValue(15);
        REQUIRE(test_edge.GetStartNode()->GetValue() == 45);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 15);
    }

    SECTION("Changing From Nodes From Reference") {
        test_edge.GetStartNode()->SetValue(45);
        test_edge.GetEndNode()->SetValue(15);
        REQUIRE(test_edge.GetStartNode()->GetValue() == 45);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 15);
    }
}

TEST_CASE("Three Constructor Test") {
    Node node_1(12);
    Node node_2(13);
    
    Edge test_edge(&node_1, &node_2, true);
    
    SECTION("Proper Assignment") {
        REQUIRE(test_edge.GetStartNode()->GetValue() == 12);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 13);
        REQUIRE(test_edge.IsTwoSided() == true);
    }
    
    SECTION("Changing Values") {
        node_1.SetValue(45);
        node_2.SetValue(15);
        REQUIRE(test_edge.GetStartNode()->GetValue() == 45);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 15);
    }

    SECTION("Changing From Nodes From Reference") {
        test_edge.GetStartNode()->SetValue(45);
        test_edge.GetEndNode()->SetValue(15);
        REQUIRE(test_edge.GetStartNode()->GetValue() == 45);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 15);
    }
}

TEST_CASE("Changing Start Node Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, false);

    SECTION("Proper Assignment") {
        REQUIRE(test_edge.GetStartNode()->GetValue() == 12);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 13);
    }
    
    SECTION("Proper Changing Values") {
        Node test_node(135, vec2(13,13));
        test_edge.SetStartNode(&test_node);
        REQUIRE(test_edge.GetStartNode()->GetValue() == 135);
        REQUIRE(test_edge.GetStartNode()->GetLocation() == vec2(13,13));
    }
}

TEST_CASE("Changing End Node Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, false);

    SECTION("Proper Assignment") {
        REQUIRE(test_edge.GetStartNode()->GetValue() == 12);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 13);
    }

    SECTION("Proper Changing Values") {
        Node test_node(135, vec2(13,13));
        test_edge.SetEndNode(&test_node);
        REQUIRE(test_edge.GetEndNode()->GetValue() == 135);
        REQUIRE(test_edge.GetEndNode()->GetLocation() == vec2(13,13));
    }
}

TEST_CASE("Changing the Weight Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, false);
    REQUIRE(test_edge.GetWeight() == -1);
    test_edge.SetWeight(12);
    REQUIRE(test_edge.GetWeight() == 12);
}

TEST_CASE("Changing the Edge Color Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, false);
    REQUIRE(test_edge.GetEdgeColor() == ci::Color("blue"));
    test_edge.SetEdgeColor(ci::Color("yellow"));
    REQUIRE(test_edge.GetEdgeColor() == ci::Color("yellow"));
}

TEST_CASE("ChangeToOneSided Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, true);
    test_edge.ChangeToOneSided();
    
    REQUIRE(test_edge.IsTwoSided() == false);
}

TEST_CASE("ChangeToTwoSided Test") {
    Node node_1(12);
    Node node_2(13);

    Edge test_edge(&node_1, &node_2, false);
    test_edge.ChangeToTwoSided();

    REQUIRE(test_edge.IsTwoSided() == true);
}
