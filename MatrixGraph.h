#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size);// constructor
	~MatrixGraph();	// destructor
		
	void getAdjacentEdges(int vertex, map<int, int>* m); //get adjacent edge function
	void insertEdge(int from, int to, int weight);//insert from vertex, to vertex, weight function
	bool printGraph(ofstream *fout);// print graph function
	int getvalue(int i, int j);//get weight function
	bool connect_vertex(int i, int j);//check connect function
};

#endif