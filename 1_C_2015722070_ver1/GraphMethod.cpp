#include "GraphMethod.h"//GraphMethod'cc includes the GraphMethod header file

bool BFS(Graph* graph, int baseV, ofstream* fout)//function that runs BFS
{
	if (graph == NULL)//exception handling - if graph is NULL
		return false;
	if (graph->getDirected() == true || graph->getWeighted() == true)//exception handling - if graph's directed is true, if graph's weighted is true
		return false;
	if (baseV > graph->getSize() || baseV < 0)//exception handling- if input baseV is negative or is greater than graph's size
		return false;
	bool *array = new bool[graph->getSize()];//dynamic allocation
	for (int i = 0; i < graph->getSize(); i++)//initialize
		array[i] = false;//array's value is false

	queue<int> q;//declare queue, int
	q.push(baseV);//push the baseV in q
	array[baseV] = true;//mark the baseV
	*fout << "======== BFS ========" << endl;//print
	while(!q.empty()) {//until q is empty, loop
		baseV = q.front();//baseV is q's front
		*fout << baseV << " ";
		q.pop();//pop, queue
		for (int i = 0; i < graph->getSize(); i++) {//loop, until i is greater than graph's size
			if (graph->adjacent(baseV, i) == 0)//if baseV and i isn't connected
				continue;//continue
			else {//if is connected
				if (array[i] == false) {//if i isn's marked
					q.push(i);//push i in q
					array[i] = true;//mark the i
				}
			}
		}
	}
	*fout << endl << "=====================" << endl << endl;
	delete array;
	return true;//true return
}

bool DFS(Graph* graph, int baseV, ofstream* fout)//function that runs DFS
{
	if (graph == NULL)//exception handling - if graph is NULL
		return false;
	if (graph->getDirected() == true || graph->getWeighted() == true)//exception handling - if graph's directed is true or graph's weighted is true
		return false;
	if (baseV > graph->getSize() || baseV < 0)//exception handling- if input baseV is negative or is greater than graph's size
		return false;
	bool *array = new bool[graph->getSize()];//dynamic allocation
	for (int i = 0; i < graph->getSize(); i++)//loop until i is greater than graph's size
		array[i] = false;//mark i
	stack<int> s;//declare stack, int
	int pCur;
	s.push(baseV);//push baseV in s
	array[baseV] = true;//mark baseV
	*fout << "======== DFS ========" << endl;
	while (!s.empty()) {//loop until stack is empty
		pCur = s.top();//pCur is stack's top
		*fout << pCur << " ";
		s.pop();//pop, stack
		if (array[pCur] == false) {//if pCur isn't marked
			array[pCur] = true;//mark pCur
		}
		for (int i = graph->getSize() - 1; i > -1; i--) {//loop reverse
			if (graph->adjacent(pCur, i) == 0)//if pCur and i isn't connected
					continue;//continue
			else//if is connected
				if (array[i] == false)//if i isn't marked
					s.push(i);//push i in s
		}
	}
	*fout << endl << "=====================" << endl << endl;
	delete array;
	return true;//true returns
}

bool DFS_R(Graph* graph, vector<bool>* visit, int baseV, ofstream* fout)//function that runs DFS(reclusize)
{	
	if (graph->getDirected() == true || graph->getWeighted() == true)//exception handling - if graph's directed is true or graph's weighted is true
		return false;
	(*visit)[baseV] = true;//make baseV
	*fout << baseV << " ";
	for (int i = 0; i < graph->getSize(); i++) {//loop until i is greater than graph's size
		if (graph->adjacent(baseV, i) == 0)//if baseV and i isn't connected
			continue;//continue
		else {//if is connected
			if ((*visit)[i] == false)//if i isn't marked
				DFS_R(graph, visit, i, fout);//reclusive
		}
	}
	return true;//true return
}

bool Kruskal(Graph* graph, ofstream* fout)//function that runs Kruskal
{
	if (graph == NULL)//exception handling - if graph is NULL
		return false;
	if (graph->getDirected() == true||graph->getWeighted()==false)//exception handling - if graph's directed is true or graph's weighted is false
		return false;

	vertexSet set(graph->getSize());//dynamic allcation
	multimap<int, pair<int, int> > weight, kruskal;;//declare map
	multimap<int, pair<int, int> >::iterator kru, ins;//declare iterator
//weight- multimap, insert the key = weight
	for (int i = 0; i < graph->getSize(); i++) {
		for (int j = 0; j < graph->getSize(); j++) {
			if (graph->adjacent(i, j) != 0) {
				weight.insert(make_pair(graph->adjacent(i, j),make_pair(i,j)));//insert
			}
		}
	}

	ins = weight.begin();//ins is weight's begin
	int v1, v2;
	int sum = 0;
	int count = 0;
	while (ins != weight.end()) {//loop until ins is weight's end
		v1 = ins->second.first;//from
		v2 = ins->second.second;//to
		if (set.Find(v1) != set.Find(v2)) {//if two vertex's root is different
			set.Union(set.Find(v1),set.Find(v2));//call the union
			kruskal.insert(make_pair(ins->first, make_pair(v1, v2)));//insert this value
			count++;//counting
		}
		if (count == graph->getSize() - 1)//if count is done
			break;//exit
		ins++;
	}
	if (count != graph->getSize() - 1) {//if set is not spanning tree
		return false;//false
	}
	*fout << "====== Kruskal ======" << endl;
//print
	for (kru = kruskal.begin(); kru != kruskal.end(); kru++) {//loop for print
		*fout << kru->first << " ";
		sum = sum + kru->first;//calculate the sum
	}
	*fout << endl << sum << endl << "=====================" << endl << endl;//print the sum
	return true;//true return
}

bool Dijkstra(Graph* graph, int baseV, ofstream* fout)//function that runs Dijkstra
{
	if (graph == NULL)//exception handling - if graph is NULL
		return false;
	if (graph->getDirected() == false || graph->getWeighted() == false)//exception handling - if graph's directed is false of graph's weighted is false
		return false;
	if (baseV > graph->getSize() || baseV < 0)//exception handling- if input baseV is negative or is greater than graph's size
		return false;
	map<int, int> *m = new map<int,int>[graph->getSize()];//dynamic allocation
	for (int i = 0; i < graph->getSize(); i++)//initialize
		m[0][i] = 0;//to 0
	int stand = baseV;
	int cnt = 0;
	while(cnt!=(graph->getSize()-1)) {//loop until count is size
		stand = stand%graph->getSize();//set the stand
		graph->getIncidentEdges(stand, m);//call the getIncident function
		cnt++;//counting
		stand++;//stand +
	}
	*fout << "====== Dijkstra ======" << endl << baseV << endl;
//print
	for (int i = 0; i < graph->getSize(); i++) {
		if (i == baseV) {//if self, don't print
			continue;
		}
		if (m[i].empty() == true) {//if m array is empty
			*fout << "[" << i << "] X" << endl;//x print
		}
		else {// not empty
			int j = i;
			*fout << "[" << i << "] ";
			while (j!=baseV) {//until j is baseV
				*fout << m[j].begin()->second << " ";//vertex
				j = m[j].begin()->second;//next vertex
			}
			*fout << " ("<<m[i].begin()->first<<")" << endl;//cost
		}
	}
	*fout << "=====================" << endl << endl;
	delete[] m;
	return true;//true
}
