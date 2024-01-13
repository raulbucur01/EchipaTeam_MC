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
	vector<std::pair<vector<Node*>,QColor>> nodes;
	vector<vector<int>>matrix;

public:
	Graph();
	vector<std::pair<vector<Node*>,QColor>> getNodes() {
		return nodes;
	}
	int GetSize();
	void addNodes(std::pair<vector<Node*>,QColor> n) {
		nodes.push_back(n);
	}
	void clear()
	{
		for (std::pair<vector<Node*>, QColor> i : nodes)
			for (Node* j : i.first)
			{
				delete j;
			}
		nodes.clear();
	}
	void setMatrix(std::vector<std::vector<int>>matrice)
	{
		matrix = matrice;
	}
	void deletelast()
	{
		if (nodes.empty())
		{
			return;
		}
		for (Node* i: nodes.back().first)
		{
			delete i;
		}
		if(!nodes.empty())
		nodes.pop_back();

	}

	~Graph()
	{
		for (std::pair<vector<Node*>,QColor> i : nodes)
			for (Node* j : i.first)
			{
				delete j;
			}
		nodes.clear();
	}

};

#endif // GRAPH_H
