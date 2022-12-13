#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"//ListGraph.h includes Graph header file

class ListGraph : public Graph//declare and define ListGraph class that inherits the Graph class
{
private://declare the private member
	map < int, int >* m_List;//map array that insert the graph data

public://declare the public member
	ListGraph(bool type, bool directed, bool weighted, int size);//constructor of the ListGraph class
	~ListGraph();//destructor of the ListGraph class
		
	void getIncidentEdges(int vertex, map<int, int>* m);//function that the insert to map-m
	void	insertEdge(int from, int to, int weight);//function that insert the data in m_List
	bool	printGraph(ofstream* fout);//function that prints the List
	int adjacent(int from, int to) {//function that return the weight
		map<int, int>::iterator i;
		i = m_List[from].find(to);//find the wanted postion
		if (i == m_List[from].end())//if from vertex and to vertex isn't conneted
			return 0;//0 return
		else//if is connected
			return
			i->second;//weight returns
	}
};//end

#endif
