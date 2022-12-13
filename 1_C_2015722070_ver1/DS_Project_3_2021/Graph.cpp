#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define BFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL;
    m_vSize = 0;
}

Graph::~Graph()
{

}

void Graph::AddVertex(int vertexKey)
{
    Vertex *v = new Vertex;
    v->SetKey(vertexKey);
    // empty graph
    if(m_pVHead == NULL){
        m_pVHead = v;
    }
    // first vertex exists
    else{
        Vertex *temp = m_pVHead;
        while(temp->GetNext() != NULL)
            temp = temp->GetNext();
        temp->SetNext(v);
    }
    m_vSize++;
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
    // find vertex and add edge to Vertex structure
    Vertex *v = FindVertex(startVertexKey);
    v->AddEdge(endVertexKey, weight);
}

Vertex* Graph::FindVertex(int key)
{
    Vertex *v = m_pVHead;
    if(v == NULL){
        cout << "no vertex" << endl;
        return 0;
    }

    for(int i = 0; i < m_vSize; i++){
        if(v->GetKey() == key)  // vertex founded
            return v;
        if(v->GetKey() != key)
            v = v->GetNext();
        if(v == NULL){          // vertex not founded
            return 0;
        }
    }
}

int Graph::Size() const
{
    return m_vSize;
}

void Graph::Clear()
{

}

void Graph::Print(std::ofstream& fout)
{
    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();
    
    fout << "======================= PRINT =======================" << endl;
    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            if(etemp == NULL){
                fout << "0 ";
            }
                
            else if(etemp->GetKey() == j){
                fout << etemp->GetWeight() << " ";
                etemp = etemp->GetNext();
            }
            else{
                fout << "0 ";
            }
                
        }
        fout << endl;
        vtemp = vtemp->GetNext();
        if(vtemp != NULL)
            etemp = vtemp->GetHeadOfEdge();
    }
    fout << "=====================================================" << endl << endl;
}

bool Graph::IsNegativeEdge()
{
    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();

    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            if(etemp->GetWeight() < 0)  // negative edge detected
                return 1;

            etemp = etemp->GetNext();    
            if(etemp == NULL)
                break;
        }
        vtemp = vtemp->GetNext();
        if(vtemp != NULL)
            etemp = vtemp->GetHeadOfEdge();
    }
    return 0;
}

std::vector<int> Graph::FindPathBfs()
{
    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();

    vector<int> v;
    vector<int> d;
    queue<int> q;

    vector<vector<int>> e;
    e.resize(m_vSize);

    // get key information about edge and store in vector e
    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            e[i].push_back({etemp->GetKey()});

            etemp = etemp->GetNext();    
            if(etemp == NULL)
                break;
        }
        vtemp = vtemp->GetNext();
        if(vtemp != NULL)
            etemp = vtemp->GetHeadOfEdge();
    }   

    d.resize(m_vSize, -1);
    d[0] = 0;
    q.push(0);

    // BFS algorithm
    while(!q.empty()){
        int temp = q.front();
        q.pop();

        for(int i = 0; i < e[temp].size(); i++){
            if(e[temp].front() < 0) continue;   // if negative edge detected, skip
            int now = e[temp][i];
            if(d[now] == -1){
                q.push(now);
                d[now] = d[temp] + 1;
            }
        }
    }
    v.push_back(d[m_vSize-1]);
    return v;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet()
{
    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();

    vector<int> v;
    vector<int> d;
    vector<vector<pair<int,int>>> e;
    e.resize(m_vSize);
    d.resize(m_vSize, IN_FINITY);
    // get key and weight information about edge and store in vector e
    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            e[i].push_back({etemp->GetKey(), etemp->GetWeight()});

            etemp = etemp->GetNext();    
            if(etemp == NULL)
                break;
        }
        vtemp = vtemp->GetNext();
        if(vtemp != NULL)
            etemp = vtemp->GetHeadOfEdge();
    }   

    set<pair<int,int>> s;   // use stl set
    s.insert({0, 0});
    d[0] = 0;

    // dijkstra algorithm
    while(!s.empty()){
        int u = s.begin()->second, ud = s.begin()->first;
        s.erase(s.begin());

        if(d[u] < ud)    continue;
        for(int i = 0; i < e[u].size(); i++){
            if(e[u][i].second < 0){ // negative edge detected
                continue;           // skip
            }
            int v = e[u][i].first;
            int vd = ud + e[u][i].second;
            if(d[v] > vd){
                s.erase({d[v],v});
                d[v] = vd;
                s.insert({d[v], v});
            }
        }
    }
    v.push_back(d[m_vSize-1]);  // put the distance betweeen our company and target company
    return v;
}

