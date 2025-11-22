    #ifndef BINARY_THREE_H
    #define BINARY_THREE_H

    #include "TreeNode.h"
    // #include "TreeUtils/TreeUtils.h"

    template <typename T>
    class BinaryTree {
    private:
        Node<T>* RootNode;

        //mb its cringe to split func like this. IDK (Я художник я так вижу)
        void addRecursive(Node<T>*& current, T& value);
        Node<T>* findRecursive(Node<T>* current, T& value);
        void deleteTreeRecursive(Node<T>*& node);

    public:
        BinaryTree();
        ~BinaryTree();

        void add(T value);
        Node<T>* find(T value);
    };

template<typename T>
void BinaryTree<T>::deleteTreeRecursive(Node<T>*& node) {
    if (!node) {
        return;
    }

    if (node->LeftNode) {
        deleteTreeRecursive(node->LeftNode);
    }

    if (node->RightNode) {
        deleteTreeRecursive(node->RightNode);
    }

    std::cout << "Deleting node with value: " << node->Value << std::endl;
    delete node;
    node = nullptr;
}

    template<typename T>
    BinaryTree<T>::~BinaryTree() {
        deleteTreeRecursive(RootNode);
    }

    template<typename T>
    BinaryTree<T>::BinaryTree(): RootNode(nullptr) {}

    template<typename T>
    void BinaryTree<T>::addRecursive(Node<T>*& current, T& value) {
        if(!current) {
            current = new Node<T>(value);
            return;
        }

        if (value < current->Value) {
            addRecursive(current->LeftNode, value);
        } else {
            addRecursive(current->RightNode, value);
        }

    }

    // add(10); add(8); add(7); ... add(n);
    template<typename T>
    void BinaryTree<T>::add(T value) {
        addRecursive(RootNode, value);
    }

    template<typename T>
    Node<T>* BinaryTree<T>::findRecursive(Node<T>* current, T &value) {
    //понять бы что возвращать при find. И для чего он тут нужен.


    //сделать вариатвность обхода ?
        if(current->LeftNode) {
            findRecursive(current->LeftNode);
        }

        if(current->RightNode) {
            findRecursive(current->RightNode);
        }


    }


    template<typename T>
    Node<T>* BinaryTree<T>::find(T value) {
        return  findRecursive(RootNode,value);
    }


    #endif