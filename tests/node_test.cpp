#include <catch2/catch.hpp>
#include <core/node.h>

TEST_CASE("One Param Constructor Test"){
    Node test_node(10);
    REQUIRE(test_node.GetValue() == 10);
    REQUIRE(test_node.GetLocation() == vec2(-1, -1));
    REQUIRE(test_node.GetColor() == ci::Color("orange"));
}

TEST_CASE("Two Param Constructor Test"){
    Node test_node(10, vec2(10,10));
    REQUIRE(test_node.GetValue() == 10);
    REQUIRE(test_node.GetLocation() == vec2(10, 10));
    REQUIRE(test_node.GetColor() == ci::Color("orange"));
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
    REQUIRE(test_node6.GetColor() == ci::Color("orange"));
    
    SECTION("Test No change between values") {
        test_node1.SetValue(45);
        test_node1.SetLocation(vec2(15,15));
        test_node1.SetColor(ci::Color("green"));
        REQUIRE(test_node1.GetValue() == 45);
        REQUIRE(test_node1.GetLocation() == vec2(15, 15));
        REQUIRE(test_node1.GetColor() == ci::Color("green"));
        REQUIRE(test_node6.GetValue() == 10);
        REQUIRE(test_node6.GetLocation() == vec2(10, 10));
        REQUIRE(test_node6.GetColor() == ci::Color("orange"));
    }
}

TEST_CASE("Copy Operator Test") {
    Node test_node1(10, vec2(10, 10));
    Node test_node2 = test_node1;
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));

    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    test_node1.SetColor(ci::Color("green"));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));
}

TEST_CASE("Move Constructor Test"){
    Node test_node1(10, vec2(10, 10));
    Node test_node2(std::move(test_node1));

    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));
    
    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    test_node1.SetColor(ci::Color("green"));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));
}

TEST_CASE("Move Operator Test"){
    Node test_node1(10, vec2(10, 10));
    Node test_node2 = std::move(test_node1);

    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));

    test_node1.SetValue(20);
    test_node1.SetLocation(vec2(12,12));
    test_node1.SetColor(ci::Color("green"));
    REQUIRE(test_node2.GetValue() == 10);
    REQUIRE(test_node2.GetLocation() == vec2(10, 10));
    REQUIRE(test_node2.GetColor() == ci::Color("orange"));
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

TEST_CASE("SetColor Test") {
    Node test_node1(10, vec2(10,10));
    REQUIRE(test_node1.GetColor() == ci::Color("orange"));
    test_node1.SetColor(ci::Color("green"));
    REQUIRE(test_node1.GetColor() == ci::Color("green"));
}

TEST_CASE("Equals Operator Test") {
    SECTION("Not equals both parameters") {
        Node test_node1(10, vec2(10,10));
        Node test_node2(20, vec2(12,12));
        REQUIRE_FALSE(test_node1 == test_node2);
    }

    SECTION("Not equals value") {
        Node test_node1(10, vec2(10,10));
        Node test_node2(20, vec2(10,10));
        REQUIRE_FALSE(test_node1 == test_node2);
    }

    SECTION("Not equals location") {
        Node test_node1(20, vec2(10,10));
        Node test_node2(20, vec2(12,12));
        REQUIRE_FALSE(test_node1 == test_node2);
    }

    SECTION("Equals") {
        Node test_node1(10, vec2(10,10));
        Node test_node2(10, vec2(10,10));
        REQUIRE(test_node1 == test_node2);
    }
}

TEST_CASE("Less Than Operator Test") {
    Node test_node1(10, vec2(10,10));
    Node test_node2(20, vec2(12,12));
    
    SECTION("Value less") {
        REQUIRE(test_node1 < test_node2);
    }
    
    SECTION("Location x less") {
        test_node2.SetValue(10);
        test_node2.SetLocation(vec2(5, 12));
        REQUIRE(test_node2 < test_node1);
    }

    SECTION("Location y less") {
        test_node2.SetValue(10);
        test_node2.SetLocation(vec2(10, 12));
        REQUIRE(test_node1 < test_node2);
    }
}
