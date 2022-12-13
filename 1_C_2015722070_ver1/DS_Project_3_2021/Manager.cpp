#include "Manager.h"
#include <cstring>

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    ifstream fin;
    fin.open(filepath);
    fout.open(RESULT_LOG_PATH, ios::app);
    ferr.open(ERROR_LOG_PATH, ios::app);
    
    if(!fin){
        ferr << "File Open Error" << endl;
        return;
    }
    
    char cmd[32];
    while(!fin.eof()){
        fin.getline(cmd, 100);
        char* command = strtok(cmd, " ");
        if(command == NULL) continue;

        if(strcmp(command, "LOAD") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL)
                PrintError(Load(temp));
            else
                PrintError(LoadFileNotExist);
        }
        else if(strcmp(command, "LOADREPORT") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL){
                PrintError(Load(temp));
            }
            else
                PrintError(FailedtoUpdatePath);
        }
        else if(strcmp(command, "PRINT") == 0){
            Result r = Print();
            if(r != 0)
                PrintError(r);
        }
        else if(strcmp(command, "BFS") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL)
                PrintError(InvalidVertexKey);
            else{
                Result r = FindPathBfs();
                if(r != 0 && r != 203)
                    PrintError(r);
            }
        }
        else if(strcmp(command, "DIJKSTRA") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL)
                PrintError(InvalidVertexKey);
            else{
                Result r = FindShortestPathDijkstraUsingSet();
                if(r != 0 && r != 203)
                    PrintError(r);
            }
        }
        else if(strcmp(command, "BELLMANFORD") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL)
                PrintError(InvalidVertexKey);
            else{
               Result r = FindShortestPathBellmanFord();
                if(r != 0)
                    PrintError(r); 
            }
        }
        else if(strcmp(command, "FLOYD") == 0){
            char* temp = strtok(NULL, "");
            if(temp != NULL)
                PrintError(InvalidVertexKey);
            else{
                Result r = FindShortestPathFloyd();
                if(r != 0)
                    PrintError(r);
            }
        }
        else if(strcmp(command, "RABINKARP") == 0){
            char* temp = strtok(NULL, "");
            for(int i = 0; i <strings.size(); i++){
                RabinKarpCompare(temp, strings[i]);
            }

            if(founded.size() == 0){
                fout << "===================== RABINKARP =====================" << endl;
                fout << "NO DUPLICATE TITLE EXISTS" << endl;
                fout << "=====================================================" << endl << endl;
            }
            else{
                fout << "===================== RABINKARP =====================" << endl;
                fout << "DUPLICATE TITLE EXISTS" << endl;
                for(int i = 0; i < founded.size(); i++)
                    fout << founded[i] << endl;
                fout << "=====================================================" << endl << endl;
            }
            founded.clear();
        }
        else{
            PrintError(NonDefinedCommand);
        }
    }
}

void Manager::PrintError(Result result)
{
    ferr << "=====================================================" << endl;
    ferr << "Error code: " << result << endl;
    ferr << "=====================================================" << endl << endl;
}

// make a graph
Result Manager::Load(const char* filepath)
{
    ifstream file;
    file.open(filepath);
    if(!file)
        return LoadFileNotExist;

    // load mapdata.txt file
    if(strcmp(filepath, "mapdata.txt") == 0){
        m_graph = new Graph;
        char mapdata[60];
        int start = 0;
        int count = 0;

        // get the number of vertexes
        while(!file.eof()){
            file.getline(mapdata, 100);
            count++;
        }
        for(int i = 0; i < count; i++)
            m_graph->AddVertex(i);      // add vertex
        
        ifstream file2;
        file2.open(filepath);
        while(!file2.eof()){
            file2.getline(mapdata, 100);
            char* company = strtok(mapdata, "/");
            char* weight;
            for(int end = 0; weight = strtok(NULL, " "); end++){
                if(atoi(weight) != 0)
                    m_graph->AddEdge(start, end, atoi(weight)); // add edge
            }
            start += 1;
        }

        fout << "======================== LOAD =======================" << endl;
        fout << "Success" << endl;
        fout << "=====================================================" << endl;
        return Success;
    }

    // load reportdata.txt file
    else if(strcmp(filepath, "reportdata.txt") == 0){
        char reportdata[60];
        while(!file.eof()){
            file.getline(reportdata, 100);
            strings.push_back(reportdata);
        }
        
        fout << "===================== LOADREPORT ====================" << endl;
        fout << "Success" << endl;
        fout << "=====================================================" << endl;
        return Success;
    }
}

