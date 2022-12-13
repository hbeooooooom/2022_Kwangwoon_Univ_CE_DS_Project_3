#include "Manager.h"//Manager.cc includes Manager header file

Manager::Manager()//constructor of Manager
{
	fout.open("log.txt", ios::app);//file open
	load = 0;//load is 0
}

Manager::~Manager()//destructor of Manager class
{
	fout.close();//file close
	delete graph;
}

void Manager::run(const char* command_txt)//function that runs the commands
{
	ifstream fin;//declare the input stream	
	fin.open(command_txt);//file open
	if(!fin)//if file isn't open
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	//declare the values
	char*	str=NULL;
	char*	str2=NULL;
	char*	str3= NULL;
	char	buf[128]={0};

	while(fin.getline(buf, 64))//loop until end of file
	{
		str=strtok(buf, " \t\n");//using -strtok, divide the string, first of command
		str2 = strtok(NULL, " ");//str2, second of command
		str3 = strtok(NULL, " ");//str3, third of command
		if(strcmp(str, "LOAD") == 0)//if command is LOAD
		{
			if(str2== NULL)//exception handling
				printErrorCode(100);

			if(load == 1)//exception handling
			{
				printErrorCode(100);
			}
			else if(str3 != NULL || !LOAD(str2))//run and find the exception
			{
				printErrorCode(100);
			}
			else {//load success
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl << endl;
			}
			load = 1;
		}
		else if (strcmp(str, "PRINT") == 0) {//if command is PRINT
			if (str2 == NULL&&str3 == NULL) {
				if (PRINT() == false)//call the function and compare
					printErrorCode(200);
			}
			else {//exception handling
				printErrorCode(200);
			}
		}
		else if (strcmp(str, "BFS") == 0) {//if command is BFS
			if (str2 != NULL&&str3 == NULL) {
				if (mBFS(atoi(str2)) == false)//call the function and compare
					printErrorCode(300);
			}
			else {//exception handling
				printErrorCode(300);
			}
		}
		else if (strcmp(str, "DFS") == 0) {//if command is DFS
			if (str2 != NULL&&str3 == NULL) {
				if (mDFS(atoi(str2)) == false)//call the function and compare
					printErrorCode(400);
			}
			else {//exception handling
				printErrorCode(400);
			}
		}
		else if (strcmp(str, "DFS_R") == 0) {//if command is DFS_R
			if (str2 != NULL&&str3 == NULL) {
				if (mDFS_R(atoi(str2)) == false)//call the function and compare
					printErrorCode(500);
			}
			else {//exception handling
				printErrorCode(500);
			}
		}
		else if (strcmp(str, "Kruskal") == 0) {//if command is Kruskal
			if (str2 == NULL&&str3==NULL) {
				if (mKruskal() == false)//call the function and compare
					printErrorCode(600);
			}
			else {//exception handling
				printErrorCode(600);
			}
		}
		else if (strcmp(str, "Dijkstra") == 0) {//if command is Dijkstra
			if (str2 != NULL&&str3 == NULL) {
				if(mDijkstra(atoi(str2))==false)//call the function and compare
					printErrorCode(700);
			}
			else {//exception handling
				printErrorCode(700);
			}
		}
		else if (strcmp(str, "EXIT") == 0) {//if command is EXIT
			break;
		}
		else {//exception handling
		return;
		}
		fout<<endl;
	}	
	fin.close();
	return;
}

bool Manager::LOAD(char* filename)//function that LOAD the file
{	
	//declare the values
	char*	str=NULL;
	char*	str2=NULL;
	char*	str3 = NULL;
	char*	str4 = NULL;
	char*	str5 = NULL;
	char	buf[128]={0};
	char	buf2[128]={0};
	char	buf3[128] = {0};
	char start[64] = { 0 };
	bool type;
	int num;
	int i = 0;
	ifstream fin;//call the input stream
	fin.open(filename);//file open
	if(!fin)//if file isn't opened
	{	
		return false;
	}
	fin.getline(buf2,64);//read a line
	fin.getline(buf3, 64);//read a next line
	str2 = strtok(buf2, " ");//read a word in buf2
	str3 = strtok(NULL, " ");//read a next word in buf2
	str4 = strtok(NULL, " ");//read a next next word in buf2
	str5 = strtok(buf3, " ");//read a word in buf3
	num = atoi(str5);
	if (strcmp(str2, "L") == 0) {//if it is List graph
		type = false;//list
		graph = new ListGraph(type, atoi(str3), atoi(str4), num);//dynamic allocation
		while (fin.getline(buf, 64))//loop until end of file
		{
			str = strtok(buf, " \t\n");
			str2 = strtok(NULL, "WrWn");
			if (str2 == NULL) {//if str2 is NULL
				strcpy(start, str);//copy the from
			}
			else {
				graph->insertEdge(atoi(start), atoi(str), atoi(str2));//call the insert function
			}
			
		}
	}
	else if (strcmp(str2, "M") == 0) {//if it is matrix graph
		type = true;//matrix
		graph = new MatrixGraph(type, atoi(str3), atoi(str4), num);//dynamic allocation
		while (fin.getline(buf, 64))//loop until end of file
		{
				str = strtok(buf, " \t\n");
				for (int j = 0; j < num; j++){
					graph->insertEdge(i, j, atoi(str));//call the insert function
					str = strtok(NULL, " \t\n");
			}
				i++;
		}
	}
	else//exception processing
		return false; 
	
	return true;
}

void Manager::printErrorCode(int n)//function that print the error
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout << "=======================" << endl << endl;
}

bool Manager::PRINT()//function that runs print
{
	if(graph->printGraph(&fout)==false)//call the function
		return false;
//exception handling
	return true;
}
bool Manager::mDijkstra(int from)//function that runs mDijkstra
{
	//Graph* graph, int baseV, ofstream* fout
	if(Dijkstra(graph,from,&fout)==false)
		return false;
//exception handling
	return true;
}
bool Manager::mKruskal()//function that runs mKruskal
{	
	if(Kruskal(graph,&fout)==false)//call the function
		return false;
//exception handling
	return true;
}
bool Manager::mBFS(int ver)//function that runs mBFS
{
	if (BFS(graph, ver, &fout)==true) {//call the function
		return true;
	}
	else//exception handling
		return false;

}
bool Manager::mDFS_R(int ver)//function that runs mDFS(reclusive)
{
	if (graph == NULL)//exception handling - if graph is NULL
		return false;
	if (graph->getDirected() == true || graph->getWeighted() == true)//exception handling - if graph's directed is true or graph's weighted is true
		return false;
	if (ver > graph->getSize() || ver < 0)//exception handling- if input baseV is negative or is greater than graph's size
		return false;
	vector<bool> *visit = new vector<bool>(graph->getSize());//dynamic allocation

	for (int i = 0; i < graph->getSize(); i++)//initialize
		(*visit)[i] = false;
	fout << "======= DFS_R =======" << endl;
	if (DFS_R(graph,visit,ver,&fout) == true) {//call the DFS_R function
		fout << endl << "=====================" << endl << endl;
		delete[] visit;
		return true;
	}
	else {
		delete[] visit;
		return false;
	}

}
bool Manager::mDFS(int ver)//function that runs mDFS
{
	if (DFS(graph, ver, &fout) == true) {//call the function	
		return true;
	}
	else//exception handling
		return false;
}
