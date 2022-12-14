#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{
private:
	Graph* graph;
	Graph* nodirection_graph; //no direction graph
	ofstream fout;
	int load;

public:
	Manager();
	~Manager();

	void run(const char * command_txt);
	
	bool LOAD(char* filename); //LOAD function
	bool PRINT();//print function
	
	bool mBFS(int vertex);//BFS function
	bool mDFS_R(int vertex);//DFS_R function
	bool mDFS(int vertex);//DFS function
	bool mDIJKSTRA(int vertex);//DIJKSTRA function
	bool mKRUSKAL();//KRUSKAL function
	bool mBELLMANFORD(int s_vertex, int e_vertex); // BELLMANFORD function
	bool mFLOYD();// FLOYD function
	
	void printErrorCode(int n);

};

#endif