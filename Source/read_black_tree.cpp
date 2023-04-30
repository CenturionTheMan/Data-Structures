#include "Headers/read_black_tree.h"
#include <iostream>

#pragma region CTOR_DTOR

RedBlackTree::RedBlackTree()
{
    BinarySearchTree();
}

RedBlackTree::RedBlackTree(int size, int* arr)
{
    RedBlackTree::AddAll(size, arr);
}

RedBlackTree::~RedBlackTree()
{
    
}

#pragma endregion

#pragma region PRIVATE
NodeRBT* RedBlackTree::CastNode(Node* n)
{
    return (NodeRBT*) n;
}


void RedBlackTree::GetTreeAsString(std::string prefix, NodeRBT* curr, bool isRight, std::string& con)
{
    if(curr != NULL)
    {
        con += prefix;

        con += isRight ? "|--" : "*--" ;

        // print the value of the Node
        con.push_back(curr->color);
        con += ":"+ std::to_string(curr->value) + "\n";

        // enter the next tree level - left and right branch
        RedBlackTree::GetTreeAsString( prefix + (isRight ? "|    " : "    "), CastNode(curr->right), true, con);
        RedBlackTree::GetTreeAsString( prefix + (isRight ? "|    " : "    "), CastNode(curr->left), false, con);
    }
}

void RedBlackTree::FixColorsInTreeAfterAddition(NodeRBT* node)
{
    if(node == NULL)
        return;
        
    if(node == CastNode(BinarySearchTree::root))
        node->color = 'B';


    //Repeat if father is red and given node is not root. Since root is black given node have atleast two child if inside loop
    while (node != CastNode(BinarySearchTree::root) && CastNode(node->parent)->color == 'R')
    {
        //identify side
        if(node->parent->parent->left == node->parent) //parent of node is on left side of grandparent
        {
            NodeRBT* uncle = CastNode(node->parent->parent->right);
            
            //first case, uncle and father are red
            if(uncle != NULL && uncle->color == 'R')
            {
                uncle->color = 'B';
                CastNode(node->parent)->color = 'B';
                if(node->parent->parent == root)
                {
                    CastNode(BinarySearchTree::root)->color = 'B';
                    break;
                }
                else
                {
                    CastNode(node->parent->parent)->color = 'R';
                    node = CastNode(node->parent->parent);
                    continue;
                }
            }

            //second case, father is red and uncle is not. Given node is right child of father
            if(node->parent->right == node)
            {
                BinarySearchTree::RotateLeft(node->parent);
                node = CastNode(node->left);
            }
            
            //third case, father is red and uncle is not. Given node is left child of father
            BinarySearchTree::RotateRight(node->parent->parent);
            CastNode(node->parent)->color = 'B';
            if(node->parent->right != NULL)
                CastNode(node->parent->right)->color = 'R';
        }
        else //mirror case
        {
            NodeRBT* uncle = CastNode(node->parent->parent->left);
            
            //first case, uncle and father are red
            if(uncle != NULL && uncle->color == 'R')
            {
                uncle->color = 'B';
                CastNode(node->parent)->color = 'B';
                if(node->parent->parent == BinarySearchTree::root)
                {
                    CastNode(BinarySearchTree::root)->color = 'B';
                    break;
                }
                else
                {
                    CastNode(node->parent->parent)->color = 'R';
                    node = CastNode(node->parent->parent);
                    continue;
                }
            }

            //second case, father is red and uncle is not. Given node is right child of father
            if(node->parent->left == node)
            {
                BinarySearchTree::RotateRight(node->parent);
                node = CastNode(node->right);
            }
            
            //third case, father is red and uncle is not. Given node is left child of father
            BinarySearchTree::RotateLeft(node->parent->parent);
            CastNode(node->parent)->color = 'B';
            if(node->parent->left != NULL)
                CastNode(node->parent->left)->color = 'R';
        }
    }
}


