#include "Headers/menu_console.h"

#pragma region PRIVATE
bool MenuConsole::GetDataFromFile(int& size, int*& arr)
{
    std::string inputStr ="";

    std::cout<<"Path for file:\n";
    std::cin >> inputStr;

    return ReadDataFromFile(inputStr, size, arr);
}

bool MenuConsole::TryParseToInt(std::string str, int& val)
{
    try
    {
        val = stoi(str);
        return true;
    }
    catch(const std::exception& e){}
    return false;
}

void MenuConsole::PrintElapsedTime()
{
    double microseconds = MenuConsole::timer.TimerStop(MICRO_SECONDS);
    std::cout<<std::fixed << std::setprecision(2)<<"\nTime elapsed: " << microseconds << " [us]" <<std::endl;
}


#pragma endregion PRIVATE

#pragma region CTOR
MenuConsole::MenuConsole()
{

}

MenuConsole::~MenuConsole()
{

}
#pragma endregion CTOR

MainMenuOptions MenuConsole::DisplayMainMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= MENU =======\n");
    printf("[0] Exit\n");
    printf("[1] Dynamic array\n");
    printf("[2] Double linked list\n");
    printf("[3] Binary Heap\n");
    printf("[4] Binary search tree\n");
    printf("[5] Red black tree\n");
    printf("[6] Read data from file to all structures\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 6)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    std::cout<<MenuConsole::LINE_SEP;

    return static_cast<MainMenuOptions>(input);
}

void MenuConsole::ReadDataFromFileToAllStructures(DynamicArray& array, DoubleLinkedList& list, BinaryHeap& heap, BinarySearchTree& bst, RedBlackTree& rbt)
{
    int size;
    int* arr;
    if(!MenuConsole::GetDataFromFile(size, arr))
    {
        std::cout<<"Something went wrong when reading data from file!\n";
        return;
    }
    array.RemoveAll();
    list.RemoveAll();
    heap.RemoveAll();
    bst.RemoveAll();
    rbt.RemoveAll();

    array.AddAll(size, arr);
    list.AddAll(size, arr);
    heap.PushAllFloyd(size, arr);
    bst.AddAll(size, arr);
    rbt.AddAll(size, arr);

    delete[] arr;

    std::cout<<"Data from file was read successfully and added to structures!\n";
}

#pragma region ARRAY

ArrayAndListMenuOptions MenuConsole::DisplayArrayMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= DYNAMIC ARRAY MENU =======\n");
    printf("[0] Go to main menu\n");
    printf("[1] Read data from file\n");
    printf("[2] Add at begin\n");
    printf("[3] Add at end\n");
    printf("[4] Add at index\n");
    printf("[5] Remove at begin\n");
    printf("[6] Remove at end\n");
    printf("[7] Remove at index\n");
    printf("[8] Remove all\n");
    printf("[9] Find number\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 9)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    return static_cast<ArrayAndListMenuOptions>(input);
}

