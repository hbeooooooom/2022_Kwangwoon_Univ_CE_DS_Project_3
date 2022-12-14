#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)//constructor
{
	m_Type = type; //initialize
	m_List = new map<int, int>[size]; //initialize
}

ListGraph::~ListGraph()//destructor
{
	delete[] m_List; 
}
int ListGraph::getvalue(int i, int j) //get edge function
{
	map<int,int>::iterator iter = m_List[i].find(j);
	if(iter == m_List[i].end()) return 0;// if not connect edge
	return m_List[i].find(j)->second; //connect
}
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	for(map<int, int>::iterator iter = m_List[vertex].begin(); iter!= m_List[vertex].end(); iter++)
	{
		m->insert({iter->first,iter->second}); //get adjacent edge in map stl
	}
}
bool ListGraph::connect_vertex(int i, int j)
{
	map<int, int>::iterator it;
	it = m_List[i].find(j);
	if (it != m_List[i].end() && it->second != 0) // if connected
		return true; //return ture
	else
		return false;
}
void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to,weight});//insert list
	return;
}

bool ListGraph::printGraph(ofstream *fout)
{
	*fout<<"Graph is ListGraph!"<<endl;

	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout<<" -> "; it_++)
		{
			*fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		*fout<<endl;
	}
	*fout<<endl;
	return 1;
}