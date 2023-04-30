#pragma once

#include <iostream>
#include "helpers.h"
#include "file_handler.h"
#include "dynamic_array.h"
#include "double_linked_list.h"
#include "binary_heap.h"
#include "read_black_tree.h"



namespace Tests{
    //Whether should print detailed messages
    const bool PrintMessages = true;

    /// @brief Will perform all tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformAllTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Will perform Array tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformDynamicArrayTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Will perform List tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformDoubleLinkedListTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Will perform Heap tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformHeapTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Will perform BST tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformBstTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Will perform RBT tests
    /// @param perTestReps how many times should test be repeated per size
    /// @param maxElementsAmount maximum elements amount in structure (at final iteration)
    /// @param amountOfSamples how many population sizes need to be achieved (based on it will calculate step size which will be added until achieving maxElementsAmount)
    /// @param outputDirectoryPath path for output directory
    void PerformRbtTests(int perTestReps, int maxElementsAmount, int amountOfSamples, std::string outputDirectoryPath);

    /// @brief Function will test all structure without measuring time (Function is supposed to find bugs)
    void Fun();

    /// @brief Function will setup csv file for test
    /// @param name file name (path)
    /// @return file name
    std::string SetupFile(std::string name);

    /// @brief Function will save population and time taken in given file
    /// @param populationAmount population to save
    /// @param timeTaken time to save
    /// @param fileName file path
    void SavePopAndTimeToFile(int populationAmount, double timeTaken, std::string testType, std::string fileName);

    /// @brief Function will write current*100/all in console
    /// @param current 
    /// @param all 
    void PrintPercentFinish(int current, int all);
}