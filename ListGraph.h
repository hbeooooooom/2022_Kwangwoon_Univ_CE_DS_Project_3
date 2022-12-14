#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	map < int, int >* m_List;

public:	
	ListGraph(bool type, int size);
	~ListGraph();
		
	void getAdjacentEdges(int vertex, map<int, int>* m); //get adjacent edge function
	void insertEdge(int from, int to, int weight); //insert value in graph function
	bool printGraph(ofstream *fout); // print graph function
	int getvalue(int i, int j); //get edge function
	bool connect_vertex(int i, int j);//check connect vertex function
};

#endif