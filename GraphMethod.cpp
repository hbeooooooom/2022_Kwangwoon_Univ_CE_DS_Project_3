#include "GraphMethod.h"
#define MAX_INT 2147483647
#define MIN(a,b) a<b ? a:b
bool BFS(Graph *graph, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize())
        return false; // if vertex > size return false
    queue<int> q;
    map<int, int> adjacentnode;
    int front_value;
    bool *visited = new bool[graph->getSize()]{0}; // make arr
    visited[vertex] = true;

    *fout << "========== BFS ==========" << endl;
    *fout << "startvertex: " << vertex << endl;

    q.push(vertex);
    while (!q.empty())
    {
        front_value = q.front();
        graph->getAdjacentEdges(front_value, &adjacentnode); // get adj node
        q.pop();
        *fout << front_value;
        for (map<int, int>::iterator iter = adjacentnode.begin(); iter != adjacentnode.end(); iter++)
        {
            if (!visited[iter->first])
            {
                q.push(iter->first);
                visited[iter->first] = true; // set value true
            }
        }
        if (!q.empty())
        {
            *fout << " -> "; // if empty queue
        }
        else
            *fout << endl; // print value
    }
    *fout << "======================" << endl;
    delete[] visited;

    return true;
}
bool DFS(Graph *graph, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize())
        return false; // if vertex > size return false

    stack<int> s;
    map<int, int> adjacentnode;
    int back_value;

    bool *visited = new bool[graph->getSize()]{0};
    visited[vertex] = true;
    *fout << "========== DFS ==========" << endl;
    *fout << "startvertex: " << vertex << endl;
    s.push(vertex);
    while (!s.empty())
    {
        back_value = s.top();
        graph->getAdjacentEdges(back_value, &adjacentnode); // get adj node

        s.pop();
        *fout << back_value;
        for (map<int, int>::iterator iter = adjacentnode.end(); iter != adjacentnode.begin();)
        {
            iter--;
            if (!visited[iter->first])
            {
                s.push(iter->first);
                visited[iter->first] = true; // set value true
            }
        }
        if (!s.empty())
        {
            *fout << " -> "; // if stack empty
        }
        else
            *fout << endl; // print value
    }
    *fout << "======================" << endl;
    delete[] visited;

    return true;
}

bool DFS_R(Graph *graph, vector<bool> *visit, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize())
        return false;

    map<int, int> adjacentnode;
    graph->getAdjacentEdges(vertex, &adjacentnode); // get adj node
    for (map<int, int>::iterator iter = adjacentnode.begin(); iter != adjacentnode.end(); iter++)
    {
        if (visit->at(iter->first) == false)
        {
            (*visit)[iter->first] = true; // change value true
            *fout << " -> " << iter->first;
            DFS_R(graph, visit, iter->first, fout); // recursive DFS_R function
        }
    }
    return true;
}

bool Kruskal(Graph *graph, ofstream *fout)
{
}

