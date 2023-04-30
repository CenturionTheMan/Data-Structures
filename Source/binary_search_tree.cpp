#include "Headers/binary_search_tree.h"
#include <iostream>

#pragma region CTOR_DTOR
BinarySearchTree::BinarySearchTree()
{
    BinarySearchTree::root = NULL;
}

BinarySearchTree::BinarySearchTree(int size, int* arr)
{
    BinarySearchTree::root = NULL;
    for (int i = 0; i < size; i++)
    {
        BinarySearchTree::Add(arr[i]);
    }
}

BinarySearchTree::~BinarySearchTree()
{
    BinarySearchTree::RemoveAll();
}
#pragma endregion CTOR_DTOR

#pragma region PRIVATE

void BinarySearchTree::GetTreeAsString(std::string prefix, Node* curr, bool isRight, std::string& con)
{    
    if(curr != NULL)
    {
        con += prefix;

        con += isRight ? "|--:" : "*--:" ;
        
        // print the value of the Node
        con += std::to_string(curr->value) + "\n";

        // enter the next tree level - left and right branch
        BinarySearchTree::GetTreeAsString( prefix + (isRight ? "|    " : "   "), curr->right, true, con);
        BinarySearchTree::GetTreeAsString( prefix + (isRight ? "|    " : "   "), curr->left, false, con);
    }
}

void BinarySearchTree::RecursivelyDeleteNodes(Node* toDelete)
{
    if(toDelete == NULL)
        return;
    RecursivelyDeleteNodes(toDelete->right);
    RecursivelyDeleteNodes(toDelete->left);
    delete toDelete;
}

