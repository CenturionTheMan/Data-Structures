#include <iostream>
#include <string>
#include "Headers/dynamic_array.h"
#include "Headers/double_linked_list.h"
#include "Headers/binary_heap.h"
#include "Headers/read_black_tree.h"
#include "Headers/menu_console.h"
#include "Headers/time_tester.h"
#include "Headers/helpers.h"

void RunMainMenu();
void PerformTests();

int main()
{
    char input;
    do
    {
        std::cout<<"[1] - MENU" <<std::endl;
        std::cout<<"[2] - TESTS" <<std::endl;
        std::cout<<"Input: ";
        std::cin>>input;
    } while (input != '1' && input != '2');
    if(input == '1')
    {
        RunMainMenu();
    }
    else
    {
        PerformTests();
    }

    return 0;
}


void PerformTests()
{
    std::string outputDirectoryPath = "";
    int repPertest;
    int maxElementAmount;
    int samplesAmount;

    std::cout<<"Repeat amount per test: ";
    std::cin>>repPertest;

    std::cout<<"Max element amount in structure: ";
    std::cin>>maxElementAmount;

    std::cout<<"Samples amount: ";
    std::cin>>samplesAmount;

    std::cout<<"Path for output directory: ";
    std::cin>>outputDirectoryPath;

    Tests::PerformAllTests(repPertest, maxElementAmount, samplesAmount, outputDirectoryPath);


    std::cin.get();
    std::cin.get();
}

void RunMainMenu()
{
    DynamicArray array;
    DoubleLinkedList list;
    BinaryHeap heap;
    BinarySearchTree bst;
    RedBlackTree rbt;

    MenuConsole menu;

    MainMenuOptions menuRes;
    do
    {
        menuRes = menu.DisplayMainMenu();
        switch (menuRes)
        {
        case DYNAMIC_ARRAY:{
            ArrayAndListMenuOptions res;
            std::cout<<"Array:\n";
            std::cout<<array.ToString() + "========================================\n\n";
            do
            {
                res = menu.DisplayArrayMenu();
                menu.HandleDataStructInput(res, array);
            } while (res != ArrayAndListMenuOptions::GO_TO_MAIN_MENU_AL);
            break;
            }

        case DOUBLE_LINED_LIST:{
            ArrayAndListMenuOptions res;
            std::cout<<"List from first to last:\n";
            std::cout<<list.ToStringForward();
            std::cout<<"List from last to first:\n";
            std::cout<<list.ToStringBackward();
            std::cout<<"========================================\n\n";
            do
            {
                res = menu.DisplayListMenu();
                menu.HandleDataStructInput(res, list);
            } while (res != ArrayAndListMenuOptions::GO_TO_MAIN_MENU_AL);
            break;
        }

        case BINARY_HEAP:{
            HeapMenuOptions res;
            std::cout<<"Heap:\n";
            std::cout<<heap.ToString() + "========================================\n\n";
            do
            {
                res = menu.DisplayHeapMenu();
                menu.HandleDataStructInput(res, heap);
            } while (res != HeapMenuOptions::GO_TO_MAIN_MENU_H);
            break;
        }

        case BINARY_SEARCH_TREE:{
            TreeMenuOptions res;
            std::cout<<"Binary search tree:\n";
            std::cout<<bst.ToString() + "========================================\n\n";
            do
            {
                res = menu.DisplayBinarySearchTreeMenu();
                menu.HandleDataStructInput(res, bst);
            } while (res != TreeMenuOptions::GO_TO_MAIN_MENU_T);
            break;
        }

        case RED_BLACK_TREE:{
            TreeMenuOptions res;
            std::cout<<"Red black tree:\n";
            std::cout<<rbt.ToString() + "========================================\n\n";
            do
            {
                res = menu.DisplayRedBlackTreeMenu();
                menu.HandleDataStructInput(res, rbt);
            } while (res != TreeMenuOptions::GO_TO_MAIN_MENU_T);
            break;
        }

        case READ_DATA_FROM_FILE_ALL:{
            menu.ReadDataFromFileToAllStructures(array, list, heap, bst, rbt);
            break;
        }
    }
    } while (menuRes != MainMenuOptions::EXIT);
    
    std::cout<<"APP EXITED";
}
