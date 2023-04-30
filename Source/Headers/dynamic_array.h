#pragma once
#include <string>

/// @brief Class used for creating and handling dynamic array
class DynamicArray
{
private:
    int size; //amount of elements in array 
    int* array; //array pointer for storing data
public:
    /// @brief CTOR, will set size to 0 and array to new int array of size 0 
    DynamicArray();

    /// @brief CTOR, will set size and will add each element from arr as last
    /// @param size size to set
    /// @param arr arr to get data from
    DynamicArray(int size, int* arr);

    /// @brief DTOR, will free taken space
    ~DynamicArray();

    /// @return amount of elements in array
    int GetSize();
    
    /// @brief Will set size and will add each element from arr as last
    /// @param size size to set
    /// @param arr arr to get data from 
    /// @return true if success, false otherwise
    bool AddAll(int size, int* arr);

    /// @brief Will add given integer at index 0. All numbers indexes will be pushed by one
    /// @param num Number to add
    /// @return true if success, false otherwise
    bool AddFirst(int num);

    /// @brief Will add given integer at the end of array
    /// @param num Number to add
    /// @return true if success, false otherwise
    bool AddLast(int num);

    /// @brief Will push elements from given index to the end by one and will add new number at given index
    /// @param num Number to add
    /// @param index Index to put number at
    /// @return true if success, false otherwise
    bool AddAtPos(int index, int num);

    /// @brief Will remove item from beginning
    /// @return true if success, false otherwise
    bool RemoveFirst();

    /// @brief Will remove item from ending
    /// @return true if success, false otherwise
    bool RemoveLast();

    /// @brief Will remove item from given position
    /// @param index Index to put number at
    /// @return true if success, false otherwise
    bool RemoveAtPos(int index);

    /// @brief Will remove all elemets in array
    void RemoveAll();

    /// @brief Will return number at given index
    /// @param index Index to get number from
    /// @return number at given position
    /// @exception will throw exception if given index is out of array bounds
    int GetAtPos(int index);

    /// @brief Function will go through all elements in array and will return index of searched number.
    ///        Returned value will be equal to index value of first founded number
    /// @param number Number to find
    /// @return index of given number in array or -1 if there is none
    int FindNumber(int number);

    /// @brief Function will convert array to string representation
    /// @return String constructed of array content
    std::string ToString();
};