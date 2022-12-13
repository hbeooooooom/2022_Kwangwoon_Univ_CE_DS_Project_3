#include "Manager.h"

Manager::Manager()
{
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	fout.close();
}

void Manager::run(const char* command_txt)
{
	ifstream fin;		fin.open(command_txt);

	if (!fin) // file open error
	{
		cout << "[ERROR] command file open error!" << endl;
		return;
	}

	char*	str = NULL;
	char*	str2 = NULL;
	char	buf[128] = { 0 };
	fout << "Program Start." << endl;
	while (fin.getline(buf, 64)) // first line load at buf
	{
		str = strtok(buf, " ");

		if (strcmp(str, "LOAD") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) == NULL)
				printErrorCode(100);

			if (load == 1)
			{
				printErrorCode(100);
			}
			else if ((str2 = strtok(NULL, " \t\r")) != NULL)
			{
				printErrorCode(100);
			}
			else if (!LOAD(str))
			{
				printErrorCode(100);
			}
			load = 1;
		}
		else if (strcmp(str, "PRINT") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) != NULL)
				printErrorCode(200);

			if (load == 0)
			{
				printErrorCode(200);
			}
			else if (!PRINT())
			{
				printErrorCode(200);
			}
		}
		else if (strcmp(str, "BFS") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) == NULL)
				printErrorCode(300);

			if (load == 0) // no graph.
			{
				printErrorCode(300);
			}
			else if (!mBFS(atoi(str)))
			{
				printErrorCode(300);
			}
		}
		else if (strcmp(str, "DFS") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) == NULL)
				printErrorCode(400);

			if (load == 0)
			{
				printErrorCode(400);
			}
			else if (!mDFS(atoi(str)))
			{
				printErrorCode(400);
			}
		}
		else if (strcmp(str, "DFS_R") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) == NULL)
				printErrorCode(500);

			if (load == 0)
			{
				printErrorCode(500);
			}
			else if (!mDFS_R(atoi(str)))
			{
				printErrorCode(500);
			}
		}
		else if (strcmp(str, "Kruskal") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) != NULL)
				printErrorCode(600);

			if (load == 0)
			{
				printErrorCode(600);
			}
			else if (!mKruskal())
			{
				printErrorCode(600);
			}
		}
		else if (strcmp(str, "Dijkstra") == 0)
		{
			if ((str = strtok(NULL, " \t\r")) == NULL)
				printErrorCode(700);

			if (load == 0)
			{
				printErrorCode(700);
			}
			else if (!mDijkstra(atoi(str)))
			{
				printErrorCode(700);
			}
		}
		else if (strcmp(str, "EXIT") == 0)
		{
			fout << "Program End." << endl;
			break;
		}
		fout << endl;
	}
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	char*	str = NULL;
	char*	str2 = NULL;
	char	buf[128] = { 0 };
	char	buf2[128] = { 0 };

	ifstream fin;
	fin.open(filename);

	if (!fin)
	{
		return false;
	}

	fout << "======== LOAD ========" << endl;

	fin.getline(buf, '\r');
	str = strtok(buf, " ");
	str2 = strtok(NULL, "\r");

	if (buf[0] == 'L') // Load to ListGraph
	{
		str = strtok(&buf[2], " ");
		str2 = strtok(NULL, " ");

		fin.getline(buf2, '\r');
		int size = atoi(buf2);

		graph = new ListGraph(0, atoi(str), atoi(str2), size); // set ListGraph.

		fin.getline(buf, '\r');
		while (fin.eof() != true)
		{
			int fromVertex = atoi(buf);
			while (1)
			{
				fin.getline(buf, '\r');
				if (buf[0] == NULL)
					return true;

				if (strlen(buf) == 1) // if buf line mean fromVertex
					break;
				else
				{
					str = strtok(buf, " ");
					str2 = strtok(NULL, " ");
					graph->insertEdge(fromVertex, atoi(str), atoi(str2)); // insert Edge.
				}
			}
		}
	}
	else if (buf[0] == 'M') // Load to MatrixGraph
	{
		str = strtok(&buf[2], " ");
		str2 = strtok(NULL, " ");

		fin.getline(buf2, '\r');
		int size = atoi(buf2);

		graph = new MatrixGraph(1, atoi(str), atoi(str2), size); // set MatrixGraph

		for (int i = 0; i<size; i++)
		{
			fin.getline(buf, 128);
			str = strtok(buf, " ");
			for (int j = 0; j < size; j++)
			{
				graph->insertEdge(i, j, atoi(str)); // insert Edge.
				str = strtok(NULL, " ");
			}
		}
	}
	else // fail to Load
	{
		fin.close();
		return false;
	}
	fout << "Success" << endl;
	fout << "=========================" << endl;
	fin.close();
	return true;
}

bool Manager::PRINT()
{
	fout << "======== PRINT ========" << endl;
	if (graph->printGraph(&fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

bool	Manager::mDijkstra(int ver)
{
	if (Dijkstra(graph, ver, &fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

bool	Manager::mKruskal()
{
	if (Kruskal(graph, &fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

bool	Manager::mBFS(int ver)
{
	if (BFS(graph, ver, &fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

bool	Manager::mDFS_R(int ver)
{
	vector<bool> visit(graph->getSize(), false);
	if (DFS_R(graph, &visit, ver, &fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

bool	Manager::mDFS(int ver)
{
	if (DFS(graph, ver, &fout) == false)
		return false;
	else
	{
		fout << "=======================" << endl;
		return true;
	}
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}