std::vector<int> Graph::FindShortestPathBellmanFord()
{
    vector<int> v(0);

    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();

    int d[m_vSize];
    for(int i = 0; i < m_vSize; i++)
        d[i] = IN_FINITY;
    d[0] = 0;

    // BellmanFord algorithm, check theNumberOfVertex-1 times
    for(int k = 0; k < m_vSize - 1; k++){
        for(int i = 0; i < m_vSize; i++){
            for(int j = 0; j < m_vSize; j++){
                int from = i;
                int to = etemp->GetKey();
                int cost = etemp->GetWeight();

                if(d[from] == IN_FINITY) continue;
                if(d[to] > d[from] + cost)
                    d[to] = d[from] + cost;

                etemp = etemp->GetNext();    
                if(etemp == NULL)
                    break;
            }
            vtemp = vtemp->GetNext();
            if(vtemp != NULL)
                etemp = vtemp->GetHeadOfEdge();
        }
        
        vtemp = m_pVHead;
        etemp = vtemp->GetHeadOfEdge();
    }
    v.push_back(d[m_vSize-1]);  // last element is distance

    // check if negative cycle exits
    vtemp = m_pVHead;
    etemp = vtemp->GetHeadOfEdge();
    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            int from = i;
            int to = etemp->GetKey();
            int cost = etemp->GetWeight();

            if(d[from] == IN_FINITY) continue;
            if(d[to] > d[from] + cost){ // negative cycle exists
                v.push_back(IN_FINITY);
                return v;
            }

            etemp = etemp->GetNext();    
                if(etemp == NULL)
                    break;
        }
        vtemp = vtemp->GetNext();
            if(vtemp != NULL)
                etemp = vtemp->GetHeadOfEdge();
    }
    return v;
}
    
std::vector<vector<int>> Graph::FindShortestPathFloyd()
{
    Vertex *vtemp = m_pVHead;
    Edge *etemp = vtemp->GetHeadOfEdge();

    vector<vector<int>> v(m_vSize, vector<int>(m_vSize, 0));
    vector<vector<int>> v2(m_vSize, vector<int>(m_vSize, 0));

    // get edge weight information and store in vector v
    for(int i = 0; i < m_vSize; i++){
        for(int j = 0; j < m_vSize; j++){
            if(i == j){
                v[i][j] = 0;
            }
            else if(etemp == NULL){
                v[i][j] = IN_FINITY;
            }
            else if(etemp->GetKey() == j){
                v[i][j] = etemp->GetWeight();
                etemp = etemp->GetNext();
            }
            else{
                v[i][j] = IN_FINITY;
            }
                
        }
        vtemp = vtemp->GetNext();
        if(vtemp != NULL)
            etemp = vtemp->GetHeadOfEdge();
    }

    // floyd algorithm
    for(int k = 0; k < m_vSize; k++){
        for(int i = 0; i < m_vSize; i++){
            for(int j = 0; j < m_vSize; j++){
                int temp = v[i][k] + v[k][j];
                if(temp < v[i][j])
                    v[i][j] = temp;
            }
            // if negative cycle exists
            if(v[i][i] < 0)
                return v2;  // v2 element is 0
        }
    }

    return v;
}