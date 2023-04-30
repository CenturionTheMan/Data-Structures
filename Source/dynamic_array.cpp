#include "Headers/dynamic_array.h"
#include <stdexcept>
#include <stdio.h>


#pragma region CTOR_DTOR
DynamicArray::DynamicArray(){
    DynamicArray::size = 0;
    DynamicArray::array = new int[0];
}

DynamicArray::DynamicArray(int size, int* arr)
{
    DynamicArray::size = size;
    DynamicArray::array = arr;
}

DynamicArray::~DynamicArray(){
    if(DynamicArray::size > 0)
        delete[] DynamicArray::array;
}
#pragma endregion CTOR_DTOR

#pragma region PUBLIC
int DynamicArray::GetSize() {
    return DynamicArray::size;
}

bool DynamicArray::AddAll(int size, int* arr)
{
    int* newArr = new int[DynamicArray::size + size];

    for (int i = 0; i < DynamicArray::size; i++)
    {
        newArr[i] = DynamicArray::array[i];
    }
    

    int oldIndex = 0;
    for (int newIndex = DynamicArray::size; newIndex < DynamicArray::size + size; newIndex++)
    {
        newArr[newIndex] = arr[oldIndex];
        oldIndex++;
    }

    DynamicArray::size += size;
    delete[] DynamicArray::array;
    DynamicArray::array = newArr;

    return true;
}

bool DynamicArray::AddFirst(int num)
{
    return DynamicArray::AddAtPos(0, num);
}

bool DynamicArray::AddLast(int num)
{
    return DynamicArray::AddAtPos(DynamicArray::size, num);
}

bool DynamicArray::AddAtPos(int index, int num)
{
    if(index < 0 || index > DynamicArray::size)
    {
        return false;
    }

    DynamicArray::size++;
    int* newArr = new int[DynamicArray::size];

    int oldIndex = 0;
    for (int newIndex = 0; newIndex < DynamicArray::size; newIndex++)
    {
        if(newIndex == index)
        {
            newArr[newIndex] = num;
            continue;
        }
        newArr[newIndex] = DynamicArray::array[oldIndex];
        oldIndex++;
    }
 
    delete[] DynamicArray::array;
    DynamicArray::array = newArr;
    return true;
}

bool DynamicArray::RemoveFirst()
{
    return DynamicArray::RemoveAtPos(0);
}

bool DynamicArray::RemoveLast()
{
    return DynamicArray::RemoveAtPos(DynamicArray::size - 1);
}

bool DynamicArray::RemoveAtPos(int index)
{
    if(index < 0 || index > DynamicArray::size -1)
    {
        return false;
    }

    if(DynamicArray::size == 1)
    {
        RemoveAll();
        return true;
    }

    DynamicArray::size--;
    int* newArr = new int[DynamicArray::size];

    int newIndex = 0;
    for (int oldIndex = 0; oldIndex <= DynamicArray::size; oldIndex++)
    {
        if(oldIndex == index)
        {
            continue;
        }

        newArr[newIndex] = DynamicArray::array[oldIndex];
        newIndex++;
    }
    
    delete[] DynamicArray::array;
    DynamicArray::array = newArr;
    return true;
}

void DynamicArray::RemoveAll()
{
    if(DynamicArray::size == 0)
        return;
    delete[] DynamicArray::array;
    DynamicArray::array = new int[0];
    DynamicArray::size = 0;
}

int DynamicArray::GetAtPos(int index)
{
    if(index < 0 || index > DynamicArray::size -1){
        throw std::out_of_range("Given index is smaller than 0 or bigger/equal to dynamic list size!");
    }
    
    return *(DynamicArray::array + index);
}

int DynamicArray::FindNumber(int number)
{
    for (int i = 0; i < DynamicArray::size; i++)
    {
        if(*(DynamicArray::array + i) == number)
        {
            return i;
        }
    }
    return -1;
}

std::string DynamicArray::ToString()
{
    std::string text = "[ ";
    if(DynamicArray::size == 0) return "EMPTY\n";
    for (int i = 0; i < DynamicArray::size; i++)
    {
        try
        {
            text += std::to_string(DynamicArray::GetAtPos(i));
            if(i != DynamicArray::size -1) text += ", ";
        }
        catch(const std::exception& e){}
    }
    return text + " ]\n";
}
#pragma endregion PUBLIC