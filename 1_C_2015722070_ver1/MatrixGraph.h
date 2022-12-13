#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"//MatrixGraph.h includes Graph headerfile

class MatrixGraph : public Graph//declare and define MatrixGraph class that inherit the Graph class
{
private://declare the private member
	int**	m_Mat;//2-dimension array that save the matrix

public://declare the public member
	MatrixGraph(bool type, bool directed, bool weighted, int size);//constructor of the MatrixGraph class
	~MatrixGraph();	//destructor of the MatrixGraph class
		
	void getIncidentEdges(int vertex, map<int, int>* m);//function that the insert to map-m
	void	insertEdge(int from, int to, int weight);//function that insert the data in m_Mat
	bool	printGraph(ofstream* fout);//function that prints the matrix
	int adjacent(int from, int to) {//function that return the weight
		if (m_Mat[from][to] == 0) {//if from vertex and to vertex isn't conneted
			return 0;//0 returns
		}
		else//if is connected
			return m_Mat[from][to];//weight returns
	}
};//end

#endif
