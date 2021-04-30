#include <catch2/catch.hpp>
#include <core/node.h>

TEST_CASE("One Param Constructor Test"){
    Node test_node(10);
    REQUIRE(test_node.GetValue() == 10);
    REQUIRE(test_node.GetLocation() == vec2(-1, -1));
}

TEST_CASE("Two Param Constructor Test"){
    Node test_node(10, vec2(10,10));
    REQUIRE(test_node.GetValue() == 10);
    REQUIRE(test_node.GetLocation() == vec2(10, 10));
}

TEST_CASE("Copy Constructor Test"){
    Node test_node1(10, vec2(10,10));
    Node test_node2(20, vec2(12,12));
    Node test_node3(30, vec2(13, 14));
    Node test_node4(30, vec2(233, 14));
    Node test_node5(35, vec2(233, 14));
    
    Node test_node6(test_node1);
    
    REQUIRE(test_node6.GetValue() == 10);
    REQUIRE(test_node6.GetLocation() == vec2(10, 10));
    
    SECTION("Test No change between values") {
        test_node1.SetValue(45);
        test_node1.SetLocation(vec2(15,15));
        REQUIRE(test_node2.GetValue() == 20);
        REQUIRE(test_node2.GetLocation() == vec2(12, 12));
    }

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
