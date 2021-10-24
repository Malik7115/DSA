#ifndef HELPERFUNCS_CPP
#define HELPERFUNCS_CPP

#include <iostream>
#include <array>
#include <vector>
#include <iterator>
#include <limits>
#include <bits/stdc++.h>
#include <stdlib.h>


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

void file2graph(const string& filename, int maxVertices, vector<pair<int, vector<int>>> &adj)
{
    string line;
    ifstream numFile (filename);
    adj.resize(maxVertices);

    if(numFile.is_open())
    {
        while(getline(numFile, line))
        {
            int vertex = 0;
            stringstream ss(line);
            string word;

            bool first = true;
            while(ss >> word)
            {

                if(first)
                {
                    vertex = stoi(word) - 1; //to make starting index 0
                    adj[vertex].first = vertex;
                    first = false;
                }
                else
                    adj[vertex].second.push_back(stoi(word) - 1);
            }
            
        }
    }

}

#endif
