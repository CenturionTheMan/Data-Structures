#pragma once
#include <string>
#include "binary_search_tree.h"

/// @brief Node class used for representing nodes in binary tree
struct NodeRBT:public Node
{
    char color;

    /// @brief CTOR
    NodeRBT();
    NodeRBT(char color);
};


/// @brief Data structure of type Red black tree
class RedBlackTree:protected BinarySearchTree
{
private:
    /// @brief Will cast Node to RBTNode
    /// @param n node to cast
    /// @return RBTNode
    NodeRBT* CastNode(Node* n);

    /// @brief Function will recursively called itself (DFS alg) in order to create string which represents binary tree structure
    /// @param prefix Prefix for each line (should be set as "" in first call)
    /// @param curr Current node (node from which tree is printed)
    /// @param isRight whether given node is right child
    /// @param con result string
    void GetTreeAsString(std::string prefix, NodeRBT* curr, bool isRight, std::string& con);

    /// @brief Will fix colors in tree after addition
    /// @param node Added node
    void FixColorsInTreeAfterAddition(NodeRBT* node);

    /// @brief Will fix colors after deletion
    /// @param node Node with double color (wrong position)
    /// @param doubleColor Color of given node (Red-Black or Black-Black)
    void FixColorsInTreeAfterDeletion(NodeRBT* node);

    /// @brief Will swap references for given nodes. CHILD->LEFT wont be updated
    /// @param parent parent node
    /// @param child child node
    void Transplant(NodeRBT* parent, NodeRBT* child);
public:
    /// @brief CTOR - will initialize params
    RedBlackTree();

    /// @brief CTOR, will add each element from arr to data structure
    /// @param size size of arr
    /// @param arr arr to get data from
    RedBlackTree(int size, int* arr);

    /// @brief DTOR - will free memory
    ~RedBlackTree();

    /// @brief Function will add all elements from array to red black tree
    /// @param count size of array
    /// @param arr array to add numbers from
    void AddAll(int count, int* arr);

    /// @brief Function will add new value to tree (at correct place and with correct color)
    /// @param val Value to add
    /// @return Pointer to just added node
    void Add(int val);

    /// @brief Function will find node with given value in tree
    /// @param val value to find
    /// @return Pointer to founded node in tree, will be NULL if given value does not exists
    NodeRBT* Find(int val);

    /// @brief Function will remove given value from tree
    /// @param val Value to remove
    /// @return true if success, false otherwise
    bool Remove(int val);

    /// @brief Function will remove given node from tree
    /// @param node node to remove
    /// @return true if success, false otherwise
    bool Remove(NodeRBT* node);

    /// @brief Function will remove all nodes from tree
    void RemoveAll();

    /// @brief 
    /// @return tree as string
    std::string ToString();
};