Node* BinarySearchTree::FindMin(Node* node)
{
    if(node == NULL)
        return NULL;
    
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

Node* BinarySearchTree::FindMax(Node* node)
{
    if(node == NULL)
        return NULL;
    
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

Node* BinarySearchTree::RemoveAndReturnChanged(Node* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    //If given node have both childrens successor of this node will be removed, otherwise this node will be removed
    Node* toRemove = (node->left != NULL && node->right != NULL )? BinarySearchTree::FindSuccessor(node) : node;

    Node* changedNode = NULL;

    if(toRemove != node) //if node have both children
    {
        //Find which child (left/right) is toRemove -> assign right child (bigger one) of toRemove to this reference
        if(toRemove == toRemove->parent->left){
            toRemove->parent->left = toRemove->right;
        }
        else{
            toRemove->parent->right = toRemove->right;
        }
        //

        //If to remove has right child change its parent reference
        if(toRemove->right!=NULL){
            toRemove->right->parent = toRemove->parent;
        }

        //Copy value of successor to pointed as to delete node
        node->value = toRemove->value;
        changedNode = node;
    }
    else //otherwise
    {
        //Pointer to to the child of to remove node
        Node* toRemoveChild = (toRemove->left != NULL)? toRemove->left : toRemove->right;

        //If toRemoveChild is not NULL assign its parent reference 
        if(toRemoveChild != NULL)
        {
            toRemoveChild->parent = toRemove->parent;
            changedNode = toRemoveChild;
        }

        //If toRemove parent is NULL root reference need to be changed (we are removing current root element)
        if(toRemove->parent == NULL)
        {
            BinarySearchTree::root = toRemoveChild;
        }
        else //If to remove have parent its child reference need to be changed
        {
            
            if(toRemove->parent->left == toRemove){
                toRemove->parent->left = toRemoveChild;
            }
            else{
                toRemove->parent->right = toRemoveChild;
            }
        }   
    }
    delete toRemove;
    return changedNode;
}



#pragma endregion PRIVATE

#pragma region PUBLIC
void BinarySearchTree::AddAll(int count, int* arr)
{
    for (int i = 0; i < count; i++)
    {
        BinarySearchTree::Add(arr[i]);
    }
}

Node* BinarySearchTree::Add(int val)
{
    if(BinarySearchTree::root == NULL)
    {
        BinarySearchTree::root = new Node(val);
        return BinarySearchTree::root;
    }

    Node* current = BinarySearchTree::root;
    Node* toAdd = new Node(val);
    while (current != NULL)
    {
        if(val <= current-> value)
        {
            if(current->left == NULL)
            {
                current->left = toAdd;
                toAdd->parent = current;
                return toAdd;
            }
            current = current->left;
        }
        else
        {
            if(current->right == NULL)
            {
                current->right = toAdd;
                toAdd->parent = current;
                return toAdd;
            }
            current = current->right;
        }
    }
    return NULL;
}

Node* BinarySearchTree::Find(int val)
{
    Node* current = BinarySearchTree::root;

    while (current != NULL)
    {
        if(val == current->value){
            break;
        }
        else if(val <= current->value)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

Node* BinarySearchTree::FindMin()
{
    return FindMin(BinarySearchTree::root);
}

Node* BinarySearchTree::FindMax()
{
    return FindMax(BinarySearchTree::root);
}

bool BinarySearchTree::RotateRight(Node* pivot)
{
    if(pivot == NULL || pivot->left == NULL)
        return false;
    
    Node* leftChild = pivot->left;


    if(pivot == BinarySearchTree::root)
    {
        BinarySearchTree::root = leftChild;
    }
    else
    {
        //pivot parent child assign
        if(pivot->parent->left == pivot)
            pivot->parent->left = leftChild;
        else
            pivot->parent->right = leftChild;
    }
    //pivot child parent assign
    leftChild->parent = pivot->parent;

    //children swaps
    pivot->left = leftChild->right;
    
    if(leftChild->right != NULL)
        leftChild->right->parent = pivot;

    leftChild->right = pivot;
    pivot->parent = leftChild;
    return true;
}

bool BinarySearchTree::RotateRight(int val)
{
    return BinarySearchTree::RotateRight(BinarySearchTree::Find(val));
}

bool BinarySearchTree::RotateLeft(Node* pivot)
{
    if(pivot == NULL || pivot->right == NULL)
        return false;
    
    Node* rightChild = pivot->right;

    if(pivot == BinarySearchTree::root)
    {
        BinarySearchTree::root = rightChild;
    }
    else
    {
        //pivot parent child assign
        if(pivot->parent->left == pivot)
            pivot->parent->left = rightChild;
        else
            pivot->parent->right = rightChild;
    }
    rightChild->parent = pivot->parent;
    
    pivot->right = rightChild->left;
    
    if(rightChild->left != NULL)
        rightChild->left->parent = pivot;

    rightChild->left = pivot;
    pivot->parent = rightChild;   
    return true; 
}

bool BinarySearchTree::RotateLeft(int val)
{
    return BinarySearchTree::RotateLeft(BinarySearchTree::Find(val));
}

void BinarySearchTree::PerformDSW()
{
    Node* holder = BinarySearchTree::root;
    int nodesAmount = 0;
    //Straightening tree
    while (holder != NULL)
    {
        if(holder->left != NULL)
        {
            BinarySearchTree::RotateRight(holder);
            holder = holder->parent;
        }
        else
        {
            nodesAmount ++;
            holder = holder->right;
        }
    }

    int logNum = floor(log2(nodesAmount + 1));
    int m = (int)pow(2 , logNum) - 1;
    holder = BinarySearchTree::root;
    //Balancing tree
    for (int i = 0; i < (nodesAmount - m); i++)
    {
        BinarySearchTree::RotateLeft(holder);
        holder = holder->parent->right;
    }

    while (m > 1)
    {
        m = m/2;
        holder = BinarySearchTree::root;
        for (int i = 0; i < m; i++)
        {
            BinarySearchTree::RotateLeft(holder);
            holder = holder->parent->right;
        }
    }
     
}

Node* BinarySearchTree::FindSuccessor(Node* node)
{
    if(node == NULL)
        return NULL;

    if(node->right != NULL)
    {
        return BinarySearchTree::FindMin(node->right);
    }
    else
    {
        Node* current = node->parent;
        Node* prev = node;
        while (current != NULL)
        {
            if(current->left==prev)
            {
                return current;
            }
            else
            {
                prev = current;
                current = current->parent;
            }
        }
        return NULL;
    }
}

bool BinarySearchTree::Remove(int val)
{
    return BinarySearchTree::Remove(BinarySearchTree::Find(val));
}

bool BinarySearchTree::Remove(Node* node)
{
    bool isNull = node == NULL;
    BinarySearchTree::RemoveAndReturnChanged(node);
    return !isNull;
}

void BinarySearchTree::RemoveAll()
{
    BinarySearchTree::RecursivelyDeleteNodes(BinarySearchTree::root);
    BinarySearchTree::root = NULL;
}

std::string BinarySearchTree::ToString()
{
    std::string res ="";
    BinarySearchTree::GetTreeAsString("", BinarySearchTree::root, false, res);
    return (res == "")? "EMPTY\n" : res;
}

#pragma endregion PUBLIC


#pragma region Node
Node::Node(Node* left, Node* right, Node* parent, int value)
{
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->value = value;
}

Node::Node()
{
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

Node::Node(int val)
{
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
    this->value = val;
}
#pragma endregion