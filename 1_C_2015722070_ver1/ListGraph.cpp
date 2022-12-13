#include "ListGraph.h"//ListGraph.cc include ListGraph header file

ListGraph::ListGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)//constructor of ListGraph class
{	
	m_List = new map<int, int>[size];//dynamic allocation
}

ListGraph::~ListGraph()//destructor of ListGraph class
{
	delete m_List;//dynamic deallocation
}

void ListGraph::getIncidentEdges(int vertex, map<int, int>* m)//function that get the incidentedges
{	
		for (int j = 0; j < getSize(); j++) {//loop until j is greater than graph's size
			if (adjacent(vertex, j) != 0) {//if vertex and j isn't connected
				m[j].insert(make_pair((adjacent(vertex,j)+m[vertex].begin()->first),vertex));//insert in map
			}
		}
}

void ListGraph::insertEdge(int from, int to, int weight)//function that insert the data in m_List
{	
	m_List[from].insert(make_pair(to, weight));//insert - map
}

bool ListGraph::printGraph(ofstream* fout)//function that prints the graph
{
	if (m_List == NULL)//exception handling if m_List is empty
		return false;
	map<int, int>::iterator i;//declare the iterator
	*fout << "======== PRINT =======" << endl;
	int size = getSize();
	for (int from = 0; from < size; from++) {//loop until from is greater than or equal the size
		*fout << from << " ";
//print all
		for (i = m_List[from].begin(); i != m_List[from].end(); i++)
			*fout << i->first << "," << i->second << " ";
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;
	return true;//true return
}
