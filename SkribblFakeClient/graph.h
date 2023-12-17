#ifndef GRAPH_H
#define GRAPH_H

#include"node.h"
#include <fstream>
#include<iostream>
#include<stack>
#include<QScreen>
#include<QGuiApplication>
#include<limits>
#include<algorithm>
#include<array>

using namespace std;

class Graph
{
    vector<vector<Node*>> nodes;
    vector<vector<int>>matrix;

public:
    Graph();
    vector<vector<Node*>> getNodes(){
        return nodes;
    }
    void addNodes(vector<Node*> n){
        nodes.push_back(n);
    }
    void clear()
    {
        nodes.clear();
    }
    void setMatrix(std::vector<std::vector<int>>matrice)
    {
        matrix = matrice;
    }

    ~Graph()
    {
        for(vector<Node*> i : nodes)
        for(Node* j : i)
        {
            delete j;
        }
    }

};

#endif // GRAPH_H
