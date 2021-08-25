#ifndef DATASTRUCTS_CPP
#define DATASTRUCTS_CPP

#include "cHelperFuncs.cpp"



/****************
 Trees
 ***************/

struct node 
{
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;

    node (int val)
    {
        key = val;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    
};

// The Following Code Pieces Assume that the trees are binary search trees
void inorderTreeWalk(node* x)
{
    // 0(n)
    if(x!=NULL)
    {
        inorderTreeWalk(x->left);
        cout << x->key << endl;
        inorderTreeWalk(x->right);
    }
}

node* treeSearch(node* x, int k)
{
    // O(h)
    if(x == NULL || k == x->key)
    {
        return x;
    }
    if(k < x->key)
    {
        return treeSearch(x->left, k);
    }
    else
    {
        return treeSearch(x->right, k);
    }

}

node* treeMin(node* x)
{
    //O(h)
    while(x->left != NULL)
    {
        x = x->left;
    }
    return x;
}

node* treeMax(node* x)
{
    // O(h)
    while(x->right != NULL)
    {
        x = x->right;
    }
    return x;
}

node* treeSuccessor(node* x)
{
    if(x->right != NULL)
    {
        return treeMin(x->right);
    }

    node* y = x->parent;

    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void treeInsert(node* T, node* z)
{
    node* y = NULL;
    node* x = T;

    while(x!=NULL)
    {
        y = x;
        if(z->key < x->key)
        {
            x = x->left;
        }
        else 
        {
            x = x->right;
        }
    }

    z->parent = y;

    if(y == NULL)
    {
        T = z;
    }
    else if(z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
}


#endif
