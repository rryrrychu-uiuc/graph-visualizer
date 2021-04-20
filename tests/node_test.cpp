#include <catch2/catch.hpp>
#include <core/node.h>

TEST_CASE("Constructor Test"){
    Node test_node(10, vec2(10,10));
    REQUIRE(test_node.GetValue() == 10);
    REQUIRE(test_node.GetLocation() == vec2(10, 10));
}

TEST_CASE("Copy Constructor Test"){
    Node test_node1(10, vec2(10,10));
    Node test_node2(test_node1);
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    
    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
}

TEST_CASE("Copy Operator Test") {
    Node test_node1(10, vec2(10, 10));
    Node test_node2 = test_node1;
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));

    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
}

TEST_CASE("Move Constructor Test"){
    Node test_node1(10, vec2(10, 10));
    Node test_node2(std::move(test_node1));

    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));

    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
}

TEST_CASE("Move Operator Test"){
    Node test_node1(10, vec2(10, 10));
    Node test_node2 = std::move(test_node1);

    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));

    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
}

TEST_CASE("SetLocation Test"){
    Node test_node1(10, vec2(10,10));
    test_node1.SetLocation(vec2(12,12));
    REQUIRE(test_node1.GetLocation() == vec2(12, 12));
}

TEST_CASE("SetValue Test"){
    Node test_node1(10, vec2(10,10));
    test_node1.SetValue(20);
    REQUIRE(test_node1.GetValue() == 20);
}

TEST_CASE("AddAdjNode Test") {
    Node test_node1(10, vec2(10,10));
    Node test_node2(20, vec2(12,12));
    
    test_node1.AddAdjacentNode(&test_node2);
    
    vector<Node*> values = test_node1.GetAdjacentNodes();
    
    for(size_t index = 0; index < values.size(); index++) {
        values[index]->SetValue(14);
        REQUIRE(test_node2.GetValue() == 14);
    }
}

TEST_CASE("IsAdjacent Test") {
    Node test_node1(10, vec2(10,10));
    Node test_node2(20, vec2(12,12));
    Node test_node3(30, vec2(13, 14));
    Node test_node4(30, vec2(233, 14));
    Node test_node5(35, vec2(233, 14));
    test_node1.AddAdjacentNode(&test_node3);
    test_node1.AddAdjacentNode(&test_node4);
    test_node1.AddAdjacentNode(&test_node5);
    SECTION("Not Adjacent") {
        REQUIRE_FALSE(test_node1.IsAdjacentTo(&test_node2));
    }
    SECTION("Is Adjacent") {
        REQUIRE(test_node1.IsAdjacentTo(&test_node3));
        REQUIRE(test_node1.IsAdjacentTo(&test_node4));
        REQUIRE(test_node1.IsAdjacentTo(&test_node5));
    }
}
