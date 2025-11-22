#ifndef NODE_H
#define NODE_H

template<class T>
class LinkedListNode {
private:
public:
    T value;
    LinkedListNode* next;
    explicit LinkedListNode(T Value);
    ~LinkedListNode();
};

#endif

