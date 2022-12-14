#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)// constructor
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);//initialize
	}
}

MatrixGraph::~MatrixGraph()	// destructor
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];//memory free
	}
	delete[] m_Mat;//memory free
}
int MatrixGraph::getvalue(int i, int j)
{
	return m_Mat[i][j]; //get weight
}
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	for(int i = 0; i<getSize(); i++)
	{
		if(m_Mat[vertex][i] != 0)
		{
			m->insert({i,m_Mat[vertex][i]}); //insert map data
		}
	}
}
bool MatrixGraph::connect_vertex(int i, int j)
{
	if (m_Mat[i][j] != 0) // if connected
		return true; //return true
	else
		return false;
}
void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight;//insert weight
	return;
}

bool MatrixGraph::printGraph(ofstream *fout)
{
	if( m_Size < 0 )
		return 0;

	*fout<<"Graph is MatrixGraph!"<<endl;

	*fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]"<<'\t';
	}
	*fout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && *fout<<'\t'; j++)
		{
			*fout<<m_Mat[i][j];
		}
		*fout<<endl;
	}
	return 1;
}
