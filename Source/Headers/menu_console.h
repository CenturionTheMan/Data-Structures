#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include "file_handler.h"
#include "time_tester.h"
#include "dynamic_array.h"
#include "binary_heap.h"
#include "double_linked_list.h"
#include "read_black_tree.h"

/// @brief Main menu inputs
enum MainMenuOptions{
    EXIT = 0,
    DYNAMIC_ARRAY = 1,
    DOUBLE_LINED_LIST = 2,
    BINARY_HEAP = 3,
    BINARY_SEARCH_TREE = 4,
    RED_BLACK_TREE = 5,
    READ_DATA_FROM_FILE_ALL= 6,
};

/// @brief Array and list inputs
enum ArrayAndListMenuOptions
{
    GO_TO_MAIN_MENU_AL = 0,
    READ_DATA_FROM_FILE_AL = 1,
    ADD_AT_BEGIN = 2,
    ADD_AT_END = 3,
    ADD_AT_INDEX = 4,
    REMOVE_AT_BEGIN = 5,
    REMOVE_AT_END = 6,
    REMOVE_AT_INDEX = 7,
    REMOVE_ALL_AL = 8,
    FIND_NUMBER = 9,
};

/// @brief Heap inputs
enum HeapMenuOptions
{
    GO_TO_MAIN_MENU_H = 0,
    READ_DATA_FROM_FILE_H = 1,
    PUSH = 2,
    POP = 3,
    REMOVE_ALL_H = 4,
    FIND_NUMBER_H = 5,
};

/// @brief BST and RBT inputs
enum TreeMenuOptions
{
    GO_TO_MAIN_MENU_T = 0,
    READ_DATA_FROM_FILE_T = 1,
    ADD = 2,
    REMOVE = 3,
    REMOVE_ALL_T = 4,
    FIND = 5,
    ROTATE_LEFT = 6,
    ROTATE_RIGHT = 7,
    PERFORM_DSW = 8,
};


/// @brief Class used for handling data structures using console
class MenuConsole
{
private:
    /// @brief Timer for time
    Timer timer;

    /// @brief some cons values for printing
    const std::string LINE_SEP = "========================================\n\n";
    const std::string WRONG_INPUT = "WRONG INPUT!\n";
    const std::string VALUE_TO_ADD = "Value to add:\n";
    ///

    /// @brief Function will get input from file
    /// @param size amount of numbers in file (first number in file)
    /// @param arr numbers in file (each next value)
    /// @return true if success, false otherwise
    bool GetDataFromFile(int& size, int*& arr);

    /// @brief Function will try to parse string to int
    /// @param str String to parse
    /// @param val Parsed string (as int)
    /// @return true if success, false otherwise
    bool TryParseToInt(std::string str, int& val);

    /// @brief Function will stop timer and print elapsed microseconds
    void PrintElapsedTime();

public:
    /// @brief CTOR
    MenuConsole();

    /// @brief DTOR
    ~MenuConsole();

    /// @brief Function displays main menu
    /// @return input used bu user (option number)
    MainMenuOptions DisplayMainMenu();

    /// @brief Function will ask for path for file and will try to load its content to all data structures
    /// @param array array to do action on
    /// @param list list to do action on
    /// @param heap heap to do action on
    /// @param bst binary search tree to do action on
    /// @param rbt red black tree to do action on
    void ReadDataFromFileToAllStructures(DynamicArray& array, DoubleLinkedList& list, BinaryHeap& heap, BinarySearchTree& bst, RedBlackTree& rbt);
    
    /// @brief Function will display DynamicArray menu with different options to handle array
    /// @return user input
    ArrayAndListMenuOptions DisplayArrayMenu();

    /// @brief Function will display DoubleLinkedList menu with different options to handle list
    /// @return user input
    ArrayAndListMenuOptions DisplayListMenu();

    /// @brief Function will display BinaryHeap menu with different options to handle heap
    /// @return user input
    HeapMenuOptions DisplayHeapMenu();

    /// @brief Function will display BinarySearchTree menu with different options to handle heap
    /// @return user input 
    TreeMenuOptions DisplayBinarySearchTreeMenu();

    /// @brief Function will display RedBlackTree menu with different options to handle heap
    /// @return user input
    TreeMenuOptions DisplayRedBlackTreeMenu();

    /// @brief Function will do given given operation on list based on user input
    /// @param input user input
    /// @param lists list to do action on
    void HandleDataStructInput(ArrayAndListMenuOptions input, DoubleLinkedList& lists);
    
    /// @brief Function will do given given operation on array based on user input
    /// @param input user input
    /// @param array array to do action on
    void HandleDataStructInput(ArrayAndListMenuOptions input, DynamicArray& array);

    /// @brief Function will do given given operation on heap based on user input
    /// @param input user input
    /// @param heap heap to do action on
    void HandleDataStructInput(HeapMenuOptions input, BinaryHeap& heap);

    /// @brief Function will do given given operation on binary search tree based on user input
    /// @param input user input
    /// @param tree tree to do action on
    void HandleDataStructInput(TreeMenuOptions input, BinarySearchTree& tree);

    /// @brief Function will do given given operation on red black tree based on user input
    /// @param input user input
    /// @param tree tree to do action on
    void HandleDataStructInput(TreeMenuOptions input, RedBlackTree& tree);
};