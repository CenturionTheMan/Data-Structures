#include "Headers/binary_heap.h"
#include <stdexcept>

#pragma region CTOR_DTOR
BinaryHeap::BinaryHeap()
{
    BinaryHeap::size = 0;
    BinaryHeap::heap = NULL;
}

BinaryHeap::BinaryHeap(int size, int* arr)
{
    BinaryHeap::size = 0;
    BinaryHeap::heap = new int[0];
    for (int i = 0; i < size; i++)
    {
        BinaryHeap::Push(arr[i]);
    }
}

BinaryHeap::~BinaryHeap()
{ 
    delete[] BinaryHeap::heap;
}
#pragma endregion CTOR_DTOR

#pragma region PRIVATE
int BinaryHeap::GetIndexOfLeftChild(int parentIndex)
{
    int index = 2 * parentIndex + 1;
    return (index < BinaryHeap::size)? index : -1;
}

int BinaryHeap::GetIndexOfRightChild(int parentIndex)
{
    int index = 2 * parentIndex + 2;
    return (index < BinaryHeap::size)? index : -1;
}

int BinaryHeap::GetIndexOfParent(int current)
{
    int index = (current - 1)/2;
    return (current > 0)? index : -1;
}

void BinaryHeap::GetTreeAsString(std::string prefix, int index, bool isRight, std::string& con)
{    
    if(index >= 0 && index < BinaryHeap::size)
    {
        con += prefix;

        con += isRight ? "|--:" : "*--:" ;

        // print the value of the node
        con += std::to_string(BinaryHeap::heap[index]) + "\n";

        // enter the next tree level - left and right branch
        BinaryHeap::GetTreeAsString( prefix + (isRight ? "|  " : "   "), GetIndexOfRightChild(index), true, con);
        BinaryHeap::GetTreeAsString( prefix + (isRight ? "|  " : "   "), GetIndexOfLeftChild(index), false, con);
    }
}

void BinaryHeap::PerformFloyd()
{
    int parent = (size - 2)/2;
    for(int i = parent; i >= 0; i--)
    {
        int curIndex = i;
    NO_INDEX_REPEAT:
        int lChildIndex = 2 * curIndex + 1;
        int rChildIndex = 2 * curIndex + 2;
        int biggerIndex;
        if(lChildIndex < size && rChildIndex < size)
        {
            biggerIndex = (heap[lChildIndex] > heap[rChildIndex])? lChildIndex : rChildIndex;
        }
        else if(lChildIndex < size || rChildIndex < size)
        {
            biggerIndex = (lChildIndex < size)? lChildIndex : rChildIndex;
        }
        else
        {
            continue;
        }

        if(heap[curIndex] < heap[biggerIndex])
        {
            int temp = heap[curIndex];
            heap[curIndex] = heap[biggerIndex];
            heap[biggerIndex] = temp;
            curIndex = biggerIndex;
            goto NO_INDEX_REPEAT;
        }
    }
}

void BinaryHeap::ChangeHeapSize(int newSize)
{
    int* newArr = new int[newSize];

    int oldSize = 0;
    for (int i = 0; i < newSize; i++)
    {
        if(i >= BinaryHeap::size)
        {
            break;
        }
        newArr[i] = BinaryHeap::heap[i];
    }
    BinaryHeap::size = newSize;
    delete[] BinaryHeap::heap;
    BinaryHeap::heap = newArr;
}


#pragma endregion PRIVATE

#pragma region PUBLIC

void BinaryHeap::PushAll(int count, int* arr)
{
    for (int i = 0; i < count; i++)
    {
        BinaryHeap::Push(arr[i]);
    }
}

void BinaryHeap::PushAllFloyd(int count, int* arr)
{
    if(count == 0)
        return;

    int prevSize = BinaryHeap::size;
    BinaryHeap::ChangeHeapSize(BinaryHeap::size + count);

    int inputIndexer = 0;
    for (int i = prevSize; i < BinaryHeap::size; i++)
    {
        BinaryHeap::heap[i] = arr[inputIndexer];
        inputIndexer++;
    }

    BinaryHeap::PerformFloyd();
}

void BinaryHeap::Push(int num)
{
    BinaryHeap::ChangeHeapSize(BinaryHeap::size + 1);

    int toAddIndex = BinaryHeap::size -1;
    *(BinaryHeap::heap + toAddIndex) = num;

    int toAddParent = GetIndexOfParent(toAddIndex);
    while (toAddParent >= 0 && heap[toAddParent] < heap[toAddIndex])
    {
        int temp = heap[toAddParent];
        heap[toAddParent] = heap[toAddIndex];
        heap[toAddIndex] = temp;
        toAddIndex = toAddParent;
        toAddParent = GetIndexOfParent(toAddIndex);
    }
}


int BinaryHeap::PopHead()
{
    if(BinaryHeap::size < 1)
    {
        throw std::out_of_range("Binary heap size is equal to 0");
    }
    if(BinaryHeap::size == 1)
    {
        int toRet = BinaryHeap::heap[0];
        BinaryHeap::RemoveAll();
        return toRet;
    }    

    int num = BinaryHeap::heap[0];
    BinaryHeap::heap[0] = BinaryHeap::heap[BinaryHeap::size -1];

    BinaryHeap::ChangeHeapSize(BinaryHeap::size - 1);

    int current = 0;
    while (current >= 0)
    {
        int swapTo = current;
        int left = GetIndexOfLeftChild(current);
        int right = GetIndexOfRightChild(current);

        if(left >=0 && BinaryHeap::heap[swapTo] < BinaryHeap::heap[left])
            swapTo = left;
        
        if(right >=0 && BinaryHeap::heap[swapTo] < BinaryHeap::heap[right])
            swapTo = right;
        
        if(swapTo == current)
            break;

        int temp = BinaryHeap::heap[current];
        BinaryHeap::heap[current] = BinaryHeap::heap[swapTo];
        BinaryHeap::heap[swapTo] = temp;
        current = swapTo;
    }

    return num;
}

void BinaryHeap::RemoveAll()
{
    if(BinaryHeap::size == 0)
        return;
    delete[] BinaryHeap::heap;
    BinaryHeap::heap =NULL;
    BinaryHeap::size = 0;
}

bool BinaryHeap::Find(int num)
{
    if( BinaryHeap::size > 0 && num > BinaryHeap::heap[0])
    {
        return false;
    }

    for (int i = 0; i < BinaryHeap::size; i++)
    {
        if(BinaryHeap::heap[i] == num)
        {
            return true;
        }
    }

    return false;
}

int BinaryHeap::GetSize()
{
    return BinaryHeap::size;
}

std::string BinaryHeap::ToString()
{
    std::string res = "";
    BinaryHeap::GetTreeAsString("",0,false, res);
    return (res=="")? "NONE\n" : res + "\n";
}
#pragma endregion PUBLIC