#pragma once
#include <string>

/// @brief single item in list
struct ListItem
{
    int value;
    ListItem* next;
    ListItem* prev;

    /// @brief CTOR
    /// @param value Item value
    /// @param next Next item in list
    /// @param prev Previous item in list
    ListItem(int value, ListItem* next, ListItem* prev);
};

/// @brief Double linked list - Data structure
class DoubleLinkedList
{
    private:
        int size; //Amount of items in list
        ListItem* head; //First item in list
        ListItem* tail; //Last item in list

        /// @brief Function will setup first item in list
        /// @param num Value of item
        void InitializeFirstElement(int num);

        /// @brief Will find item with given index. THIS FUNCTION DOES NOT CHECK IF INDEX IS VALID!
        /// @param index Index of given item
        /// @return item with given index
        ListItem* GetItemByIndex(int index);

    public:
        /// @brief CTOR
        DoubleLinkedList();

        /// @brief CTOR, will add each element from arr to data structure
        /// @param size size of arr
        /// @param arr arr to get data from
        DoubleLinkedList(int size, int* arr);

        /// @brief DTOR
        ~DoubleLinkedList();

        /// @brief Function will add all given array to list
        /// @param count array size
        /// @param arr array to add
        void AddAll(int count, int* arr);

        /// @brief Will add item at the beginning of list (head)
        /// @param num Item value
        void AddFirst(int num);

        /// @brief Will add item at the end of list (tail)
        /// @param num Item value
        void AddLast(int num);

        /// @brief Will add item at given index and push all needed items by one place
        /// @param index Index to put item at
        /// @param num Item value
        /// @return true if success, false otherwise
        bool AddAtPos(int index, int num);

        /// @brief Will remove first item in list
        /// @return true if success, false otherwise
        bool RemoveFirst();

        /// @brief Will remove last item in list
        /// @return true if success, false otherwise
        bool RemoveLast();

        /// @brief Will remove item at given index
        /// @param index Idex to remove file at
        /// @return true if success, false otherwise
        bool RemoveAtPos(int index);

        /// @brief Will remove all elements in array
        void RemoveAll();

        /// @brief Function will get first item in list as num param
        /// @return first item in list
        /// @exception will throw exception if list size is smaller than 1
        int GetFirst();

        /// @brief Function will get last item in list
        /// @return last item in list
        /// @exception will throw exception if list size is smaller than 1
        int GetLast();

        /// @brief Function will get item at given index and return its value
        /// @param index Index to get
        /// @return item at given index
        /// @exception will throw exception if given index is out of list size bounds
        int GetAtPos(int index);

        /// @brief Will find given number in list
        /// @param numberToFind Number to search for
        /// @return index of given number or -1 if there is none
        int FindNumber(int numberToFind);

        /// @brief 
        /// @return will return amount of elements in list
        int GetSize();

        /// @brief 
        /// @return will return list content as string (in order from first to last)
        std::string ToStringForward();

        /// @brief 
        /// @return will return list content as string (in order from last to first)
        std::string ToStringBackward();
};