bool Dijkstra(Graph *graph, int vertex, ofstream *fout)
{
    if (vertex >= graph->getSize() || vertex < 0)
        return false;

    *fout << "======= Dijkstra =======" << endl;
    *fout << "startvertex: " << vertex << endl;

    int *distance, *visit, *path;
    distance = new int[graph->getSize()]; // distance array
    visit = new int[graph->getSize()];    // visit check value array
    path = new int[graph->getSize()];     // path array

    for (int i = 0; i < graph->getSize(); i++)
    { // initializing
        distance[i] = 0;
        visit[i] = 0;
        path[i] = -1;
    }
    stack<int> s;
    s.push(vertex);
    int back_value; // pop stack valuue

    while (!s.empty())
    {
        back_value = s.top();
        visit[back_value] = 1;
        s.pop();

        for (int i = 0; i < graph->getSize(); i++)
        {
            if (i != back_value && graph->connect_vertex(back_value, i) == true && i != vertex)
            {
                if (visit[i] == 0)
                    s.push(i); // if first time visiting
                if ((distance[i] != 0 && distance[i] > (distance[back_value] + graph->getvalue(back_value, i))) || distance[i] == 0)
                {
                    distance[i] = distance[back_value] + graph->getvalue(back_value, i);
                    path[i] = back_value;
                }
            }
        }
    }
    int find_back_value;
    for (int i = 0; i < graph->getSize(); i++)
    {
        if (i == vertex)
        {
            continue;
        }
        *fout << "[" << i << "] ";

        find_back_value = i;
        stack<int> s;
        while (1)
        {
            if (path[find_back_value] == -1)
                break;

            s.push(path[find_back_value]);
            find_back_value = path[find_back_value];
        }
        if (s.empty())
        {
            *fout << "x" << endl;
            continue;
        }
        while (!s.empty())
        {
            *fout << s.top() << " -> ";
            s.pop();
        }

        *fout << i << " (" << distance[i] << ")" << endl;
    }
    return true;
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex, ofstream *fout)
{
    if (s_vertex > graph->getSize() || e_vertex >= graph->getSize())
        return false;

    bool *visited = new bool[graph->getSize()]{0};
    int distance[graph->getSize()];
    int prev[graph->getSize()];
    for(int i=0;i<graph->getSize();i++){
        distance[i]=MAX;
        prev[i]=-1;
    } 
    distance[s_vertex] = 0;     
    for(int i=1;i<=graph->getSize();i++) {
        for(int j=0;j<graph->getSize();j++){
            map<int,int> adjacentnode;
            if(distance[j] == MAX) continue;
            graph->getAdjacentEdges(j,&adjacentnode);
            for(map<int, int>::iterator iter=adjacentnode.begin();iter!=adjacentnode.end(); iter++){ // change path
                if(distance[iter->first] > distance[j]+iter->second){
                    distance[iter->first] = distance[j]+iter->second;
                    prev[iter->first] = j;

                    if(i==graph->getSize()) return false; //if negative cycle print error code
                }
            }
        }
    }

    *fout << "======Bellman-Ford======"<<endl;
    if(distance[e_vertex] == MAX) *fout << "x"; //if no path print x
    else{
        stack<int> s;
        for(int j=e_vertex;j!=-1;j=prev[j]) s.push(j);// push value in stack
        *fout << s.top();
        s.pop();
        while(!s.empty()){ //stack is empty finish path
            *fout << " -> " << s.top();
            s.pop();
        }
        *fout <<endl<<"cost: " << distance[e_vertex]; //print path weight
    }
    *fout << "\n====================\n";
    return true;
}



bool FLOYD(Graph *graph, ofstream *fout)
{
    int **distance;
    distance = new int *[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++)
    {
        distance[i] = new int[graph->getSize()];
    }

    for (int i = 0; i < graph->getSize(); i++) // initialize
    {
        for (int j = 0; j < graph->getSize(); j++)
        {
            if(i == j) distance[i][j] = 0;
            else if(graph->getvalue(i,j)!=0) distance[i][j] = graph->getvalue(i,j);
            else distance[i][j] = MAX;
        }
    }
    for (int k = 0; k < graph->getSize(); k++)
    {
        for (int i = 0; i < graph->getSize(); i++)
        {
            for (int j = 0; j < graph->getSize(); j++)
            {
                distance[i][j] = MIN(distance[i][j],distance[i][k]+distance[k][j]);
            }
        }
    }
    for(int i = 0; i<graph->getSize(); i++)
        for(int j =0;j<graph->getSize();j++)
            if(distance[i][j]<999999 && distance[i][j]>500000) return false;

    *fout<<"======== FLOYD ========="<<endl;
    *fout<<"\t";
    for(int i=0; i<graph->getSize(); i++)
	{
		*fout<<"["<<i<<"]"<<'\t';
	}
	*fout<<endl;

    for(int i = 0; i<graph->getSize(); i++)
    {
        *fout<<"["<<i<<"]";
        for(int j = 0; j<graph->getSize()&&*fout<<'\t'; j++)
        {
            if(distance[i][j] == 999999) *fout<<"x";
            else *fout<<distance[i][j];
        }
        *fout<<endl;
    }
    return true;
}