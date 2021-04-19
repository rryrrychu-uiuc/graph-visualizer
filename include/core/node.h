#pragma once
#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H

#include <glm/vec2.hpp>
#include "cinder/gl/gl.h"

using ci::vec2;

template <typename ElementType>
class Node {
public:
    
    Node(const Node& source);

    Node(Node&& source) noexcept;

    ~Node();

    Node<ElementType>& operator=(const Node<ElementType>& source);

    Node<ElementType>& operator=(Node<ElementType>&& source) noexcept;
    
    Node(ElementType data, vec2 location);
    
    vec2 GetLocation();
    
    ElementType GetValue();
    
    void SetLocation(vec2 location);
    
    void SetValue(ElementType value);
    
private:
    ElementType data_;
    vec2 location_;
};

#endif //FINAL_PROJECT_NODE_H
