#include "Headers/double_linked_list.h"
#include <stdexcept>

#pragma region CTOR_DTOR
DoubleLinkedList::DoubleLinkedList()
{
    DoubleLinkedList::size = 0;
    DoubleLinkedList::head = NULL;
    DoubleLinkedList::tail = NULL;
}

DoubleLinkedList::DoubleLinkedList(int size, int* arr)
{
    DoubleLinkedList::size = 0;
    DoubleLinkedList::head = NULL;
    DoubleLinkedList::tail = NULL;
    for (int i = 0; i < size; i++)
    {
        DoubleLinkedList::AddLast(arr[i]);
    }
}

DoubleLinkedList::~DoubleLinkedList()
{
    DoubleLinkedList::RemoveAll();
}
#pragma endregion CTOR_DTOR

#pragma region PRIVATE
void DoubleLinkedList::InitializeFirstElement(int num)
{
    ListItem* item = new ListItem(num, NULL, NULL);
    DoubleLinkedList::head = item;
    DoubleLinkedList::tail = item;
    DoubleLinkedList::size++;
}

ListItem* DoubleLinkedList::GetItemByIndex(int index)
{
    ListItem* toPush;
    if(index <= DoubleLinkedList::size/2)
    {   
        toPush = head;
        for (int i = 0; i < index; i++) //Find item at given index
        {
            toPush = toPush->next;
        }
    }
    else
    {
        toPush = tail;
        for (int i = 0; (DoubleLinkedList::size - i - 1) > index; i++) //Find item at given index
        {
            toPush = toPush->prev;
        }
    }
    return toPush;
}
#pragma endregion PRIVATE

#pragma region PUBLIC
void DoubleLinkedList::AddAll(int count, int* arr)
{
    for (int i = 0; i < count; i++)
    {
        DoubleLinkedList::AddLast(arr[i]);
    }   
}


void DoubleLinkedList::AddFirst(int num)
{   
    if(DoubleLinkedList::size == 0){
        InitializeFirstElement(num);
        return;
    }
    ListItem* item = new ListItem(num, DoubleLinkedList::head, NULL);
    DoubleLinkedList::head->prev = item;
    DoubleLinkedList::head = item;
    DoubleLinkedList::size++;    
}

void DoubleLinkedList::AddLast(int num)
{    
    if(DoubleLinkedList::size == 0){
        InitializeFirstElement(num);
        return;
    }

    ListItem* item = new ListItem(num, NULL, DoubleLinkedList::tail);
    DoubleLinkedList::tail->next = item;
    DoubleLinkedList::tail = item;
    DoubleLinkedList::size++; 
}

bool DoubleLinkedList::AddAtPos(int index, int num)
{
    if(index < 0 || index > size)
    {
        return false;
    }
    else if(index==0)
    {
        AddFirst(num);
        return true;
    }
    else if(index==DoubleLinkedList::size)
    {
        AddLast(num);
        return true;
    }

    ListItem* toPush = GetItemByIndex(index);

    //swap references
    ListItem* item = new ListItem(num, toPush, toPush->prev);
    toPush->prev->next = item;
    toPush->prev = item;
    //
    DoubleLinkedList::size++;
    return true;
}

bool DoubleLinkedList::RemoveFirst()
{
    if(DoubleLinkedList::size == 0)
        return false;
    else if(DoubleLinkedList::size == 1)
    {
        DoubleLinkedList::RemoveAll();
        return true;
    }

    ListItem* holder = DoubleLinkedList::head->next;
    holder->prev = NULL;
    delete DoubleLinkedList::head;
    DoubleLinkedList::head = holder;
    DoubleLinkedList::size--;
    return true;
}

bool DoubleLinkedList::RemoveLast()
{
    if(DoubleLinkedList::size == 0)
        return false;
    else if(DoubleLinkedList::size == 1)
    {
        DoubleLinkedList::RemoveAll();
        return true;
    }
    
    ListItem* holder = DoubleLinkedList::tail->prev;
    holder->next = NULL;
    delete DoubleLinkedList::tail;
    DoubleLinkedList::tail = holder;
    DoubleLinkedList::size--;
    return true;
}

bool DoubleLinkedList::RemoveAtPos(int index)
{
    if(DoubleLinkedList::size == 0 || index < 0 || index >= DoubleLinkedList::size)
    {
        return false;
    }
    else if(index==0)
    {
        return RemoveFirst();
    }
    else if(index==DoubleLinkedList::size-1)
    {
        return RemoveLast();
    }
    

    ListItem* toPush = GetItemByIndex(index);

    ListItem* before = toPush->prev;
    ListItem* after = toPush->next;
    before->next = after;
    after->prev = before;
    DoubleLinkedList::size--;
    delete toPush;
    return true;
}

void DoubleLinkedList::RemoveAll()
{
    ListItem* temp = DoubleLinkedList::head;
    while (temp != NULL)
    {
        ListItem* toRemove = temp;
        temp = temp->next;
        delete toRemove;
    }
    DoubleLinkedList::size = 0;
    DoubleLinkedList::head = NULL;
    DoubleLinkedList::tail = NULL;
}

int DoubleLinkedList::GetFirst()
{
    if(DoubleLinkedList::size < 1)
        throw std::out_of_range("Double linked list size is equal to 0!");

    return DoubleLinkedList::head->value;
}

int DoubleLinkedList::GetLast()
{
    if(DoubleLinkedList::size < 1)
        throw std::out_of_range("Double linked list size is equal to 0!");

    return DoubleLinkedList::tail->value;
}

int DoubleLinkedList::GetAtPos(int index)
{
    if(index < 0 || index >= DoubleLinkedList::size)
        throw std::out_of_range("Given index is smaller than 0 or bigger/equal to double linked list size!");

    return GetItemByIndex(index)->value;
}

int DoubleLinkedList::FindNumber(int numberToFind)
{
    ListItem* holder = head;
    for (int i = 0; holder != NULL ; i++)
    {
        if(holder->value == numberToFind)
            return i;
        
        holder = holder->next;
    }
    return -1;
}

int DoubleLinkedList::GetSize()
{
    return DoubleLinkedList::size;
}

std::string DoubleLinkedList::ToStringForward()
{
    std::string res = "[ ";
    ListItem* iterator = DoubleLinkedList::head;
    while (iterator != NULL)
    {
        res += std::to_string(iterator->value);
        iterator = iterator->next;
        if(iterator != NULL) res += ", ";
    }
    res += " ]\n";
    return res;
}

std::string DoubleLinkedList::ToStringBackward()
{
    std::string res = "[ ";
    ListItem* iterator = DoubleLinkedList::tail;
    while (iterator != NULL)
    {
        res += std::to_string(iterator->value);
        iterator = iterator->prev;
        if(iterator != NULL) res += ", ";
    }
    res += " ]\n";
    return res;
}
#pragma endregion PUBLIC

#pragma region LIST_ITEM
ListItem::ListItem(int value, ListItem* next, ListItem* prev)
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}
#pragma endregion LIST_ITEM