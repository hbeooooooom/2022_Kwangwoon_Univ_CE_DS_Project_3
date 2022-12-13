#include "GraphMethod.h"

bool BFS(Graph* graph, int baseV, ofstream* fout)
{
	if (graph->getWeighted() == 1 || graph->getDirected() == 1) // check error
		return false;

	*fout << "======== BFS ========" << endl;
	bool * visited;
	visited = new bool[graph->getSize()];
	for (int i = 0; i < graph->getSize(); i++)
		visited[i] = false; // reset to false

	int temp;
	visited[baseV] = true;
	queue<int> q;
	q.push(baseV);

	while (1)
	{
		temp = q.front();
		q.pop();
		*fout << temp << " ";
		for (int i = 0; i < graph->getSize(); i++)
		{
			if (graph->getConnected(temp, i) == true && visited[i] == false && i != temp)
			{
				q.push(i);
				visited[i] = true;
			}
		}
		if (q.empty() == true) // if queue is empty, break.
			break;
	}
	*fout << endl << endl;
	delete[] visited;
	return true;
}

bool DFS(Graph* graph, int baseV, ofstream* fout)
{
	if (graph->getWeighted() == 1 || graph->getDirected() == 1) // check error
		return false;

	*fout << "======== DFS ========" << endl;
	bool * visited;
	visited = new bool[graph->getSize()];
 	for (int i = 0; i < graph->getSize(); i++) // reset to false,
		visited[i] = false;

	visited[baseV] = true;
	stack<int> q;
	q.push(baseV);
	int temp;

	while (1)
	{
		temp = q.top();
		q.pop();
		*fout << temp << " ";

		for (int i = graph->getSize()-1; i>=0; i--)
		{
			if (graph->getConnected(temp, i) == true && visited[i] == false && i != temp)
			{
				q.push(i);
				visited[i] = true;
			}
		}
		if (q.empty() == true) // if stack is empty, break.
			break;
	}

	*fout << endl << endl;
	delete[] visited;
	return true;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int baseV, ofstream* fout)
{
	if (graph->getWeighted() == 1 || graph->getDirected() == 1) // check error
		return false;

	*fout << "======== DFS_R ========" << endl;
	visit->at(baseV) = true;
	*fout << baseV << " ";

	for (int i = 0; i <graph->getSize(); i++)
	{
		if (graph->getConnected(baseV, i) == true && visit->at(i) == false && i != baseV)
		{
			visit->at(i) = true; // check the visit
			DFS_R(graph, visit, i, fout); // recursive
		}
	}
	
	return true;
}

bool Kruskal(Graph* graph, ofstream* fout)
{
	if (graph->getWeighted() == 0 || graph->getDirected() == 1) // check error
		return false;

	*fout << "======== Kruskal ========" << endl;

	vertexSet vs(graph->getSize()); // use to check cycle.

	multimap<int, pair<int, int> > edgelist; // all of edge insert here

	for (int i = 0; i < graph->getSize(); i++)
	{
		for (int j = 0; j < graph->getSize(); j++)
		{
			if (graph->getConnected(i, j) == true)
			{
				pair <int, int> p(i, j);
				edgelist.insert(make_pair(graph->getWeight(i, j), p)); // insert edge.
			}
		}
	}

	multimap<int, pair<int, int> > MST; // MST map.
	multimap<int, pair<int, int> >::iterator it;

	while (MST.size() != graph->getSize() - 1)
	{
		it = edgelist.begin();
		int temp1 = it->second.first;
		while (1) // check cycle
		{
			if (vs.Find(temp1) == it->second.second || vs.Find(temp1) == -1)
				break;
			else
				temp1 = vs.Find(temp1);
		}
		
		if (vs.Find(temp1) == -1) // if not cycle,
		{
			MST.insert(make_pair(it->first, it->second));
			vs.Union(it->second.first, it->second.second);
		}
		edgelist.erase(it); // erase from edgelist
	}

	it = MST.begin();
	int sum = 0;
	for (int i = 0; i < MST.size(); i++) // print MST edges, and make sum of the edges
	{
		sum += it->first;
		*fout << it->first << " ";
		it++;

		if (it == MST.end())
			break;
	}
	*fout << endl << sum << endl;

	return true;
}

bool Dijkstra(Graph* graph, int baseV, ofstream* fout)
{
	if (graph->getWeighted() == 0 || graph->getDirected() == 0) // check error
		return false;
	
	*fout << "======== Dijkstra ========" << endl;
	
	// data array of distance from baseV, visit, path
	int *distance, *visit, *path;
	distance = new int[graph->getSize()];
	visit = new int[graph->getSize()];
	path = new int[graph->getSize()];

	for (int i = 0; i < graph->getSize(); i++)
	{ // reset
		distance[i] = 0;
		visit[i] = 0;
		path[i] = -1;
	}

	stack<int> s;
	s.push(baseV);
	int from;

	while (1)
	{
		from = s.top();
		visit[from] = 1; // check visit
		s.pop();

		for (int i = 0; i < graph->getSize(); i++)
		{
			if (graph->getConnected(from, i) == true && i != from && i != baseV) // if connected, and not baseV
			{
				if(visit[i]==0) // first visit
					s.push(i);
				if ((distance[i] != 0 && distance[i] > (distance[from] + graph->getWeight(from, i))) || distance[i]==0) // check distance
				{
					distance[i] = distance[from] + graph->getWeight(from, i);
					path[i] = from;
				}
			}
		}

		if (s.empty() == true) // if stack is empty
			break;
	}
	*fout << baseV << endl;
	int pre; // use at find from vertex, baseV
	for (int i = 0; i < graph->getSize(); i++)
	{
		if (i == baseV)
			continue;
		pre = i;
		*fout << "[" << i << "]  ";
		while (1) // finding and printing the path to baseV
		{
			if (path[pre] == -1)
				break;
			*fout << path[pre] << " ";
			pre = path[pre];
		}
		*fout << "  [" << distance[i] << "]";
		*fout << endl;
	}
	return true;
}