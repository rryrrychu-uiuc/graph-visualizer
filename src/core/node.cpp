#include "../../include/core/node.h"

template<typename ElementType>
Node<ElementType>::Node(const Node &source) {
    location_ = source.location_;
    data_ = source.data_;
}

template<typename ElementType>
Node<ElementType>::Node(Node &&source) noexcept {
    location_ = source.location_;
    data_ = source.data_;
    
    source.data_ = nullptr;
}

template<typename ElementType>
Node<ElementType>::~Node() {
    data_ = nullptr;
}

template<typename ElementType>
Node<ElementType> &Node<ElementType>::operator=(const Node<ElementType> &source) {
    Node new_node(source);
    std::swap(location_, source.location_);
    std::swap(data_, source.data_);
}

template<typename ElementType>
Node<ElementType> &Node<ElementType>::operator=(Node<ElementType> &&source) noexcept {
    if(this == &source) {
        return *this;
    }

    location_ = source.location;
    data_ = source.data_;
    return *this;
}

template<typename ElementType>
Node<ElementType>::Node(ElementType data, vec2 location) {
    location_ = location;
    data_ = data;
}

template<typename ElementType>
vec2 Node<ElementType>::GetLocation() {
    return glm::vec2();
}

template<typename ElementType>
ElementType Node<ElementType>::GetValue() {
    return nullptr;
}

template<typename ElementType>
void Node<ElementType>::SetLocation(vec2 location) {

}

template<typename ElementType>
void Node<ElementType>::SetValue(ElementType value) {

}

