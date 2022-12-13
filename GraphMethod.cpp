#include "GraphMethod.h"
#define MAX_INT 2147483647;
bool BFS(Graph* graph, int vertex,ofstream* fout)
{
    if(vertex >= graph->getSize()) return false; // if vertex > size return false
    queue<int> q;
    map<int,int> adjacentnode;
    int front_value;
    bool* visited = new bool[graph->getSize()]{0}; //make arr
    visited[vertex] = true;

    *fout<<"========== BFS =========="<<endl;
    *fout<<"startvertex: "<<vertex<<endl;
    
    q.push(vertex);
    while(!q.empty())
    {
        front_value = q.front();
        graph->getAdjacentEdges(front_value,&adjacentnode); //get adj node
        q.pop();
        *fout<<front_value;
        for(map<int,int>::iterator iter = adjacentnode.begin(); iter!=adjacentnode.end();iter++)
        {
            if(!visited[iter->first])
            {
                q.push(iter->first);
                visited[iter->first] = true;//set value true
            }
        }
        if(!q.empty())
        {
            *fout<<" -> "; //if empty queue
        }
        else
            *fout<<endl; //print value
    }
    *fout<<"======================"<<endl;
    delete [] visited;

    return true;
}
bool DFS(Graph* graph, int vertex, ofstream* fout)
{
    if (vertex >= graph->getSize()) return false;// if vertex > size return false

    stack<int>s;
    map<int, int> adjacentnode;
    int back_value;

    bool* visited = new bool[graph->getSize()]{ 0 };
    visited[vertex] = true;
    *fout << "========== DFS ==========" << endl;
    *fout << "startvertex: " << vertex << endl;
    s.push(vertex);
    while (!s.empty())
    {
        back_value = s.top();
        graph->getAdjacentEdges(back_value, &adjacentnode); //get adj node

        s.pop();
        *fout << back_value;
        for (map<int, int>::iterator iter = adjacentnode.end(); iter != adjacentnode.begin(); )
        {
            iter--;
            if (!visited[iter->first])
            {
                s.push(iter->first);
                visited[iter->first] = true; //set value true
            }
        }
        if (!s.empty())
        {
            *fout << " -> "; // if stack empty
        }
        else
            *fout << endl; //print value
    }
    *fout << "======================" << endl;
    delete[] visited;

    return true;
}


bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream* fout)
{
    if (vertex >= graph->getSize()) return false;

    map<int, int> adjacentnode;
    graph->getAdjacentEdges(vertex, &adjacentnode); //get adj node
    for (map<int, int>::iterator iter = adjacentnode.begin(); iter != adjacentnode.end(); iter++)
    {
        if (visit->at(iter->first) == false)
        {
            (*visit)[iter->first] = true; //change value true
            *fout << " -> " << iter->first;
            DFS_R(graph, visit, iter->first, fout); //recursive DFS_R function
        }
    }
    return true;
}

bool Kruskal(Graph* graph, ofstream *fout)
{

}

bool Dijkstra(Graph* graph, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize()) return false;

    *fout<<"======= Dijkstra ======="<<endl;
    *fout<<"startvertex: "<<vertex<<endl;

    int *distance, *visit, *path;
	distance = new int[graph->getSize()]; // distance array
	visit = new int[graph->getSize()]; //visit check value array
	path = new int[graph->getSize()]; //path array

	for (int i = 0; i < graph->getSize(); i++)
	{ // initializing
		distance[i] = 0;
		visit[i] = 0;
		path[i] = -1;
	}
    stack<int> s;
	s.push(vertex);
	int back_value; //pop stack valuue

    while(!s.empty())
    {
        back_value = s.top();
        visit[back_value] = 1;
        s.pop();

        for(int i = 0; i<graph->getSize(); i++)
        {
           if(graph -> connect_vertex(back_value,i) == true && i != back_value && i != vertex)
           {
                if(visit[i]==0) s.push(i); //if first time visiting
                if ((distance[i] != 0 && distance[i] > (distance[back_value] + graph->getvalue(back_value, i))) || distance[i]==0)
                {
                    distance[i] = distance[back_value] + graph->getvalue(back_value,i);
                    path[i] = back_value;
                }
           }
        }
    }
    int find_back_value;
    for(int i = 0; i<graph->getSize();i++)
    {
        if(i == vertex) {
            continue;
        }
        *fout <<"[" << i <<"] ";

        find_back_value = i;
        stack<int>s;
        while(1)
        {
            if(path[find_back_value] == -1) break;

            s.push(path[find_back_value]);
            find_back_value = path[find_back_value];
        }
        if(s.empty()){
            *fout <<"x"<<endl;
            continue;
        }
        while(!s.empty())
        {
            *fout<<s.top()<<" -> ";
            s.pop();
        }
        
        *fout << i <<" ("<< distance[i] << ")" <<endl;
    }
    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream *fout)
{
    if (s_vertex > graph->getSize()||e_vertex > graph->getSize()) return false;

    *fout<<"======= Bellman-Ford ======="<<endl;
    int *distance, *path;
	distance = new int[graph->getSize()]; // distance array
	path = new int[graph->getSize()]; //path array

}

bool FLOYD(Graph* graph, ofstream *fout)
{

}