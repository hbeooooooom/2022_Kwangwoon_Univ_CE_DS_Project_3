#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}
int ListGraph::getvalue(int i, int j)
{
	map<int, int>::iterator iter = m_List[i].find(j);
	if(iter == m_List[i].end()) return 0;

	return m_List[i].find(j)->second;
}
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	for(map<int, int>::iterator iter = m_List[vertex].begin(); iter!= m_List[vertex].end(); iter++)
	{
		m->insert({iter->first,iter->second});
	}
}
void ListGraph::setdistance(int vertex,map<int, int>* m )
{
	for(int i = 0; i<getSize();i++)
	{
		if(getvalue(vertex,i)!=0)
		m[i].insert({getvalue(vertex,i)+m[vertex].begin()->first, vertex});
	}
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