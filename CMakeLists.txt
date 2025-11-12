cmake_minimum_required(VERSION 3.28)
project(MONO)

set(CMAKE_CXX_STANDARD 17)

add_executable(DtStrct main.cpp
        src/Containers/LinkedList/LinkedListNode.h
        src/Containers/LinkedList/LinkedList.h
        src/Containers/BinaryTree/BinaryTree.h
        src/Containers/BinaryTree/TreeNode.h
        src/Containers/BinaryTree/TreeUtils/TreeUtils.h
        src/Projects/Calculator/Calculator.cpp
        src/Projects/Calculator/facilities.h
        src/Projects/Socket/Socket.cpp
        src/Projects/Socket/Socket.h
)
