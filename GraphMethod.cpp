#include "GraphMethod.h"

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
        graph->getAdjacentEdges(front_value,&adjacentnode);
        q.pop();
        *fout<<front_value;
        for(map<int,int>::iterator iter = adjacentnode.begin(); iter!=adjacentnode.end();iter++)
        {
            if(!visited[iter->first])
            {
                q.push(iter->first);
                visited[iter->first] = true;
            }
        }
        if(!q.empty())
        {
            *fout<<" -> ";
        }
        else
            *fout<<endl;
    }
    *fout<<"======================"<<endl;
    delete [] visited;

    return true;
}
bool DFS(Graph* graph, int vertex, ofstream* fout)
{
    if(vertex >= graph->getSize()) return false;

    stack<int>s;
    map<int,int> adjacentnode;
    int back_value;

    bool* visited = new bool[graph->getSize()]{0};
    visited[vertex] = true;
    *fout<<"========== DFS =========="<<endl;
    *fout<<"startvertex: "<<vertex<<endl;
    s.push(vertex);
    while(!s.empty())
    {
        back_value = s.top();
        graph->getAdjacentEdges(back_value,&adjacentnode);

        s.pop();
        *fout<<back_value;
        for(map<int,int>::iterator iter = adjacentnode.begin(); iter!=adjacentnode.end();iter++)
        {
            if(!visited[iter->first])
            {
                s.push(iter->first);
                visited[iter->first] = true;
            }
        }
        if(!s.empty())
        {
            *fout<<" -> ";
        }
        else
            *fout<<endl;
    }
    *fout<<"======================"<<endl;
    delete [] visited;

    return true;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex)
{

}

bool Kruskal(Graph* graph)
{

}

bool Dijkstra(Graph* graph, int vertex)
{

}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex)
{

}

bool FLOYD(Graph* graph)
{

}