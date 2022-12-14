#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999

class Graph{
protected:
	bool m_Type;//0:List 1:Matrix
	int m_Size; //graph size

public:
	Graph(bool type, int size);
	~Graph();

	bool getType();
	int getSize();
	
	virtual void getAdjacentEdges(int vertex, map<int, int>* m) = 0;//get adjacent edge function
	virtual void insertEdge(int from, int to, int weight) = 0; //insert vertex, vertex, weight function
	virtual	bool printGraph(ofstream *fout) = 0; // print graph function
	virtual int getvalue(int i, int j)=0; //get edge value function
	virtual bool connect_vertex(int i, int j)=0; //check connet vertex function
};

#endif
