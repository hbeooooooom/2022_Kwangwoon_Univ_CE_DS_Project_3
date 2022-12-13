#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"//Manager.h includes GraphMethod header file

class Manager//declare and define the Manager class
{
private://declare the private members
	Graph* graph;//pointer that points the graph
	ofstream fout;//declare the create the file output stream
	int load;//load value

public://declare the public members
	Manager();//constructor of the Manager class
	~Manager();//destructor of the Manager class

	void	run(const char * command_txt);//function that runs the command
	
	bool	LOAD(char* filename);//function that loads the file(graph)
	bool	PRINT();//function that prints the graph
	
	bool	mDijkstra(int from);//function that runs Dijkstra
	bool	mKruskal();//function that runs Kruskal
	bool	mBFS(int ver);//function that runs BFS
	bool	mDFS_R(int ver);//function that runs DFS_R
	bool	mDFS(int ver);//funtion that runs DFS

	void	printErrorCode(int n);//function that prints the error
};//end

#endif