// print out the graph as matrix form
Result Manager::Print()
{
    if(m_graph->Size() == 0)
        return GraphNotExist;

    m_graph->Print(fout);
    return Success;
}

// find the path from startVertexKey to endVertexKey with BFS 
Result Manager::FindPathBfs()
{
    if(m_graph->Size() == 0)
        return GraphNotExist;

    vector<int> v = m_graph->FindPathBfs();
    if(m_graph->IsNegativeEdge() == 1){ // if negative edge exists, note
        fout << "================== InvalidAlgorithm =================" << endl;
        fout << "vertex on path: " << v.front() << endl;
        fout << "=====================================================" << endl << endl;
        return InvalidAlgorithm;
    }
    else{
        fout << "======================== BFS ========================" << endl;
        fout << "vertex on path: " << v.front() << endl;
        fout << "=====================================================" << endl << endl;
        return Success;
    }
}

// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
Result Manager::FindShortestPathDijkstraUsingSet()
{
    if(m_graph->Size() == 0)
        return GraphNotExist;

    vector<int> v = m_graph->FindShortestPathDijkstraUsingSet();
    if(m_graph->IsNegativeEdge() == 1){ // if negative edge exists, note
        fout << "================== InvalidAlgorithm =================" << endl;
        fout << "path length: " << v.front() << endl;
        fout << "=====================================================" << endl << endl;
        return InvalidAlgorithm;
    }
    else{
        fout << "===================== DIJKSTRA ======================" << endl;
        fout << "path length: " << v.front() << endl;
        fout << "=====================================================" << endl << endl;
        return Success;
    }
}

// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
Result Manager::FindShortestPathBellmanFord()
{
    if(m_graph->Size() == 0)
        return GraphNotExist;

    vector<int> v = m_graph->FindShortestPathBellmanFord();
    if(v.back() != IN_FINITY){  // check if negative cycle detected
        fout << "==================== BELLMANFORD ====================" << endl;
        fout << "path length: " << v.back() << endl;
        fout << "=====================================================" << endl << endl;
        return Success;
    }
    else
        return NegativeCycleDetected;
}

// find the shortest path from startVertexKey to endVertexKey with Floyd
Result Manager::FindShortestPathFloyd()
{
    if(m_graph->Size() == 0)
        return GraphNotExist;

    vector<vector<int>> v = m_graph->FindShortestPathFloyd();
    // check if got negative cycle
    bool isAllZero = true;
    for(int i = 0; i < m_graph->Size(); i++){
    if(v[0][i] != 0){
            isAllZero = false;
            break;
        }
    }

    if(isAllZero == false){
        fout << "======================= FLOYD =======================" << endl;
        for(int i = 0; i < m_graph->Size(); i++){
            for(int j = 0; j < m_graph->Size(); j++){
                fout << v[i][j] << " ";
            }
            fout << endl;
        }
        fout << "=====================================================" << endl << endl;
        return Success;
    }
    else
        return NegativeCycleDetected;
}

// find if compared string contains compare sting
Result Manager::RabinKarpCompare(string CompareString, string ComparedString)
{
    string pattern = CompareString; // string to find pattern
    string parent = ComparedString; // string to compare
    for(int i = 0; i < pattern.size(); i++)
        pattern[i] = tolower(pattern[i]);
    for(int i = 0; i < parent.size(); i++)
        parent[i] = tolower(parent[i]);

    int patternSize = pattern.size();
    int parentSize = parent.size();
    int patternHash = 0;
    int parentHash = 0;
    int power = 1;

    for(int i = 0; i <= parentSize - patternSize; i++){
        if(i == 0){
            for(int j = 0; j < patternSize; j++){
                parentHash = parentHash + parent[patternSize-1-j] * power;
                patternHash = patternHash + pattern[patternSize-1-j] * power;
                if(j < patternSize - 1)
                    power = power*2;
            }
        }
        else
            parentHash = 2*(parentHash-parent[i-1]*power)+parent[patternSize-1+i];

        if(parentHash == patternHash){
            bool isFind = true;
            // check if string is really overlapped
            for(int j = 0; j < patternSize; j++){
                if(parent[i+j] != pattern[j]){
                    isFind = false;
                    break;
                }
            }
            // if found pattern in compared string, push to founded vector
            if(isFind){
                founded.push_back(parent);
                return Success;
            }
        }
    }   
}
