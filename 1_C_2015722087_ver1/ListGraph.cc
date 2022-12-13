#include "ListGraph.h"

ListGraph::ListGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)
{
	// dynamic allocation
	m_List = new map <int, int>[size];
}

ListGraph::~ListGraph()
{
	delete [] m_List;
}

void ListGraph::getIncidentEdges(int vertex, map<int, int>* m)
{
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert(make_pair(to, weight)); // set edge
}

bool	ListGraph::printGraph(ofstream* fout)
{
	map<int, int>::iterator it;
	for (int i = 0; i < m_Size; i++) // from vertex i
	{
		it = m_List[i].begin(); // iterator point the edge of from i vertex
		*fout << i << " ";
		while (it != m_List[i].end())
		{
			*fout << it->first << "," << it->second << " ";
			it++;
		}
		*fout << endl;
	}

	return true;
}

bool ListGraph::getConnected(int from, int to)
{
	map<int, int>::iterator it;
	it = m_List[from].find(to);
	if (it != m_List[from].end() && it->second != 0) // if connected,
		return true;
	else
		return false;
}

int ListGraph::getWeight(int from, int to)
{
	map<int, int>::iterator it;
	it = m_List[from].find(to);
	if (it == m_List[from].end()) // not exist
		return 0;
	else // return weight
		return it->second;
}