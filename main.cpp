
#include "cHelperFuncs.cpp"
#include "cAlgorithms.cpp"
#include "cDataStructs.cpp"

#include <iostream>


int main(int, char**)
{
    // vector<int> vec = {4,2,7,5,1,2,0,3,6};

    
    vector<pair<int, vector<int>>> adj;
    vector<pair<int, vector<int>>> lens;
    // int maxVertices = 200;
    file2graph("graph1.txt", adj, lens);

    vector<int> A = dijkstraSP(adj, 0, lens);

    cout << adj.size() << endl;

    vector<int> test =  {6,36,58,81,98,114,132,164,187,196};
    // [2599, 2610, 2947, 2052, 2367, 2399, 2029, 2442, 2505, 3068]
    int dist;
    for(auto x: test)
    {
        dist = A[x];
    }

    // adj.resize(6);

    // addEdge(adj, 0, 1);
    // addEdge(adj, 1, 2);
    // addEdge(adj, 2, 0);
    // addEdge(adj, 3, 2);
    // addEdge(adj, 3, 4);
    // addEdge(adj, 4, 5);
    // addEdge(adj, 5, 3);

    // addEdge(adj, 3, 0);
    
    vector<int> explored;
    // DFS(adj, explored, 0);

    vector<int> mapSCC    = kosaraju(adj);
    sort(mapSCC.begin(), mapSCC.end(), greater<int>());

    vector<int> uniqueSCC = mapSCC;

    sort(uniqueSCC.begin(), uniqueSCC.end());

    vector<int>::iterator ip;

    ip = std::unique(uniqueSCC.begin(), uniqueSCC.end());
    uniqueSCC.resize(std::distance(uniqueSCC.begin(), ip));

    vector<int> countSCC;
    countSCC.resize(uniqueSCC.size());

    for(int i = 0; i < uniqueSCC.size(); i++)
    {
        int num = uniqueSCC[i];
        int count = 0;

        for(auto x: mapSCC)
        {
            if (x == num)
            {
                cout << i << endl;
                count++;
            }
        }

        countSCC[i] = count;

    }    

    sort(countSCC.begin(), countSCC.end());


    cout << "ASDASDASDASDASDSADASD" << endl;
    for(auto x: countSCC)
    {
        cout << x << endl;
    }

    map<int,int> f = topoSort(adj);

    // vector<pair<int, int>> sorted_f = sortMapVal(f);
    // for(auto x: sorted_f)
    // {
    //     cout << x.first;
    // }

    


    vector<pair<int, vector<int>>> reverse = transposeGraph(adj);

    cout << "finished" << endl;
    

    vector<int> vec = {3,2,3,4,5,5,3,6,3};
    // sort(vec.begin(), vec.end());
    
    int count = 0;
    auto it = std::remove(vec.begin(), vec.end(), 3);

    vector<int> vec2;
    copy(vec.begin(), it, back_inserter(vec2));
    vec.clear();

    copy(vec2.begin(), vec2.end(), back_inserter(vec));



    // for(auto x: vec)
    // {
    //     vec.erase(find(vec.begin(),vec.end(),3));

    // }

    int ser = 7;

    // vector<pair<char, int>> A;
    // A.push_back({'l',2});
    // A.push_back({'m',3});
    // A.push_back({'r',4});



    // cout << "DoNR" << endl << A[0].first;

    // vector<int> vec2;
    // file2Vec("array.txt", vec2);

    // // int count = quickSort(vec, 0, vec.size() - 1);
    // int count = quickSort(vec2, 0, vec2.size() - 1);

    // //pivot == first; count  ==  162085
    // //pivot == last; count   ==  164123
    // //pivot == median; count ==  138382

    // cout << vec2.size() << endl;

    // struct node* root = new node(3);
    // struct node* z    = new node(4);
    // struct node* y    = new node(2);
    // struct node* x    = new node(1);
    // struct node* a    = new node(5);
    

    // treeInsert(root, z);
    // treeInsert(root, y);
    // treeInsert(root, x);
    // treeInsert(root, a);

    // struct node* Node = new node(3);

    // Node->right = new node(3);
    // Node->left = new node(3);

    // Node->right->right = new node(3);
    // Node->right->left = new node(3);

    // bool test = isUniVal(Node);

    // std::cout << test << endl;
    
}
