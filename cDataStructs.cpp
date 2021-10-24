#ifndef DATASTRUCTS_CPP
#define DATASTRUCTS_CPP

#include "cHelperFuncs.cpp"

/****************
//Graphs:
****************/
void addEdge(vector<pair<int, vector<int>>> &adj, int u, int v)
{
    adj[u].second.push_back(v);

    adj[u].first = u;
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

void printGraph(vector<int> adj[], int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
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
