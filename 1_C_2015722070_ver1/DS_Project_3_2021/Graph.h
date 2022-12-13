#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
#define IN_FINITY 999999
#define visited true
#define unvisited false

class Graph
{
private:
    Vertex* m_pVHead;   // the head pointer for the linked list of the vertics
    int m_vSize;        // the number of the vertics

public:
	Graph();    // constructor
	~Graph();   // destructor
    void AddVertex(int vertexKey);      // add vertex with vertexNum at the end of the linked list for the vertics
    void AddEdge(int startVertexKey, int endVertexKey, int weight); // add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
    Vertex* FindVertex(int key);        // get the vertex which the key is vertexNum
    int Size() const;                   // get the number of the vertics
    void Clear();                       // memory free for the vertics
    void Print(std::ofstream& fout);    // print out the graph as matrix form
    bool IsNegativeEdge();              // check whether the graph has negative edge or not
	std::vector<int> FindPathBfs();                         // find the path from startVertexKey to endVertexKey with BFS
    std::vector<int> FindShortestPathDijkstraUsingSet();    // find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
    std::vector<int> FindShortestPathBellmanFord();         // find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
    std::vector<vector<int>> FindShortestPathFloyd();       // find the shortest path from startVertexKey to endVertexKey with Floyd
};

#endif
