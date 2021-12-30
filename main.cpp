
#include "cHelperFuncs.cpp"
#include "cAlgorithms.cpp"
#include "cDataStructs.cpp"

#include <iostream>


int main(int, char**)
{
    // vector<int> vec = {4,2,7,5,1,2,0,3,6};

    vector<long long> vec;
    string filename = "2sum.txt";
    long long check = stoll("68037543430");
    file2Vec(filename, vec);
    unordered_map <long long,long long> hash;
    for(auto j: vec)
    {
        hash.insert({j,j});
    }
    int interval = 10000;
    int count = twoSumProblem(hash, vec, interval);

    cout << "herer" <<endl;
}
