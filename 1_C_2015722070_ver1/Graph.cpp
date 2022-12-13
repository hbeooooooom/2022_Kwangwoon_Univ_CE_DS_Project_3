#include "Graph.h"//Graph.cc includes the Graph header file

Graph::Graph(bool type, bool directed, bool weighted, int size)//constructor of the Graph class
{	
	//initialize
	m_Type = type;
	m_Directed = directed;
	m_Weighted = weighted;
	m_Size = size;
}

Graph::~Graph()//destructor of the Graph class
{	
	
}

bool Graph::getDirected()//function that gets the directed
{
	return m_Directed;//directed return
}

bool Graph::getWeighted()//function that gets the weighted
{
	return m_Weighted;//weighted return
}

int Graph::getSize()//function that gets the graph's size
{
	return m_Size;//m_Size return
}
