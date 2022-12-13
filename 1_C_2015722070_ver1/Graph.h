#ifndef _GRAPH_H_
#define _GRAPH_H_

//include the file that we need
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

using namespace std;//std

#define MAX 999999

class Graph{//declare and define Graph class
protected://declare the protected members
	bool	m_Type;//0:List 1:Matrix
	bool	m_Directed;//0:undirected 1:directed
	bool	m_Weighted;//0:unweighted 1:weighted;
	int	m_Size;//graph's size

public://declare the public members
	Graph(bool type, bool directed, bool weighted, int size);//constructor of the Graph
	~Graph();//destructor of the Graph

	bool getDirected();//function that gets the graph's directed
	bool getWeighted();//function that gets the graph's Weighted
	int	getSize();//function that gets the graph's size
	
	virtual void getIncidentEdges(int vertex, map<int, int>* m) = 0;//list, matrix graph's member function
	virtual void	insertEdge(int from, int to, int weight) = 0;//list, matrix graph's member function
	virtual	bool	printGraph(ofstream* fout) = 0;//list, matrix graph's member function
	virtual int adjacent(int from, int to) = 0;//list, matrix graph's member function
};//end

#endif
