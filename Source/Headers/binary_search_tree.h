#pragma once
#include <string>
#include <cmath>


/// @brief Node class used for representing nodes in binary tree
struct Node
{

    Node* left;
    Node* right;
    Node* parent;
    int value;

    /// @brief CTOR
    Node();

    /// @brief CTOR
    /// @param left 
    /// @param right 
    /// @param parent 
    /// @param value 
    Node(Node* left, Node* right, Node* parent, int value);
    Node(int value);
};


/// @brief Data structure of type Red black tree
class BinarySearchTree
{
protected:
    Node* root; //Root reference

    /// @brief Function will recursively called itself (DFS alg) in order to create string which represents binary tree structure
    /// @param prefix Prefix for each line (should be set as "" in first call)
    /// @param curr Current node (node from which tree is printed)
    /// @param isRight whether given node is right child
    /// @param con result string
    void GetTreeAsString(std::string prefix, Node* curr, bool isRight, std::string& con);

    /// @brief Function will free up space from given node and all its children
    /// @param toDelete Begin node to delete
    void RecursivelyDeleteNodes(Node* toDelete);

    /// @brief Function will find node with smallest value in tree structure which root is given as param
    /// @param node Node which will be treated as root (Subtree)
    /// @return Pinter to node with smallest value in given subtree, or NULL if begin param is NULL
    Node* FindMin(Node* node);

    /// @brief Function will find node with largest value in tree structure which root is given as param
    /// @param node Node which will be treated as root (Subtree)
    /// @return Pinter to node with largest value in given subtree, or NULL if begin param is NULL
    Node* FindMax(Node* node);

    /// @brief Function will delete given node from tree.
    /// @param node Node to remove
    /// @return Node which position in tree changed in order to remove given node
    Node* RemoveAndReturnChanged(Node* node);
public:
    /// @brief CTOR - will initialize params
    BinarySearchTree();

    /// @brief CTOR, will add each element from arr to data structure
    /// @param size size of arr
    /// @param arr arr to get data from
    BinarySearchTree(int size, int* arr);

    /// @brief DTOR - will free memory
    ~BinarySearchTree();

    /// @brief Function will add all elements from array to bst
    /// @param count size of array
    /// @param arr array to add numbers from
    void AddAll(int count, int* arr);

   
    /// @brief Function will add new value to tree (at correct place)
    /// @param val Value to add
    /// @return Pointer to just added node
    Node* Add(int val);

    /// @brief Function will find node with given value in tree
    /// @param val value to find
    /// @return Pointer to founded node in tree, will be NULL if given value does not exists
    Node* Find(int val);

    /// @brief Function will find node with the smallest value
    /// @return Pointer to node with the smallest value or NULL if tree is empty
    Node* FindMin();

    /// @brief Function will find node with the largest value
    /// @return Pointer to node with the largest value or NULL if tree is empty
    Node* FindMax();

    /// @brief Function will rotate left child of given node along this node
    /// @param pivot Pivot node to rotate along
    /// @return true if rotate was made, false otherwise
    bool RotateRight(Node* pivot);

    /// @brief Function will find node with given value and rotate left child of given node along this node
    /// @param val Value of node to find
    /// @return true if rotate was made, false otherwise
    bool RotateRight(int val);

    /// @brief Function will rotate right child of given node along this node
    /// @param pivot Pivot node to rotate along
    /// @return true if rotate was made, false otherwise
    bool RotateLeft(Node* pivot);

    /// @brief Function will find node with given value and rotate right child of given node along this node
    /// @param val Value of node to find
    /// @return true if rotate was made, false otherwise
    bool RotateLeft(int val);

    /// @brief Function will perform DSW algorithm
    void PerformDSW();

    /// @brief Function will find Node which is next (in size )
    /// @param current Reference node
    /// @return Pointer to next node or NULL if there is no bigger node
    Node* FindSuccessor(Node* current);

    /// @brief Function will remove given value from tree
    /// @param val Value to remove
    /// @return true if success, false otherwise
    bool Remove(int val);

    /// @brief Function will remove given node from tree
    /// @param node node to remove
    /// @return true if success, false otherwise
    bool Remove(Node* node);

    /// @brief Function will remove all nodes from tree
    void RemoveAll();

    /// @brief 
    /// @return tree as string
    std::string ToString();
};

