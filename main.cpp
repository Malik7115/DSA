
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


    // string result =  largeNumMult("3141592653589793238462643383279502884197169399375105820974944592", "2718281828459045235360287471352662497757247093699959574966967627");
    // cout << endl << result << endl;


    // std::cout << 31415926535897932384626433832795 << endl;


    // node* x = treeMax(root);
    // int key = x->key;    
    // std::cout << "root->right" << endl;

    struct node* Node = new node(3);

    Node->right = new node(3);
    Node->left = new node(3);

    Node->right->right = new node(3);
    Node->right->left = new node(3);

    bool test = isUniVal(Node);

    std::cout << test << endl;
    
}

