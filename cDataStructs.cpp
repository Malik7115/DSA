#ifndef DATASTRUCTS_CPP
#define DATASTRUCTS_CPP

#include "cHelperFuncs.cpp"

/****************
//Graphs:
****************/


class vertex
{
    public:
        int name;
        vector<int> edges;
        
        
};

void addEdge(vector<pair<int, vector<int>>> &adj, int u, int v)
{
    // adds edge to a graph

    // second is a vector that represents edges of a vertex
    adj[u].second.push_back(v);

    // first represents name of vertex
    adj[u].first = u;
}

vector<pair<int, vector<int>>> transposeGraph(vector<pair<int, vector<int>>> adj)
{
    //returns the transpose of a directed graph created from an adjacency list
    vector<pair<int, vector<int>>> reverse;
    reverse.resize(adj.size());

    for (int i=0; i < adj.size(); i++)
    {
        for (int j = 0; j < adj[i].second.size(); j++)
        {
            reverse[adj[i].second[j]].first = adj[i].second[j];
            reverse[adj[i].second[j]].second.push_back(adj[i].first);
        }
    }
    return reverse;
}


// recursive DFS subroutine for the actual DFS Loop
void DFS(vector<pair<int, vector<int>>> &adj, vector<int> &explored, int s)
{
    // s is start vertex
    explored.push_back(s);

    cout << "SIZE  " << explored.size() << endl;

    // v is next index to be explored
    int v;
    
    for(int i = 0; i < adj[s].second.size(); i++)
    {
        v = adj[s].second[i];
        bool checkExplored = false;

        
        for(auto x: explored)
        {
            if (v == x)
            {
                checkExplored = true;
            }
        }

        if (checkExplored != true)
        {   

            DFS(adj, explored, v);
            // copy(explored.begin(), explored.end(), back_inserter(recureseExplored));
        }
    }
}


// actial routine to find out all veritces in a graph
vector<int> DFSLoop(vector<pair<int, vector<int>>> &adj)
{
    vector<int> explored;

    // for each vertex v in gragh adj
    for(int v = 0; v < adj.size(); v++)
    {
        bool checkExplored = false;

        for(auto x: explored)
        {
            if(v == x)
            {
                checkExplored = true;
                break;
            }
        }

        if(!checkExplored)
        {
            DFS(adj, explored, v);
        }
    }
    return explored;
}

void DFS_Topo(vector<pair<int, vector<int>>> &adj, vector<bool> &explored, int s,
                map<int, int> &finishingTime, int &currentLabel)
{
    // s is start vertex
    explored[s] = 1;
    std::vector<int>::iterator it;

    // if(!(explored.size()%1000))
    //     cout << "DFS TOPO EXP  " << explored.size() << endl;


    // v is next index to be explored
    int v;
    
    for(int i = 0; i < adj[s].second.size(); i++)
    {
        // cout << "DFS TOPo   " << v << endl;
        v = adj[s].second[i];
        bool checkExplored = false;


        if (!explored[v])
        {
            DFS_Topo(adj, explored, v, finishingTime, currentLabel);
        }


        // if (!count(explored.begin(), explored.end(), v))
        // {
        //     DFS_Topo(adj, explored, v, finishingTime, currentLabel);
        // }
        
        // for(auto x: explored)
        // {
        //     if (v == x)
        //     {
        //         checkExplored = true;
        //         break;
        //     }
        // }

        // if (checkExplored != true)
        // {   

        //     DFS_Topo(adj, explored, v, finishingTime, currentLabel);
        //     // copy(explored.begin(), explored.end(), back_inserter(recureseExplored));
        // }
    }

    finishingTime.insert(pair<int, int>(s, currentLabel));
    currentLabel --;

}

map<int, int> topoSort(vector<pair<int, vector<int>>> &adj)
{
    vector<bool> explored;
    explored.resize(adj.size());
    std::vector<int>::iterator it;

    vector<int> finishingTime;
    map<int, int> fT;

    finishingTime.resize(adj.size());

    int currentLabel = adj.size();

    for(int v = 0; v < adj.size(); v++)
    {
        // track ++;
        // cout << track << endl;
        bool checkExplored = false;

        if (!explored[v])
        {
            DFS_Topo(adj, explored, v, fT, currentLabel);
        }

        // for(auto x: explored)
        // {
        //     if(v == x)
        //     {
        //         checkExplored = true;
        //     }
        // }

        // if(!checkExplored)
        // {
        //     DFS_Topo(adj, explored, v, fT, currentLabel);
        // }

    }
    
    // returns vector where index corresponds to vertex and value corresponds
    // to finishing time of a vertex    
    return fT;
}

void DFS_SCC(vector<pair<int, vector<int>>> &adj, vector<bool> &explored, int s,
             int &numSCC, vector<int> &mapSCC, int &countCC)
{
    // s is start vertex
    explored[s] = 1;
    // cout << "DFS SCC EXP  " << explored.size() << endl;

    mapSCC[s] = numSCC;

    // v is next index to be explored
    int v;
    
    for(int i = 0; i < adj[s].second.size(); i++)
    {
        v = adj[s].second[i];
        bool checkExplored = false;

        
        if (!explored[v])
        {   
            countCC++;
            DFS_SCC(adj, explored, v, numSCC, mapSCC, countCC);
        }
    }
}


