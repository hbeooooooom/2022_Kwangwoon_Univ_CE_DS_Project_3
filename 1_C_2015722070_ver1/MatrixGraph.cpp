#include "MatrixGraph.h"//MatrixGraph.cc includes MatrexGraph header file

MatrixGraph::MatrixGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)//constructor of MatrixGraph class
{	
	m_Mat = new int*[size];//dynamic allocation - 2 dimension
	for (int i = 0; i < size; i++)
		m_Mat[i] = new int[size];

	for (int i = 0; i < size; i++) {//initialize
		for (int j = 0; j < size; j++)
			m_Mat[i][j] = 0;
	}
}

MatrixGraph::~MatrixGraph()//destructor of MatrixGraph class
{	
	for (int i = 0; i < getSize(); i++)//dynamic deallocation - 2 dimension
		delete[] m_Mat[i];
	delete[] m_Mat;
}

void MatrixGraph::getIncidentEdges(int vertex, map<int, int>* m)//function that get the incidentedges
{	
	for (int j = 0; j < getSize(); j++) {//loop until j is greater than graph's size
		if (adjacent(vertex, j) != 0) {//if vertex and j isn't connected
			m[j].insert(make_pair((adjacent(vertex, j) + m[vertex].begin()->first), vertex));//insert in map
		}
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)//function that insert the data in m_Matrix
{
	m_Mat[from][to] = weight;//insert - array
}

bool MatrixGraph::printGraph(ofstream* fout)//function that prints the graph
{	
	if (m_Mat == NULL)//exception handling if m_Mat is empty
		return false;
	*fout << "======== PRINT =======" << endl;
	int size = getSize();
	//print all
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			*fout << m_Mat[i][j] << " ";//print
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;
	return true;
}
