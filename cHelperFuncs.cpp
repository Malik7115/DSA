#ifndef HELPERFUNCS_CPP
#define HELPERFUNCS_CPP

#include <iostream>
#include <array>
#include <vector>
#include <iterator>
#include <limits>
#include <bits/stdc++.h>


using namespace std;

template<typename T>

vector<T> splitVec(vector<T> const& input, int start, int end)
{
    auto first  = input.begin() + start;
    auto last   = input.begin() + end + 1;

    vector<T> vector(first, last);
    return vector;
    
}

void swap(int&a, int&b)
{
    int temp = a;
    a = b;
    b = temp;
}


void file2Vec(const string& filename, vector<int>& vec)
{
    // Reads Integers From Files and stores them in vectors

    /**** TODO: use templates to make vector accomodate different types ****/

    string line;
    ifstream numFile (filename);

    if(numFile.is_open())
    {
        while(getline(numFile, line))
        {
            vec.push_back(stoi(line));
        }
    }
}


#endif
