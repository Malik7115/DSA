
#include "cHelperFuncs.cpp"
#include "cAlgorithms.cpp"
#include "cDataStructs.cpp"

#include <iostream>



int main(int, char**)
{
    //vector<int> vec = {4,2,7,5,1,2,3,6};
    vector<int> vec = {14,16,20,22,19};

    struct node* root = new node(3);
    struct node* z    = new node(4);
    struct node* y    = new node(2);
    struct node* x    = new node(1);
    struct node* a    = new node(5);
    

    treeInsert(root, z);
    treeInsert(root, y);
    treeInsert(root, x);
    treeInsert(root, a);

    cout << "" << endl;


    // node* x = treeMax(root);
    // int key = x->key;    
    // std::cout << "root->right" << endl;

    
}

