//
// Created by Remorselex on 08.02.2025.
//
#ifndef DTSTRCT_TREE_NODE_H
#define DTSTRCT_TREE_NODE_H

template <class T>
struct Node {
    T Value;
    Node<T>* LeftNode;
    Node<T>* RightNode;

    explicit Node(T& value);
    ~Node();
};

template<class T>
Node<T>::Node(T& value): Value(value), LeftNode(nullptr), RightNode(nullptr) {}

template <typename T>
Node<T>::~Node() {
    if(LeftNode) {
        delete LeftNode;
        LeftNode = nullptr;
    }

    if(RightNode) {
        delete RightNode;
        RightNode = nullptr;
    }

}

#endif
