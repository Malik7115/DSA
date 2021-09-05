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


#endif
