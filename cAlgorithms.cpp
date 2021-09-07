#include "cHelperFuncs.cpp"
#include "cDataStructs.cpp"


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

