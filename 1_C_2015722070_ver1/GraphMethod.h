#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"//GraphMethod.h includes ListGraph header file
#include "MatrixGraph.h"//GraphMethod.h includes MatrixGraph header file
#include "vertexSet.h"//GraphMethod.h includes vertexSet header file

bool BFS(Graph* graph, int vertex, ofstream* fout);//function that runs BFS
bool DFS(Graph* graph, int vertex, ofstream* fout);//function that runs DFS
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream* fout);//function that runs DFS(reclusive)
bool Kruskal(Graph* graph, ofstream* fout);//function that runs Kruskal
bool Dijkstra(Graph* graph, int vertex, ofstream* fout);//function that runs Dijkstra
#endif
