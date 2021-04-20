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

