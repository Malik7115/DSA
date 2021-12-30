#include "cHelperFuncs.cpp"
#include "cDataStructs.cpp"

std::random_device rand_dev;
std::mt19937       generator(rand_dev());

/**************** Misc Algorithms************/
template<typename T>
int twoSumProblem(unordered_map<T, T> &hashTable, vector<T> &inVec, signed int &sumInterval)
{   
    /*checks the number of target values tt in the interval [-sumInterval,sumInterval] (inclusive)
    such that there are distinct numbers x,yx,y in the input file that satisfy x+y=tx+y=t*/

    long long y          = 0;
    // int endHashVal = hashTable[hashTable.end()].first;
    unordered_map<T,T> targets;
    int numTargets = 0;
    

    for(signed int t = -1*sumInterval; t <= sumInterval; t++) // change to - sumInterval
    {
        for(auto x: hashTable)
        {
            y = t - x.first;
            if(hashTable.find(y) == hashTable.end()) 
                continue;

            else if((hashTable.find(y) != hashTable.end()) && x.first != y)
            {
                // numTargets += hashTable.count(y);
                targets.insert({t,t});
                break;
            }
        }
    if(abs(t)%500 == 0)
    {
        cout << t << endl;
        cout << "SIZE: " << targets.size() << endl;
    }

    }
    cout << "SIZE FINAL: " << targets.size() << endl;
    return targets.size();
}

int medianMaint(vector<int> &vec)
{
    priority_queue<int> lowHeap;  // supports extract max
    priority_queue<int> highHeap; // suppports extract min

    lowHeap.emplace(vec[0]);
    int median  = vec[0];

    int sizeDif =  0;
    int sum     =  median;

    vector <int> medianVec;
    medianVec.push_back(median);


    for(int i = 1; i < vec.size(); i++)
    {
        if((vec[i] <= lowHeap.top()))
        {
            lowHeap.emplace(vec[i]);
        }

        else
        {
            highHeap.emplace(-1 * vec[i]); // multiplying -1 to make it min heap
        }

        sizeDif = lowHeap.size() - highHeap.size(); 

        if(sizeDif > 1)
        {
            highHeap.emplace(-1 * lowHeap.top());
            lowHeap.pop();
        }

        if(sizeDif < -1)
        {
            lowHeap.emplace(-1 * highHeap.top());
            highHeap.pop();
        }


        if(lowHeap.size() < highHeap.size())
        {
            median = highHeap.top() * -1;
        }

        else
        {
            median = lowHeap.top();
        }
        sum += median;
        medianVec.push_back(median);
    }
    
    int size1 = lowHeap.size();
    int size2 = highHeap.size();

    ofstream myfile ("comp.txt");
    if (myfile.is_open())
    {
        for(int count = 0; count < medianVec.size(); count ++){
            myfile << medianVec[count] << endl;
        }
        myfile.close();
    }
    return sum;
}

string largeNumMult(std::string A, std::string B)
{

    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    int l1 = A.size();
    int l2 = B.size();
    string result(l1+l2, 0);
    int carry = 0;
    int sum = 0;

    int n1;
    int n2;
    int mul;
    int offset = 0;
   

    for(int i = 0; i<l2; i++)
    {   
        int j;
        carry = 0;
        n2    = B[i] - '0';
        for(j = 0; j<l1; j++)
        { 
            n1      = A[j] - '0';
            mul     = n1*n2;
            sum     = carry + mul + result[j + offset];
            result[j + offset]               = (sum)%10;
            carry   = sum / 10;
        }
        result[j + offset] += carry;
        offset++;
    }
    for(auto &c: result)
        c += '0';

    reverse(result.begin(), result.end());

    return result;
}

void merge(vector<int>& vec)
{
    int p   = 0;
    int r   = vec.size() - 1;
    int q   = (p+r)/2;
    int n1  = (q-p)+1;
    int n2  =  r-q;
    vector<int> L = splitVec(vec, p, p + n1-1);
    vector<int> R = splitVec(vec, q+1, q + n2);

    L.push_back(std::numeric_limits<int>::max());
    R.push_back(std::numeric_limits<int>::max());


    int i = 0;
    int j = 0;

    for (int k=p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {      
            vec[k] = L[i];
            i++;
        }

        else 
        {
            vec[k] = R[j];
            j++;
        }
    }

}

/*********************
 * Sorting Algorithms
 * *******************/


