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
    graph->getAdjacentEdges(vertex, &adjacentnode);
    for (map<int, int>::iterator iter = adjacentnode.begin(); iter != adjacentnode.end(); iter++)
    {
        if (visit->at(iter->first) == false)
        {
            (*visit)[iter->first] = true;
            *fout << " -> " << iter->first;
            DFS_R(graph, visit, iter->first, fout);
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

    map<int, int>* m= new map<int,int>[graph->getSize()];
    for(int i = 0; i<graph->getSize();i++)
    {
        m[0][i] = 0;
    }
    int count_v = 0;
    int v = vertex;

    for(;count_v!=(graph->getSize()-1);)
    {
        v = v % graph->getSize(); //v value set
        graph->setdistance(v,m);
        v++;
        count_v++;
    }
    for(int i =0; i < graph->getSize(); i++)
    {
        if(i == vertex) 
        {
            *fout<<"["<<i<<"] x"<<endl;
        }
        else if(m[i].empty() == true) //if empty array
        {
            *fout<<"["<<i<<"] x"<<endl;
        }
        else //not empty array
        {
            int j = i;
            *fout<<"[" <<i<<"]" ;
            while(j!=vertex)
            {
                *fout<< m[j].begin()->second<<"-> ";
                j = m[j].begin()->second;
            }
            *fout<<"("<<m[i].begin()->first<<")"<<endl;

        }
    }
    *fout<<"=========================" <<endl <<endl;
    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream *fout)
{

}

bool FLOYD(Graph* graph, ofstream *fout)
{

}