void RedBlackTree::FixColorsInTreeAfterDeletion(NodeRBT* node)
{
    NodeRBT* brother;

    while ((node == NULL || node->color == 'B') && node != RedBlackTree::root)
    {
        NodeRBT* parent = CastNode(node->parent);

        if(node == parent->left)
        {
            brother = CastNode(parent->right);
            //case 1
            if(brother->color == 'R')
            {
                brother->color = 'B';
                parent->color = 'R';
                RedBlackTree::RotateLeft(parent);
                parent = CastNode(node->parent);
                brother = CastNode(parent->right);
            }

            //case 2
            if( (brother->left == NULL || CastNode(brother->left)->color == 'B') && (brother->right == NULL || CastNode(brother->right)->color == 'B'))
            {
                brother->color = 'R';
                node = parent;
                continue;
            }

            //case 3
            if(brother->right == NULL ||  CastNode(brother->right)->color == 'B')
            {
                CastNode(brother->left)->color = 'B';
                brother->color = 'R';
                RedBlackTree::RotateRight(brother);
                parent = CastNode(node->parent);
                brother = CastNode(parent->right);
            }

            //case 4
            brother->color = parent->color;
            parent->color = 'B';
            CastNode(brother->right)->color = 'B';
            RedBlackTree::RotateLeft(parent);
            break;
        }
        else //mirror
        {
             brother = CastNode(parent->left);
            //case 1
            if(brother->color == 'R')
            {
                brother->color = 'B';
                parent->color = 'R';
                RedBlackTree::RotateRight(parent);
                parent = CastNode(node->parent);
                brother = CastNode(parent->left);
            }

            //case 2
            if( (brother->left == NULL || CastNode(brother->left)->color == 'B') && (brother->right == NULL || CastNode(brother->right)->color == 'B'))
            {
                brother->color = 'R';
                node = parent;
                continue;
            }

            //case 3
            if(brother->left == NULL ||  CastNode(brother->left)->color == 'B')
            {
                CastNode(brother->right)->color = 'B';
                brother->color = 'R';
                RedBlackTree::RotateLeft(brother);
                parent = CastNode(node->parent);
                brother = CastNode(parent->left);
            }

            //case 4
            brother->color = parent->color;
            parent->color = 'B';
            CastNode(brother->left)->color = 'B';
            RedBlackTree::RotateRight(parent);
            break;
        }
    }
    
    node->color = 'B';
}

void RedBlackTree::Transplant(NodeRBT* parent, NodeRBT* child)
{
    if(parent->parent == NULL)
    {
        RedBlackTree::root = child;
    }
    else if(parent->parent->left == parent)
    {
        parent->parent->left = child;
    }
    else
    {
        parent->parent->right = child;
    }
    if(child != NULL)
        child->parent = parent->parent;
}
#pragma endregion

#pragma region PUBLIC

void RedBlackTree::AddAll(int count, int* arr)
{
    for (int i = 0; i < count; i++)
    {
        RedBlackTree::Add(arr[i]);
    }
}

void RedBlackTree::Add(int val)
{
    NodeRBT* added =  CastNode(BinarySearchTree::Add(val));
    added->color = 'R';

    RedBlackTree::FixColorsInTreeAfterAddition(added);
}

NodeRBT* RedBlackTree::Find(int val)
{
    return CastNode(BinarySearchTree::Find(val));
}

bool RedBlackTree::Remove(int val)
{
    return RedBlackTree::Remove(RedBlackTree::Find(val));
}

bool RedBlackTree::Remove(NodeRBT* node)
{
    if(node == NULL)
    {
        return false;
    }

    char originalColor = node->color;
    NodeRBT* toFix = NULL;
    NodeRBT* nil = NULL;

    if(node->left == NULL)
    {
        toFix = CastNode(node->right);
        if(toFix == NULL)
        {
            nil = new NodeRBT('B');
            nil->parent = node;
            node->right = nil;
            toFix = nil;
        }
        RedBlackTree::Transplant(node, toFix);
    }
    else if(node->right == NULL)
    {
        toFix = CastNode(node->left);
        if(toFix == NULL)
        {
            nil = new NodeRBT('B');
            nil->parent = node;
            node->left = nil;
            toFix = nil;
        }
        RedBlackTree::Transplant(node, toFix);
    }
    else
    {
        NodeRBT* succ = CastNode(BinarySearchTree::FindSuccessor(node));
        originalColor = succ->color;
        toFix = CastNode(succ->right);
        if(toFix == NULL)
        {
            nil = new NodeRBT('B');
            nil->parent = succ;
            succ->right = nil;
            toFix = nil;
        }
        if(succ->parent == node)
        {
            toFix->parent = succ;
        }
        else
        {
            RedBlackTree::Transplant(succ,toFix);
            succ->right = node->right;
            if(succ->right != NULL)
                node->right->parent = succ;
        }
        Transplant(node, succ);
        node->left->parent = succ;
        succ->left = node->left;
        succ->color = node->color;
    }


    if(originalColor == 'B')
        RedBlackTree::FixColorsInTreeAfterDeletion(toFix);


    if(nil != NULL)
    {
        if(nil->parent == NULL)
        {
            RedBlackTree::root = NULL;
        }
        else
        {
            if(nil->parent->left == nil)
            {
                nil->parent->left = NULL;
            }
            else
            {
                nil->parent->right = NULL;
            }
        }
        delete nil;
    }

    delete node;
    return true;
}

void RedBlackTree::RemoveAll()
{
    BinarySearchTree::RemoveAll();
}


std::string RedBlackTree::ToString()
{
    std::string res ="";
    RedBlackTree::GetTreeAsString("", CastNode(RedBlackTree::root), false, res);
    return (res == "")? "EMPTY\n" : res;
}

#pragma endregion


#pragma region NODE_RBT
NodeRBT::NodeRBT()
{
    Node();
    this->color = 'R';
}

NodeRBT::NodeRBT(char color)
{
    Node();
    this->color = color;
}

#pragma endregion