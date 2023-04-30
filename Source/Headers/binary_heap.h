#pragma once
#include <string>

/// @brief Data structure of binary tree type
class BinaryHeap
{
private:
    int* heap; //heap array
    int size; //elements amount in heap

    /// @brief Function will return index of left child of given parent
    /// @param parentIndex Parent index
    /// @return left child index or -1 if there is none
    int GetIndexOfLeftChild(int parentIndex);

    /// @brief Function will return index of right child of given parent
    /// @param parentIndex Parent index
    /// @return right child index or -1 if there is none
    int GetIndexOfRightChild(int parentIndex);

    /// @brief Function will return index of parent of given child
    /// @param current Child index
    /// @return parent index or -1 if there is none
    int GetIndexOfParent(int current);

    /// @brief Function will recursively call itself in order to create string representation of tree structure
    /// @param prefix Custom prefix to initialize each new element. Empty as default
    /// @param index Index of given element. Root index as default 
    /// @param isRight If given element is right child
    /// @param con final string 
    void GetTreeAsString(std::string prefix, int index, bool isRight, std::string& con);

    /// @brief Function will balance heap using floyd alg
    void PerformFloyd();

    /// @brief Function will change size of heap, if newSize is smaller than previous elements will be cut from end. NOTE: size global param will be updated!
    /// @param newSize new size of heap
    void ChangeHeapSize(int newSize);

public:
    /// @brief CTOR
    BinaryHeap();

    /// @brief CTOR, will add each element from arr to data structure
    /// @param size size of arr
    /// @param arr arr to get data from
    BinaryHeap(int size, int* arr);

    /// @brief DTOR, will free resources
    ~BinaryHeap();

    /// @brief Function will push all elements from given array
    /// @param count size of array
    /// @param arr array to push from
    void PushAll(int count, int* arr);

    /// @brief Function will push all elements from given array using Floyd alg
    /// @param count size of array
    /// @param arr array to push from
    void PushAllFloyd(int count, int* arr);

    /// @brief Function will push new element in correct position
    /// @param num Number to push
    void Push(int num);

    /// @brief Function will return root element (with index 0) and correctly reshape structure
    /// @return Result number taken from structure root
    /// @exception will throw exception if heap size is smaller than 1
    int PopHead();

    /// @brief Function will remove all stack elements
    void RemoveAll();

    /// @brief Function will find number in structure
    /// @param num number to find
    /// @return true if given number is in structure, false otherwise
    bool Find(int num);

    /// @brief 
    /// @return amount of elements in heap
    int GetSize();

    /// @brief 
    /// @return This data structure in string representation
    std::string ToString();
};
