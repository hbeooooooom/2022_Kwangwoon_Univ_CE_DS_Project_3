#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define BFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL; // initialize m_pVHead 
    m_vSize = 0; // initialize m_vSize
}
Graph::~Graph()
{
    Clear(); // clear vertex
    m_pVHead = NULL; // initialize m_pVHead
    m_vSize = 0; // initialize m_vSize 
}

void Graph::AddVertex(int vertexKey)
{
    if(!m_pVHead) // m_pVHead is empty
    {
        Vertex* pNew = new Vertex(vertexKey); // allocate new Vertex node
        m_pVHead = pNew; // set m_pVHead to pNew
    }
    else
    {
        Vertex* pHead = m_pVHead; // set pHead is m_pVHead
        while(pHead->GetNext()) // move pHead to end
        {
            pHead = pHead->GetNext(); // move pHead to next
        }
        Vertex* pNew = new Vertex(vertexKey); // allcoate new Vertex node 
        pHead->SetNext(pNew); // pHead set next to new node
    }
    m_vSize++; // m_vSize plus 1
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
    Vertex* pVer = FindVertex(startVertexKey); // Find right Vertex
    pVer->AddEdge(endVertexKey, weight); // pVer add Edge node
}

Vertex* Graph::FindVertex(int key)
{
    Vertex* pFind = m_pVHead; // set pFind to m_pVHead
    while(pFind) // if pFind is not empty, doing loop
    {
        if(pFind->GetKey() == key) // if pFind key is same key
            break; // break and return pFind node
        pFind = pFind->GetNext(); // else pFind move to next
    }
    return pFind; // return pFind
}

bool Graph::IsNegativeEdge()
{
    Vertex* pHead = m_pVHead; // set pHead to m_pVHead
    while(pHead) // if pHead is not empty, doing loop
    {
        Edge* pEdge = pHead->GetHeadOfEdge(); // pEdge is Vertex's Head of Edge
        while(pEdge) // if pEdge is not empty, 
        {
            if(pEdge->GetWeight() < 0) // set pEdge wieght is negative 
                return true; // return true
            pEdge = pEdge->GetNext(); // move to pEdge is next
        }
        pHead = pHead->GetNext(); // pHead move to pHead
    }
    return false;
    
}

void Graph::Print(std::ofstream& fout)
{
    fout.open("log.txt", ios::app); // open log.txt file

    Vertex* pHead = m_pVHead;
    fout<< "==============" << "PRINT" << "===============" << endl;
    while(pHead)
    {
        // fout << pHead->getName() << " ";
        Edge* pEdge = pHead->GetHeadOfEdge(); // pEdge set pHead head of edge
        for(int i = 0 ; i < m_vSize; i++)
        {
            if(pEdge != NULL) // if pEdge is not empty
            {
                if(pEdge->GetKey() == i) // pEdge key is i
                {   
                    fout << pEdge->GetWeight() << " "; // print weight
                    pEdge = pEdge->GetNext();
                }
                else
                {
                    fout << 0 << " "; // if didn't have Edge print 0
                }
            }
            else
            {
                fout << 0 << " "; // if didn't have Edge print 0
            }
        }
        fout << endl; 
        pHead = pHead->GetNext(); // pHead move to next 
    }
    fout<< "====================================" << endl << endl;
    fout.close(); // close log.txt file
}

int Graph::Size() const
{
    return m_vSize; // return m_vSize
}

std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey)
{
    vector<int> result; 
    Vertex* pHead = m_pVHead; 
    vector<int> visit(m_vSize);
    queue<Vertex*> q;
    stack<pair<int,int>> move;
    pair<int,int> pairTemp;
    bool findPath = false;

    for(int i = 0 ; i < startVertexKey; i++)
    {
        pHead = pHead->GetNext(); // move startvalue 
    }

    visit[startVertexKey] = visited; // set visited startvalue
    q.push(pHead); // push to queue
    while(!q.empty() && !findPath) // if findpath is false
    {
        Vertex* pFront = q.front(); // set pFront is queue front
        Edge* pTemp = pFront->GetHeadOfEdge(); // set pTemp is pFornt head of edge
        q.pop(); // queue pop
        while(pTemp) 
        {
            Vertex* pPush = FindVertex(pTemp->GetKey()); // find Vertex and set pPush that value
            if(!visit[pPush->GetKey()]) // if pPush is didn't visited node
            {
                if(pTemp->GetWeight() > 0) // if pTemp weight is positive number or 0
                {
                    q.push(pPush); // set queue push pPush
                    visit[pPush->GetKey()] = visited; // set visited
                    move.push(make_pair(pFront->GetKey(), pPush->GetKey())); // set push move number
                    if(pPush->GetKey() == endVertexKey) // if endVertexKey is equal to pPush key
                    {
                        findPath = true; // set findpath is true
                        break; // loop is end
                    }
                }
            }
            pTemp = pTemp->GetNext(); // set pTemp is next Edge
        }
    }

    if(move.top().second != endVertexKey) // if move size is 0 return result
        return result; 
    int findNumber = move.top().first; // set findNumber is move top key
    result.push_back(move.top().second); // result push back move top value
    // using back trace for get shortest path 
    while(move.size() != 0)
    {
        if(findNumber == move.top().second)
        {
            result.push_back(findNumber);
            findNumber = move.top().first;
        }
        move.pop();
    }
    result.push_back(startVertexKey);
    return result; // return result
}