void MenuConsole::HandleDataStructInput(ArrayAndListMenuOptions input, DynamicArray& array)
{
    std::string valStr, indexStr;
    int val, index;
    switch (input)
    {
    case GO_TO_MAIN_MENU_AL:
        {
            std::cout<<MenuConsole::LINE_SEP; 
            return;
        }
    case READ_DATA_FROM_FILE_AL:
        {    
            int size;
            int* arr;
            if(!MenuConsole::GetDataFromFile(size, arr))
            {
                std::cout<<"Something went wrong when reading data from file!\n";
                break;
            }
            array.RemoveAll();
            MenuConsole::timer.StartTimer();
            array.AddAll(size,arr);
            MenuConsole::PrintElapsedTime();
            delete[] arr;
            break;
        }
    case ADD_AT_BEGIN:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                array.AddFirst(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;    
        }
    case ADD_AT_END:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                array.AddLast(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case ADD_AT_INDEX:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            std::cout<<"Index to add at:\n";
            std::cin>>indexStr;
            if(MenuConsole::TryParseToInt(valStr, val) && MenuConsole::TryParseToInt(indexStr, index))
            {
                MenuConsole::timer.StartTimer();
                array.AddAtPos(index, val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case REMOVE_AT_BEGIN:
        {
            MenuConsole::timer.StartTimer();
            array.RemoveFirst();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case REMOVE_AT_END:
        {
            MenuConsole::timer.StartTimer();
            array.RemoveLast();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case REMOVE_AT_INDEX:
        {
            std::cout<<"Index to remove at:\n";
            std::cin>>indexStr;
            if(MenuConsole::TryParseToInt(indexStr, index))
            {
                MenuConsole::timer.StartTimer();
                array.RemoveAtPos(index);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case REMOVE_ALL_AL:{
            MenuConsole::timer.StartTimer();
            array.RemoveAll();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case FIND_NUMBER:
        {
            std::cout<<"Number to find:\n";
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                int res = array.FindNumber(val);
                MenuConsole::PrintElapsedTime();
                std::cout<<"Given number is at index: " + std::to_string(res) + "\n";
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    }

    std::cout<<"Array:\n";
    std::cout<<array.ToString();
    std::cout<<MenuConsole::LINE_SEP; 
}

#pragma endregion ARRAY

#pragma region LIST

ArrayAndListMenuOptions MenuConsole::DisplayListMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= DOUBLE LINKED LIST MENU =======\n");
    printf("[0] Go to main menu\n");
    printf("[1] Read data from file\n");
    printf("[2] Add at begin\n");
    printf("[3] Add at end\n");
    printf("[4] Add at index\n");
    printf("[5] Remove at begin\n");
    printf("[6] Remove at end\n");
    printf("[7] Remove at index\n");
    printf("[8] Remove all\n");
    printf("[9] Find number\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 9)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    return static_cast<ArrayAndListMenuOptions>(input);
}

void MenuConsole::HandleDataStructInput(ArrayAndListMenuOptions input, DoubleLinkedList& list)
{
    std::string valStr, indexStr;
    int val, index;
    switch (input)
    {
    case GO_TO_MAIN_MENU_AL:
        {
            std::cout<<MenuConsole::LINE_SEP; 
            return;
        }
    case READ_DATA_FROM_FILE_AL:
        {    
            int size;
            int* arr;
            if(!MenuConsole::GetDataFromFile(size, arr))
            {
                std::cout<<"Something went wrong when reading data from file!\n";
                break;
            }
            list.RemoveAll();
            MenuConsole::timer.StartTimer();
            list.AddAll(size,arr);
            MenuConsole::PrintElapsedTime();
            delete[] arr;
            break;
        }
    case ADD_AT_BEGIN:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                list.AddFirst(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;    
        }
    case ADD_AT_END:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                list.AddLast(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case ADD_AT_INDEX:
        {
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin>>valStr;
            std::cout<<"Index to add at:\n";
            std::cin>>indexStr;
            if(MenuConsole::TryParseToInt(valStr, val) && MenuConsole::TryParseToInt(indexStr, index))
            {
                MenuConsole::timer.StartTimer();
                list.AddAtPos(index,val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case REMOVE_AT_BEGIN:
        {
            MenuConsole::timer.StartTimer();
            list.RemoveFirst();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case REMOVE_AT_END:
        {
            MenuConsole::timer.StartTimer();
            list.RemoveLast();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case REMOVE_AT_INDEX:
        {
            std::cout<<"Index to remove at:\n";
            std::cin>>indexStr;
            if(MenuConsole::TryParseToInt(indexStr, index))
            {
                MenuConsole::timer.StartTimer();
                list.RemoveAtPos(index);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    case REMOVE_ALL_AL:{
            MenuConsole::timer.StartTimer();
            list.RemoveAll();
            MenuConsole::PrintElapsedTime();
            break;
        }
    case FIND_NUMBER:
        {
            std::cout<<"Number to find:\n";
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                int res = list.FindNumber(val);
                MenuConsole::PrintElapsedTime();
                std::cout<<"Given number is at index: " + std::to_string(res) + "\n";
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        }
    }

    std::cout<<"List from first to last:\n";
    std::cout<<list.ToStringForward();
    std::cout<<"List from last to first:\n";
    std::cout<<list.ToStringBackward();
    std::cout<<MenuConsole::LINE_SEP; 
}

#pragma endregion LIST

#pragma region HEAP

HeapMenuOptions MenuConsole::DisplayHeapMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= BINARY HEAP MENU =======\n");
    printf("[0] Go to main menu\n");
    printf("[1] Read data from file (Floyd)\n");
    printf("[2] Push\n");
    printf("[3] Pop\n");
    printf("[4] Remove all\n");
    printf("[5] Find number\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 5)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    return static_cast<HeapMenuOptions>(input);
}

void MenuConsole::HandleDataStructInput(HeapMenuOptions input, BinaryHeap& heap)
{
    std::string valStr;
    int val;

    switch (input)
    {
     case GO_TO_MAIN_MENU_H:{
            std::cout<<MenuConsole::LINE_SEP; 
        return;
        }
    case READ_DATA_FROM_FILE_H:{    
            int size;
            int* arr;
            if(!MenuConsole::GetDataFromFile(size, arr))
            {
                std::cout<<"Something went wrong when reading data from file!\n";
                break;
            }
            heap.RemoveAll();
            MenuConsole::timer.StartTimer();
            heap.PushAllFloyd(size,arr);
            MenuConsole::PrintElapsedTime();
            delete[] arr;
        break;
        }
    case PUSH:{
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                heap.Push(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case POP:{
            if(heap.GetSize() > 0){
                MenuConsole::timer.StartTimer();
                int val = heap.PopHead();
                MenuConsole::PrintElapsedTime();
                std::cout<<"Head was equal to: " + std::to_string(val) + "\n";
            }
        break;
        }
    case REMOVE_ALL_H:{
            MenuConsole::timer.StartTimer();
            heap.RemoveAll();
            MenuConsole::PrintElapsedTime();
        break;
        }

    case FIND_NUMBER_H:{
            std::cout<<"Number to find:\n";
            std::cin>>valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                bool res = heap.Find(val);
                MenuConsole::PrintElapsedTime();
                if(res == false)
                {
                    printf("Given value is not in heap!\n");
                }
                else
                {
                    printf("Given value is in heap!\n");
                }
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
            break;
        break;
        }
    }

    std::cout<<"Heap:\n";
    std::cout<<heap.ToString();
    std::cout<<MenuConsole::LINE_SEP; 
}

#pragma endregion HEAP

#pragma region BST

TreeMenuOptions MenuConsole::DisplayBinarySearchTreeMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= BINARY SEARCH TREE MENU =======\n");
    printf("[0] Go to main menu\n");
    printf("[1] Read data from file\n");
    printf("[2] Add\n");
    printf("[3] Remove\n");
    printf("[4] Remove all\n");
    printf("[5] Find\n");
    printf("[6] Rotate left\n");
    printf("[7] Rotate right\n");
    printf("[8] Perform DSW\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 8)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    return static_cast<TreeMenuOptions>(input);
}

void MenuConsole::HandleDataStructInput(TreeMenuOptions input, BinarySearchTree& tree)
{
    std::string valStr;
    int val;

    switch (input)
    {
     case GO_TO_MAIN_MENU_H:{
            std::cout<<MenuConsole::LINE_SEP; 
        return;
        }
    case READ_DATA_FROM_FILE_H:{    
            int size;
            int* arr;
            if(!MenuConsole::GetDataFromFile(size, arr))
            {
                std::cout<<"Something went wrong when reading data from file!\n";
                break;
            }
            tree.RemoveAll();
            MenuConsole::timer.StartTimer();
            tree.AddAll(size,arr);
            MenuConsole::PrintElapsedTime();
            delete[] arr;
        break;
        }
    case ADD:{
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.Add(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case REMOVE:{
            std::cout<<"Value to remove: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.Remove(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case REMOVE_ALL_T:{
            MenuConsole::timer.StartTimer();
            tree.RemoveAll();
            MenuConsole::PrintElapsedTime();
        break;
        }
    case FIND:{
            std::cout<<"Value to find: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                Node* findRes = tree.Find(val);
                MenuConsole::PrintElapsedTime();

                if(findRes == NULL)
                {
                    printf("Given value is not in tree!\n");
                }
                else
                {
                    printf("Given value is in tree\n");
                }
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case ROTATE_LEFT:{
            std::cout<<"Value of node to rotate left: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.RotateLeft(tree.Find(val));
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case ROTATE_RIGHT:{
            std::cout<<"Value of node to rotate right: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.RotateRight(tree.Find(val));
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case PERFORM_DSW:{
            MenuConsole::timer.StartTimer();
            tree.PerformDSW();
            MenuConsole::PrintElapsedTime();
        break;
        }
    }

    std::cout<<"Binary search tree:\n";
    std::cout<<tree.ToString();
    std::cout<<MenuConsole::LINE_SEP; 
}

#pragma endregion

#pragma region RBT
TreeMenuOptions MenuConsole::DisplayRedBlackTreeMenu()
{
    int input = -1;
    std::string inputStr ="";
    printf("======= RED BLACK TREE MENU =======\n");
    printf("[0] Go to main menu\n");
    printf("[1] Read data from file\n");
    printf("[2] Add\n");
    printf("[3] Remove\n");
    printf("[4] Remove all\n");
    printf("[5] Find\n");
    printf("Choose option:\n");

    do
    {
        std::cin >> inputStr;
        if (MenuConsole::TryParseToInt(inputStr, input) && input >= 0 && input <= 5)
            break;
        else
            std::cout<<MenuConsole::WRONG_INPUT;

    } while (true);

    return static_cast<TreeMenuOptions>(input);
}

void MenuConsole::HandleDataStructInput(TreeMenuOptions input, RedBlackTree& tree)
{
    std::string valStr;
    int val;

    switch (input)
    {
     case GO_TO_MAIN_MENU_H:{
            std::cout<<MenuConsole::LINE_SEP; 
        return;
        }
    case READ_DATA_FROM_FILE_H:{    
            int size;
            int* arr;
            if(!MenuConsole::GetDataFromFile(size, arr))
            {
                std::cout<<"Something went wrong when reading data from file!\n";
                break;
            }
            tree.RemoveAll();
            MenuConsole::timer.StartTimer();
            tree.AddAll(size,arr);
            MenuConsole::PrintElapsedTime();
            delete[] arr;
        break;
        }
    case ADD:{
            std::cout<<MenuConsole::VALUE_TO_ADD;
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.Add(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case REMOVE:{
            std::cout<<"Value to remove: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                tree.Remove(val);
                MenuConsole::PrintElapsedTime();
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    case REMOVE_ALL_T:{
            MenuConsole::timer.StartTimer();
            tree.RemoveAll();
            MenuConsole::PrintElapsedTime();
        break;
        }
    case FIND:{
            std::cout<<"Value to find: \n";
            std::cin >> valStr;
            if(MenuConsole::TryParseToInt(valStr, val))
            {
                MenuConsole::timer.StartTimer();
                Node* findRes = tree.Find(val);
                MenuConsole::PrintElapsedTime();
                if(findRes == NULL)
                {
                    printf("Given value is not in tree!\n");
                }
                else
                {
                    printf("Given value is in tree\n");
                }
            }
            else
                std::cout<<MenuConsole::WRONG_INPUT;
        break;
        }
    }

    std::cout<<"Binary search tree:\n";
    std::cout<<tree.ToString();
    std::cout<<MenuConsole::LINE_SEP; 
}
#pragma endregion

