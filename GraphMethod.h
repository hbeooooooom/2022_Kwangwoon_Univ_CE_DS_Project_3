#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, int vertex, ofstream *fout); //BFS  function
bool DFS(Graph* graph, int vertex, ofstream *fout);//DFS function
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream *fout); //DFS_R function
bool Kruskal(Graph* graph, ofstream *fout); //Kruskal function
bool Dijkstra(Graph* graph, int vertex, ofstream *fout); //Dijkstra function
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ofstream *fout);//Bellman-Ford function
bool FLOYD(Graph* graph, ofstream *fout);// Floyd function
void quickSort(int arr[],int left,int right); //quick sort function
void InsertionSort(int arr[],int right); //Insertion sort function
int collapsingFind(int parent[], int i); //collapsing find function
int Union(int i, int j, int parent[]); //union function
#endif