vector<int> kosaraju(vector<pair<int, vector<int>>> &adj)
{

    cout << ">>>>>>>.KOSARAJU\n";
    vector<pair<int, vector<int>>> rev = adj;
    rev = transposeGraph(rev);

    int countCC = 1;
    vector<int> vecSCC;

    int numSCC = 0;
    map<int,int> finishingTime;
    vector<pair<int,int>> sortedFt;

    // hashmap for <vertex, leader>
    vector<int> mapSCC;
    mapSCC.resize(adj.size());

    finishingTime = topoSort(rev);
    sortedFt = sortMapVal(finishingTime);

    vector<bool> explored;
    explored.resize(adj.size());

    for(auto v: sortedFt)
    {

        bool checkExplored = false;

        if(!explored[v.first])
        {
            numSCC += 1;
            DFS_SCC(adj, explored, v.first, numSCC, mapSCC, countCC);
            vecSCC.push_back(countCC);
            countCC = 1;
        }
    }

    // vecSCC is the number of SCCs in the graph
    // mapSCC is a mapping of each vertex to the corresponding SCC
    return vecSCC;
}




void contraction(vector<pair<int, vector<int>>> &adj, int u, int v)
{   
    int a = 0; //index for vertex u
    int b = 0; //index for vertex v

    int count = 0;
    
    //find corresponding indices a and b for u and v
    for (auto i: adj)
    {
        if(i.first == u)
        {
            a = count; 
        }
        if(i.first == v)
        {
            b = count;
        }
        count++;
    }

    //remove for self loop/edge
    // auto edge = find(adj[b].second.begin(), adj[b].second.end(),  u);
    // *edge     = edge - adj[b].second.begin();
    // adj[b].second.erase(edge);

    // edge = find(adj[a].second.begin(), adj[a].second.end(),  v);
    // *edge     = edge - adj[a].second.begin();
    // adj[a].second.erase(edge);

    vector <int> temp;
    auto it = remove(adj[b].second.begin(), adj[b].second.end(), u);

    copy(adj[b].second.begin(), it, back_inserter(temp));
    adj[b].second.clear();
    copy(temp.begin(), temp.end(), back_inserter(adj[b].second));
    temp.clear();

    it = remove(adj[a].second.begin(), adj[a].second.end(), v);
    copy(adj[a].second.begin(), it, back_inserter(temp));
    adj[a].second.clear();
    copy(temp.begin(), temp.end(), back_inserter(adj[a].second));
    temp.clear();

    //iterate the v index
    for(auto &x: adj[b].second)
    {         
        for (auto &y: adj)
        {
            if (y.first == x)
            {
                for (auto &z: y.second)
                {
                    if(z == v)
                    {
                        z = u;
                    }
                }
            }
        }

        adj[a].second.push_back(x);
    }

    // a.insert(std::end(a), std::begin(b), std::end(b));

    adj.erase(adj.begin() + b); // delete node itself

}


/****************
//Heaps:
****************/

int heapTraversal(int i, int mode)
{
    //returns index of either parent, left or right nodes
    // depending on the value of arguement c

    i +=1; // to simplify indexing we add +1 to current index
    switch (mode)
    {
    case 0: //return parent

        if (i == 1)
            return 0;

        return (i/2 - 1); 
        break;

    case 1: //return left
        if(i == 0)
            return 1;

        return (2*i - 1); 
        break;

    case 2: //return right
        if(i == 0)
            return 2;

        return (2*i);
        break;
    
    default:
        return (i); // return itself as default
    }

}


void maxHeapify(vector<int> &A, int i, int heapSize)
{
    int l = heapTraversal(i, 1);
    int r = heapTraversal(i, 2);
    int largest = 0;

    if (l <= heapSize && A[l] > A[i])
    {
        largest = l;
    } 

    else
        largest = i;
    
    if(r <= heapSize && A[r] > A[largest])
    {
        largest = r;
    }

    if(largest != i)
    {
        swap(A[i], A[largest]);
        maxHeapify(A, largest, heapSize);
    }

}

void minHeapify(vector<int> &A, int i)
{
    int l = heapTraversal(i, 1);
    int r = heapTraversal(i, 2);
    int smallest = 0;

    if (l <= A.size() && A[l] < A[i])
    {
        smallest = l;
    } 

    else
        smallest = i;
    
    if(r <= A.size() && A[r] < A[smallest])
    {
        smallest = r;
    }

    if(smallest != i)
    {
        swap(A[i], A[smallest]);
        minHeapify(A, smallest);
    }

}

void buildMaxHeap(vector<int> &A)
{
    for(int i = A.size()/2; i>=0; i--)
    {
        maxHeapify(A, i, A.size());
    }
}

void heapSort(vector<int> &A)
{   
    int heapSize = A.size()-1;
    buildMaxHeap(A);
    for(int i=A.size()-1; i>=1; i--)
    {
        swap(A[0], A[i]);
        heapSize-=1;
        maxHeapify(A, 0, heapSize);

    }
}


// The following assumes that all Heaps are max heaps
int heapExtractMax(vector<int> &A)
{
    // Assumes that heap is max heap
    // can add buildMaxHeap here as well
    int heapSize = A.size() - 1;
    if (heapSize > 0)
    {
        int max = A[0];
        A[0] = A[heapSize];
        A.pop_back(); // Remove highest from priority queue
        heapSize -= 1;
        maxHeapify(A, 0, heapSize);
        return max;
    }

    else
    {
        return A[0];
    }

}

void heapIncreaseKey(vector<int> &A, int i, int key)
{
    if (key > A[i])
    {
        A[i] = key;
        while(i > 0 && A[heapTraversal(i, 0)] < A[i])
        {
            swap(A[i], A[heapTraversal(i, 0)]);
            i = heapTraversal(i,0);
        }
    }
}

void maxHeapInsert(vector<int> &A, int key)
{
    A.push_back(-(std::numeric_limits<int>::max()));
    int heapSize = A.size() - 1;
    heapIncreaseKey(A, heapSize, key);
}

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
