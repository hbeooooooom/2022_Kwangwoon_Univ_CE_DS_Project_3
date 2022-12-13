#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::out);
	load = 0;
}

Manager::~Manager()
{
	if (load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt) {
	ifstream fin;

	fin.open(command_txt);

	if (!fin)
	{
		fout << "[ERROR] command file open error!" << endl;
		return;
	}

	char* str = NULL;
	char* str2 = NULL;
	char cmd[129] = { 0 };
	while (!fin.eof())
	{

		while (fin.getline(cmd, 128))
		{
			str = strtok(cmd, " ");
			if (cmd == NULL) continue;
			if (strcmp(cmd, "LOAD") == 0) //if command LOAD
			{
				str2 = strtok(NULL, "\n");
				if (LOAD(str2)) { //success
					fout << " ======== LOAD =======" << endl;
					fout << "Success" << endl;
					fout << "====================" << endl;
				}
				else { printErrorCode(100); } //error code
			}
			else if (strcmp(cmd, "PRINT") == 0) // if command PRINT
			{
				if (!PRINT()) //if not success
				{
					printErrorCode(200); //print error code
				}
			}
			else if (strcmp(cmd, "BFS") == 0) //if command BFS
			{
				str2 = strtok(NULL, " ");
				string str_vt = str2;
				int int_vt = atoi(str_vt.c_str());
				if (!mBFS(int_vt))//if not success
				{
					printErrorCode(300); //print error code
				}
			}
			else if (strcmp(cmd, "DFS") == 0) // if command DFS
			{
				str2 = strtok(NULL, " "); //get number
				string str_vt = str2; //change string
				int int_vt = atoi(str_vt.c_str());//change int
				if (!mDFS(int_vt))
				{
					printErrorCode(400);
				}
			}
			else if (strcmp(cmd, "DFS_R") == 0) //if command DFS_R
			{
				str2 = strtok(NULL, " ");//get number
				string str_vt = str2;//change string
				int int_vt = atoi(str_vt.c_str());//change int
				if (!mDFS_R(int_vt))
				{
					printErrorCode(500);
				}
			}
			else if (strcmp(cmd, "DIJKSTRA") == 0) //if command DIJKSTRA
			{
				str2 = strtok(NULL, " "); //get number
				string str_vt = str2; //change string
				int int_vt = atoi(str_vt.c_str());//change int
				if (!mDIJKSTRA(int_vt))
				{
					printErrorCode(600);
				}
			}
		}

	}
	fin.close();

}



bool Manager::LOAD(char* filename)
{
	ifstream txt_open;
	txt_open.open(filename);//open graph file
	if (!txt_open) { return false; } //if file empty return false
	char cmd2[1000] = { 0 };
	txt_open.getline(cmd2, 100); //read type
	txt_open.getline(cmd2, 100); //read size
	string str_size = cmd2;
	int int_size = atoi(str_size.c_str());
	load = int_size;
	if (strcmp(filename, "graph_L.txt") == 0)
	{
		graph = new ListGraph(0, load); //make graph
		nodirection_graph = new ListGraph(0, load);//make no direction matrix graph
		string temp;
		while (txt_open.getline(cmd2, 100))
		{

			char* char_to_num = strtok(cmd2, " ");
			char* char__weight = strtok(NULL, " ");
			if (char__weight == NULL)
			{
				temp = char_to_num; //save first data
			}
			else
			{
				//change integer
				string str_to_num = char_to_num;
				int int_to_num = atoi(str_to_num.c_str());
				string str__weight = char__weight;
				int int__weight = atoi(str__weight.c_str());
				int int_temp = atoi(temp.c_str());

				graph->insertEdge(int_temp, int_to_num, int__weight); //push data
				if (nodirection_graph->getvalue(int_to_num, int_temp) < int__weight && nodirection_graph->getvalue(int_to_num, int_temp) != 0)
				{
					continue;
				}
				nodirection_graph->insertEdge(int_temp, int_to_num, int__weight);
				nodirection_graph->insertEdge(int_to_num, int_temp, int__weight);
			}
		}
	}
	else if (strcmp(filename, "graph_M.txt") == 0) //if Matrix graph
	{
		graph = new MatrixGraph(1, load); //make matrix graph
		nodirection_graph = new MatrixGraph(1, load);//make no direction matrix graph
		for (int i = 0; i < load; i++)
		{
			txt_open.getline(cmd2, 100);
			char* str = strtok(cmd2, " ");
			string string_weight = str;
			int int_weight = atoi(string_weight.c_str());
			graph->insertEdge(i, 0, int_weight);
			if (int_weight != 0) {
				nodirection_graph->insertEdge(i, 0, int_weight);
				nodirection_graph->insertEdge(0, i, int_weight);
			}
			for (int j = 1; j < load; j++) //push data
			{
				str = strtok(NULL, " ");
				string_weight = str;
				int_weight = atoi(string_weight.c_str());
				graph->insertEdge(i, j, int_weight);//push data
				if (int_weight == 0)
				{
					continue;
				}
				else
				{
					if (nodirection_graph->getvalue(j, i) < int_weight && nodirection_graph->getvalue(j, i) != 0)
					{
						int k = nodirection_graph->getvalue(j, i);
						nodirection_graph->insertEdge(i, j, k);
					}
					else
					{
						nodirection_graph->insertEdge(i, j, int_weight);
						nodirection_graph->insertEdge(j, i, int_weight);
					}
				}
			}
		}

		return true;
	}

}

bool Manager::PRINT() //print function
{
	if (nodirection_graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex) //bfs function
{

	if (graph == NULL)
		return false;
	if (!BFS(nodirection_graph, vertex, &fout)) return false;
	return true;
}

bool Manager::mDFS(int vertex) //dfs function
{
	if (graph == NULL) return false;
	DFS(nodirection_graph, vertex, &fout);
	return true;
}


bool Manager::mDFS_R(int vertex)//recursive dfs function
{
	if (graph == NULL) return false;
	if (vertex >= graph->getSize()) return false;
	vector<bool>* visit = new vector<bool>(graph->getSize());
	fout << "=========DFS_R=========" << endl;
	fout << "startvertex: " << vertex << endl;
	for (int i = 0; i < graph->getSize(); i++)
	{
		(*visit)[i] = false; //initializing
	}
	(*visit)[vertex] = true;
	fout << vertex << " ";
	if (DFS_R(nodirection_graph, visit, vertex, &fout))
	{

		fout << endl << "======================" << endl;
		//(*visit).clear();
		//vector<bool>*temp;
		//temp->swap(*visit);
		return true;
	}
	else
	{
		//delete[] visit;
		return false;
	}
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (graph == NULL) return false;

	if (!Dijkstra(graph, vertex, &fout)) //if Dijkstra return false
	{
		return false;//return false
	}
	return true;//else return true
}


void Manager::printErrorCode(int n)
{
	fout << "======== ERROR ========" << endl;
	fout << n << endl;
	fout << "=======================" << endl;
}
