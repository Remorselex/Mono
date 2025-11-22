//
// Created by Remorselex on 08.02.2025.
//
#ifndef DTSTRCT_TREE_UTILS_H
#define DTSTRCT_TREE_UTILS_H

#include "iostream"
#include "../TreeNode.h"

namespace TreeUtils {
    template <typename T>
    void nodePrinter(const std::string& NodeSignature, Node<T>* NodeToPrint);
}

namespace TreeUtils {
    template <typename T>
    inline void nodePrinter(const std::string& NodeSignature, Node<T>* NodeToPrint) {
        std::cout << NodeSignature << ": " << NodeToPrint->Value << std::endl
                  << "left node: " << NodeToPrint->LeftNode << std::endl
                  << "right node: " << NodeToPrint->RightNode;
    }
}
#endif