Vertex* Graph::getHead()
{
    return m_pVHead; // return
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    vector<vector<pair<int, int>>> graph;
    vector<pair<int,int>> graphTemp;
    set<pair<int, int>> s; // make set
    vector<int> result; // make result
    vector<int> dijkstra (m_vSize, IN_FINITY); // make dijkstra and initialize IN_FINITY
    vector<int> path (m_vSize, 0);

    //get graph to adjacency list
    Vertex* vHead = m_pVHead; // get Vertex Head
    while(vHead) // loop keep going vHead is not empty
    {
        Edge* eHead = vHead->GetHeadOfEdge(); // get vHead's Head of Edge
        graphTemp.clear(); // initilaize graphTemp
        for(int i = 0 ; i < m_vSize ; i++)
        {
            if(eHead != NULL) // if eHead is not NULL
            {
                if(eHead->GetKey() == i) // if eHead key is i
                {
                    if(eHead->GetWeight() <= 0) // eHead weight is 0 or negative
                    {
                        graphTemp.push_back(make_pair(eHead->GetKey(), IN_FINITY)); // graphTemp push key and IN_FINITY
                    }
                    else // else, grapTemp push back key and weight
                    {
                        graphTemp.push_back(make_pair(eHead->GetKey(), eHead->GetWeight()));
                    }
                    eHead = eHead->GetNext(); // move to eHead to next
                }
                else
                {
                    graphTemp.push_back(make_pair(i, IN_FINITY)); // else, graphTemp push back key is i, weight is IN_FINITY
                }
            }
            else
            {
                graphTemp.push_back(make_pair(i, IN_FINITY)); // else, graphTemp push back key is i, weight is IN_FINITY
            }
        }
        graph.push_back(graphTemp); // insert graph to graphTemp
        vHead = vHead->GetNext(); // move next vHead
    }

    s.insert(make_pair(startVertexKey, 0)); // visit startnode

    while(!s.empty()) // loop when s is not empty
    {
        int current = s.begin()->first;
        int distance = s.begin()->second;
        s.erase(make_pair(s.begin()->first, s.begin()->second));

        if(dijkstra[current] < distance) continue; // if visited node, continue
        
        for(int i = 0 ; i < graph[current].size(); i++)
        { 
            int next = graph[current][i].first; // set next is graph currnet i key
            int nextDistance = distance + graph[current][i].second; // set nextDistance is distance plus graph current i weight

            if(nextDistance < dijkstra[next]) // if nextDistance is smaller tahn dijkstra next
            {
                dijkstra[next] = nextDistance; // change value dijkstart next is nextDistance
                s.insert(make_pair(next,dijkstra[next])); // set insert key is next weight is dijkstra next
                path[next] = current; // path next is current
            }
        }

    }
 
    int temp = endVertexKey; // temp is endVertexKey
    result.push_back(temp); // result push back to temp
    while(path[temp] != startVertexKey) // if path temp is not startVertexKey
    {
        result.push_back(path[temp]); // result push path[temp]
        temp = path[temp]; // chage temp to path[temp]
    }
    result.push_back(startVertexKey); // result push back startVetexKey

    return result; // return result
}

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    vector<vector<pair<int, int>>> graph; // set graph 
    vector<pair<int,int>> graphTemp; // set graph temp for push back graphTemp
    vector<int> result; // make result
    vector<int> bellMan (m_vSize, IN_FINITY); // make Bellmanford and initialize IN_FINITY
    vector<int> path (m_vSize, 0);
    
    Vertex* pVertex = m_pVHead; // get Vertex Head
    for(int i = 0 ; i< m_vSize; i++) 
    {
        Edge* pEdge = pVertex->GetHeadOfEdge(); // edge is pVertex haed of edge
        graphTemp.clear(); // graphTemp clear
        while(pEdge)
        {
            graphTemp.push_back(make_pair(pEdge->GetKey(), pEdge->GetWeight())); // push back key and weight
            pEdge = pEdge->GetNext(); // pEdge move next value
        }
        graph.push_back(graphTemp); // graph push back graphTemp
        pVertex = pVertex->GetNext(); // pVetex move to next
    }
    
    bellMan[0] = 0; // set start is 0 
    for(int n = 0 ; n < m_vSize; n++) 
    {
        for (int i = 0 ; i < m_vSize ; i++)
        {
            for(int j = 0 ; j < graph[i].size(); j++)
            {
                int v = graph[i][j].first; // set v is i vertex j key
                int cost = graph[i][j].second; // set cost is i vertex j weight

                if(bellMan[i] != IN_FINITY && bellMan[v] > bellMan[i] + cost) // if bellMan is not IN_FINITY and bellMan 'n' is bigger than cost + bellMan i's
                {
                    bellMan[v] = bellMan[i] + cost; // change bellMan 'n' value 
                    path[v] = i; // set path[n] is i for find shortest path
                }
            }
        }
    }

    for(int i = 0 ; i< m_vSize; i++) // find negative cycle 
        {
            for(int j = 0 ; j < graph[i].size(); j++) 
            {
                int v = graph[i][j].first; // set v is i vertex j key
                int cost = graph[i][j].second; // set cost is i vertex j weight

                if(bellMan[i] != IN_FINITY && bellMan[v] > bellMan[i] + cost ) // if change value, exists negative cycle
                {
                    result.clear(); // result clear
                    result.push_back(-IN_FINITY); // result push back -IN_FINITY
                    return result; // return result
                }
            }
        }

    int temp = endVertexKey; // set temp is endKey
    result.push_back(temp); // push back result to temp

    while(path[temp] != startVertexKey) // if path[temp] is not startVertexkey
    {
        result.push_back(path[temp]); // push back path[temp]
        temp = path[temp]; // change temp is path[temp]
    }
    result.push_back(startVertexKey); // push back start key

    return result; // return result
}

 std::vector<vector<int> > Graph::FindShortestPathFloyd()
 {
    vector<vector<int>> floyd;
    vector<int> insertGraph;

    Vertex* pVertex = m_pVHead; // pVertex is set pHead
    int count = 0; // count is 0

    while(pVertex)
    {
        Edge* pEdge = pVertex->GetHeadOfEdge();  // set pEdge is pVertex head of Edge
        insertGraph.clear(); // insertGraph clear value
        for(int i = 0 ; i < m_vSize; i++)
        {
            if(pEdge != NULL) // if pEdge is not NULL
            {
                if(pEdge->GetKey() == i) // if pEdge key is i
                {
                    insertGraph.push_back(pEdge->GetWeight()); // insertGraph push back pEdge weight
                    pEdge = pEdge->GetNext(); // pEdge move to next pEdge
                }
                else if(count == i) // if count is i
                {
                    insertGraph.push_back(0); // set insertGraph 0
                }
                else
                {
                    insertGraph.push_back(IN_FINITY); // else, set insertGraph push back IN_FINITY
                }
            }
            else if(count == i) // if count is 0
            {
                insertGraph.push_back(0); // set insertGraph 0
            }
            else
            {
                insertGraph.push_back(IN_FINITY); // else, set insertGraph push back IN_FINITY
            }
        }
        floyd.push_back(insertGraph); // floyd push back insertGraph
        pVertex = pVertex->GetNext(); // pVertex move to next pVertex
        count++; // count is plus
    }
    
    for(int mid = 0; mid < m_vSize; mid++) 
    {
        for(int start = 0 ; start < m_vSize; start++)
        {
            for(int end = 0 ; end < m_vSize; end++)
            {
                if(floyd[start][mid] == IN_FINITY || floyd[mid][end] == IN_FINITY )
                if(floyd[start][mid] + floyd[mid][end] < floyd[start][end]) // if start to mid and mid to end weight is smaller than start to end
                {
                    floyd[start][end] = floyd[start][mid] + floyd[mid][end]; // change value start to end is start to mid and mid to end
                }
            }
        }
    }

    for(int i = 0 ; i < m_vSize; i++)
    {
        if(floyd[i][i] < 0) // if Vertext own Edge is negative number, graph have negative cycle
        {
            floyd.clear(); // set floyd clear() and break;
            break;
        }
    }
    return floyd; // return floyd
 }

 void Graph::Clear()
 {
    Vertex* pTemp = m_pVHead; // pTemp is m_pVHead
    if(pTemp)
    {
        Vertex* pNext = pTemp->GetNext(); // pNext is pTemp next
       while(pNext)
        {
            pTemp->Clear(); // pTemp deallocate Edge
            delete pTemp; // deallocate pTemp
            pTemp = pNext; // pTemp is pNext
            pNext = pNext->GetNext(); // pNext move to next
        }
        pTemp->Clear(); // pTemp clear
        delete pTemp; // deallocate pTemp 
    }
 }