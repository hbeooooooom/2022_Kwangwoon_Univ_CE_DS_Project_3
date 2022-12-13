#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)
{
	// dynamic allocation
	m_Mat = new int*[size];
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		for (int j = 0; j < size; j++) // set 0
			m_Mat[i][j] = 0;
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < m_Size; i++)
		delete[] m_Mat[i];
	delete[] m_Mat;
}

void MatrixGraph::getIncidentEdges(int vertex, map<int, int>* m)
{

}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight; // set edge
}

bool	MatrixGraph::printGraph(ofstream* fout)
{
	for (int i = 0; i < m_Size; i++) // row
	{
		for (int j = 0; j < m_Size; j++) // col
		{
			*fout << m_Mat[i][j] << " ";
		}
		*fout << endl;
	}

	return true;
}

bool MatrixGraph::getConnected(int from, int to)
{
	if (m_Mat[from][to] != 0) // if connected,
		return true;
	else
		return false;
}

int MatrixGraph::getWeight(int from, int to)
{
	return m_Mat[from][to]; // return weight of edge (from, to)
}