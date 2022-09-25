cmake_minimum_required(VERSION 3.23)
project(CZ4031_Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    CZ4031_Project1 main.cpp 
    B+Tree/Node.cpp 
    B+Tree/Node.h 
    B+Tree/LeafNode.cpp 
    B+Tree/LeafNode.h 
    Address.cpp 
    Address.h 
    B+Tree/BPlusTree.cpp 
    B+Tree/BPlusTree.h
    )