void mergeSort(vector<int> &vec)
{    
    vector<int> L;
    vector<int> R;

    int p   = 0;
    int r   = vec.size() - 1;
    if (p < r)
    {
        int q   = (p+r)/2;
    
        cout << "vec.size  == " << vec.size() << endl;
        L = splitVec(vec, p, q);
        R = splitVec(vec, q+1, r);
        mergeSort(L);
        mergeSort(R);

        L.insert(std::end(L), std::begin(R), std::end(R));
        vec = L;

        merge(vec);
        cout << endl;
        
    }
}

/*****************************
Quicksort and partition subroutine
 ****************************/

int partition(vector<int> &A, int l, int r)
{
    int p = A[l];
    int i = l+1;

    for (int j = l; j <= r; j++)
    {   
        if(A[j] < p)
        {
            swap(A[j], A[i]);
            i++;
        }
    }
    swap(A[l], A[i-1]);
    return i-1;
}

int qsCount  = 0; // for counting comparisons

bool cmp(pair<int,int> a, pair<int,int> b)
{
    return a.second < b.second;
}

int quickSort(vector<int> &A, int l, int r)
{
    
    if(l<r)
    {
        int i   = l;//choose pivot
        int mid = 0;
        int arrSize = r-l+1;

        vector<pair<int, int>> M; //map for choosing median val

        if(arrSize%2 == 0)
        {
            mid = arrSize/2 - 1 + l;
        }

        else
        {
            mid = arrSize/2 + l;
        }

        M.push_back({l, A[l]});
        M.push_back({mid, A[mid]});
        M.push_back({r, A[r]});

        sort(M.begin(), M.end(), cmp);
        i = M[1].first;
        swap(A[l], A[i]);
        int j = partition(A, l, r);

        // if(first == false)
        qsCount += r-l;

        quickSort(A, l, j-1);
        quickSort(A, j+1, r);
    }
return qsCount;
}


/********************
 * Graph Algorithms
 * ******************/

int kargersMinCut(vector<pair<int, vector<int>>> graph, int it)
{
    int totalCuts = 0;
    int minCuts   = 1000;
    int u = 0;
    int v = 0;
    int a = 0;
    int b = 0;


    // int randGen = 0
    // srand (time(NULL));

    for (int i = 0; i < it; i++)
    {
        vector<pair<int, vector<int>>> adj = graph;
        while(adj.size()>2)
        {
            
            a = rand() % adj.size();
            b = rand() % adj[a].second.size();

            // std::uniform_int_distribution<int>  distr1(0, adj.size());
            // a =  distr1(generator);
            // std::uniform_int_distribution<int>  distr2(0, adj[a].second.size());
            // b =  distr2(generator);

            
            // while(a == b)
            // {
            //     // a should not be equal to b
            //     a =  distr(generator);
            //     b =  distr(generator);
            // }

            u = adj[a].first;
            v = adj[a].second.at(b);

            contraction(adj,u,v);

        }
        totalCuts = adj[0].second.size();

        if(totalCuts < minCuts)
        {
            minCuts = totalCuts;
        }

        cout << "iterations = " << i << "   cuts = " << totalCuts <<  "  minCuts = " << minCuts << endl;

    }

    
    return minCuts;
}


vector<int> dijkstraSP(vector<pair<int, vector<int>>> &adj, int s, vector<pair<int, vector<int>>> &len)
{
    vector<int>  X; // X contains all processed vertices
    X.push_back(s);

    vector<bool> boolX;
    boolX.resize(adj.size());
    fill(boolX.begin(), boolX.end(), 0);
    boolX[s] = 1;

    vector<int>  A; // A contains shortest paths from s to all vertices
    A.resize(adj.size());
    A[s] = 0;


    int costMin = 9999;
    int cost    = 0;

    int vstar;
    int wstar;

    while(X.size() != adj.size())
    {
        costMin = 99999;
        for(auto v: X)
        {
            for (int w=0; w < adj[v].second.size(); w++)
            {   
                if(boolX[adj[v].second[w]] == true)
                    continue;

                cost = A[v] + len[v].second[w];
                if(cost < costMin)
                {
                    costMin = cost;
                    vstar   = v;
                    wstar   = adj[v].second[w];
                }
                
            }
        }
        A[wstar] = costMin;
        X.push_back(wstar);
        boolX[wstar] = 1;
    }




    return A;
}

bool isUniVal(node* x)
{
    if(x == NULL)
    {
        return true;
    }
    bool is_right_unival = false;
    bool is_left_unival = false;

    is_right_unival = isUniVal(x->right);
    is_left_unival  = isUniVal(x->left);

    if(x->right != NULL && x->left != NULL)
    {
        if(x->right->key == x->left->key && (is_right_unival & is_left_unival) == true)
        {
            return true;
        }

        else 
            return false;    
    }

    else if ((is_right_unival & is_left_unival) == true)
    {
        return true;
    }
    
}

