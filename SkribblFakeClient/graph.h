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
    vector<Node*> nodes;
    vector<vector<int>>matrix;

public:
    Graph();
    vector<Node*> getNodes(){
        return nodes;
    }
    void addNode(QPoint p){
        Node* n=new  Node;
        n->setCoord(p);
        nodes.push_back(n);
    }
    void addNode(Node* n){
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
        for(Node* i : nodes)
        {
            delete i;
        }
    }

};

#endif // GRAPH_H
