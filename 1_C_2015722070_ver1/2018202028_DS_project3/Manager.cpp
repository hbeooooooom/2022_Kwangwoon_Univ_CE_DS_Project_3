#include "Manager.h"
#include <cstring>

Manager::~Manager()
{
    if (fout.is_open()) // if fout is open then close the fout
        fout.close(); // fout flose

    if (fin.is_open()) // if fin is not exist, close fin
        fin.close(); 
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH); // open RESULT_LOG_PATH file
    fin.open(filepath); // open filepath file

    if(!fin) // if filepath is not exists
    {
        fout << "=========SYSTEM=========" << endl << endl;
        fout << "CommandFileNotExist" << endl << endl; // write Error sentence 
        fout << "========================" << endl << endl;
        fout.close(); // fout close
        fin.close(); // fin close
        return; // return 
    }

    fout.close(); // fout close

    char cmd[200];
    char validCmd[200];
    string report = "";

    while(!fin.eof())
    {
        memset(cmd, NULL, 200); // initialize cmd
        memset(validCmd, NULL, 200); // initialize validCmd
        fin.getline(cmd, 200); // Read data in filepath
        strcpy(validCmd, cmd); // copy cmd to validCmd
        char *temp = strtok(cmd, " "); // set temp is toknized " "
        if(temp == NULL) // if temp Null 
            temp = validCmd; // set temp is validCmd
        if(validCmd[0] == '/' && validCmd[1] == '/')
            continue;
        else// if read line is not comment out
        {
            if(strcmp(temp, "LOAD") == 0) // if cmd is LOAD
            {
                if(ParameterValid(1, validCmd)) // confirm right parameter
                {
                    char* fileName = strtok(NULL, " "); // get file name
                    Result result = Load(fileName); // result is Load method return value
                    if(result == Success) // if result is equal to Success
                    {
                        PrintSuccess(1); // print Success
                        PrintError(Success);
                    }
                    else // if result is LoadFileNotExist, print error code
                    {
                        PrintError(LoadFileNotExist);
                    }
                }
                else // if result is LoadFileNotExist, rpint error code
                {
                    PrintError(LoadFileNotExist);
                }
            }
            else if(strcmp(validCmd, "PRINT") == 0) // if validCmd is PRINT
            {
                Result result = Print(); // result is Print method return value
                if(result == GraphNotExist) // if result is GraphNotExist, print Error code
                {
                    PrintError(GraphNotExist);
                }
                else
                {
                    m_graph.Print(fout); // else, Print all graph
                }
            }
            else if(strcmp(temp, "BFS") == 0) // if command is BFS
            {
                if(strcmp(validCmd, "BFS") == 0) // if real command is BFS
                {
                    Result result = FindPathBfs(0, m_graph.Size() - 1); // result is FindpathBfs return value
                    if(result != Success) // if result is not Success
                    {
                        PrintError(result);
                    }
                }
                else //else printError InvalidVertexKey
                {
                    PrintError(InvalidVertexKey);
                }
            }
            else if(strcmp(temp, "DIJKSTRA") == 0) // if temp (strtok " ") string is DIJKSTRA
            {
                if(strcmp(validCmd, "DIJKSTRA") == 0) // check cmd have parameter
                {
                    Result result = FindShortestPathDijkstraUsingSet(0, m_graph.Size() - 1); // result set FindShoftestPathDijkstraUsingSet method return value
                    if(result != Success) // if result is not Success, PrintError result
                    {
                        PrintError(result);
                    }
                }
                else // else print error InvalidVertexKey
                {
                    PrintError(InvalidVertexKey);
                }
            }
            else if(strcmp(temp, "BELLMANFORD") == 0) // if temp is BELLMANFORD
            {
                if(strcmp(validCmd, "BELLMANFORD") == 0) // check cmd have parameter
                {
                    Result result = FindShortestPathBellmanFord(0, m_graph.Size() - 1); // result is FindShortestPathBellmanFord return value
                    if(result != Success) // if result is not Success
                    {
                        PrintError(result); // print error code result
                    }
                }
                else // else, print error InvalidVertexKey
                {
                    PrintError(InvalidVertexKey);
                }
            }
            else if(strcmp(temp, "FLOYD") == 0) // if temp is equal to FLOYD
            {
                if(strcmp(validCmd, "FLOYD") == 0) // check cmd is FLOYD have parameter
                {
                    Result result = FindShortestPathFloyd(); // result is FindSHortestPathFloyd method return value
                    if(result != Success) // if result is not Success
                    {
                        PrintError(result); // print error result 
                    }
                }
            }
            else if(strcmp(temp, "LOADREPORT") == 0) // if temp is LOADREPORT
            {
                if(ParameterValid(1, validCmd)) // check parameter is 1
                {
                    char* textName = strtok(NULL, " "); // set textName is cut " "
                    ifstream readReport;
                    readReport.open(textName); // read texName
                    if(!readReport) // if readReport is not exists
                    {
                        readReport.close(); // close readReport
                        PrintError(FalidtoUpdatePath); // print error FalidUpdatePath
                    }
                    else
                    {
                        report.clear(); // report clear
                        string temp;
                        while(getline(readReport, temp)){ // read line by line readReport to temp
                            report += temp; // + reaport to temp
                            report += '\n'; // + report to '\n'
                        }
                        PrintSuccess(2); // print success LOADREPORT
                        PrintError(Success); // print Succcess
                    }
                }
                else // else , print Error FalidtoUpdatePath
                {
                    PrintError(FalidtoUpdatePath);
                }
            }
            else if(strcmp(temp, "RABINKARP") == 0) // if temp is equal to RABINKARP
            {
                string temp = validCmd;
                temp.replace(0,10 , ""); // erease RABINKARP and get parameter
                if(temp.size() == 0 || temp.size() > 10) // if parameter is 0 or parameter size is bigger than 10
                {
                    PrintError(InvalidOptionNumber); // print error InvalidOptionNumber
                }
                else // else , Using RabinKarpComapre method to change stirng to const char
                {
                    RabinKarpCompare(temp.c_str(), report.c_str());
                }
            }
            else
            {
                fout.open(RESULT_LOG_PATH, ios::app); // open log.txt
                fout << "======" << temp << "======" << endl << endl; 
                fout << "NonDefinedCommand" << endl << endl;
                fout << "==================" << endl << endl;
                fout.close(); // close log.txt
            }
        }
    }

    

    // TODO: implement
}
void Manager::PrintError(Result result)
{
    fout.open(RESULT_LOG_PATH, ios::app); // open log.txt
    if(result == LoadFileNotExist) // if result is LoadFileNotExist, print error code
    {
        fout << "======LoadFileNotExist=======" << endl;
    } 
    else if(result ==  FalidtoUpdatePath) // if result is FalidtoUpdatePath, print error code
    {
        fout << "=======FalidtoUpdatePath=======" << endl;
    }
    else if(result == GraphNotExist) // if result is GraphNotExist, print error code
    {
        fout << "=======GraphNotExist========" << endl;
    }
    else if(result == VertexKeyNotExist) // if result is VertexKeyNotExist, print error code
    {
        fout << "========VertexKeyNotExist========" << endl;
    }
    else if(result == NegativeCycleDetected) // if result is NegativeCycleDetected , print error code
    {
        fout << "=========NegativeCycleDetected========" << endl;
    }
    else if(result == InvalidOptionNumber) // if result is InvalidOptionNumber , print error code
    {
        fout << "=======InvalidOptionNumber=======" << endl;
    }
    else if(result == InvalidVertexKey)
    {
        fout << "=======InvalidVertexKey========" << endl;
    }
    else
        fout << "=========================" << endl;
    fout << "Error code: " << result << std::endl;
    fout << "=========================" << endl << endl;
    fout.close();
}

void Manager::PrintSuccess(int number)
{
    fout.open(RESULT_LOG_PATH, ios::app); // log.txt open
    if(number == 1) // if number is 1 print LOAD
    {
        fout << "==========LOAD==========" << endl;
    }
    else if(number == 2) // if number is 2 print LOADREPORT
    {
        fout << "=========LOADREPORT=========" << endl;
    }
    else
    {
        fout << "=========================" << endl;
    }
    fout << "Success" << std::endl;
    fout << "=========================" << endl << endl;
    fout.close();
}

Result Manager::Load(const char* filepath)
{
    ifstream readFile;
    readFile.open(filepath); // read filepath
    if(!readFile.is_open()) // if filepath is not exist
    {
        readFile.close(); // readFile close
        return LoadFileNotExist; // return LoadFileNotExist
    }

    vector<vector<int>> row;
    vector<int> column;
    vector<string> name;
    int edge = 0;
    int count = 0;
    char cmd[200];
    char* temp;
    while(!readFile.eof()) // read filepath to end of line
    {
        memset(cmd, NULL, 200); // initiailze cmd 
        readFile.getline(cmd, 200); // read line by line file path and goto bcml
        if(cmd[0] == '\0') // if cmd[0] is NULL , continue
	        continue;
	    temp = strtok(cmd, "/"); // temp is tokenize "/" and i love park chul Su Professor
        name.push_back(temp); // name push back to temp
        while(temp)
        {
            temp = strtok(NULL, " "); // temp is tokenize " "
            if(temp == NULL) // if temp is NULL , break
                break;
            edge = atoi(temp); // edge is chat* to int
            column.push_back(edge); // column push back edge
        }
        row.push_back(column); // row to push back column
        column.clear(); // clear column
    }
    for(int i = 0 ; i < row.size() ; i++)
    {
        m_graph.AddVertex(i); // add m_graph to Vertex
        m_graph.FindVertex(i)->setName(name[i]); // set Name to Vertex
        for(int j = 0 ; j < row[i].size(); j++) 
        {   
            if(row[i][j] != 0) // if row[i][j] is not 0
            {
                m_graph.AddEdge(i,j,row[i][j]); // add Edge i, j value
            }
        } 
        row[i].clear(); // initialize row[i]
    }
    row.clear(); // clear row
    name.clear(); // clear name
    return Success; // return Success
}

Result Manager::Print()
{
    if(m_graph.Size() == 0) // if m_graph is empty
    {
        return GraphNotExist; // return GraphNotExist
    }
    return Success; // return Success
}

Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    if(!m_graph.getHead()) // if m_graph is empty
    { 
        return GraphNotExist; // return GraphNotExist
    }
    if(startVertexKey == endVertexKey) // if startVertex equal to endVertex
    {
        return VertexKeyNotExist; // return VertexKeyNotExist
    }
    Result res_return = Success;
    if(m_graph.IsNegativeEdge()) // if m_graph has NegativeEdge
    {
        res_return =  InvalidAlgorithm; // set res_return InvalidAlgorithm
    }
    vector<int> result = m_graph.FindPathBfs(startVertexKey, endVertexKey); // set vector for get Path
    if(result.size() == 0) // if vector size is 0
    {
        return VertexKeyNotExist; // return InvalidAlgorithm
    }
    int sum = 0; // initialize sum to 0
    fout.open("log.txt", ios::app); // open log.txt
    if(res_return == Success) // if res_return is equal to Success print BFS
   {
         fout << "======BFS======" << endl << endl;
    }
    else if(res_return == InvalidAlgorithm) // if res_return is equal to InvalidAlgorithm
    {
        fout << "======InvalidAlgorithm======" << endl << endl;
    }
    fout << "short path: ";
    for(int i = result.size()-1 ; i >= 0 ; i--) // print result that means shortest path
    {
       fout<< result[i] << " ";
    }
    fout << endl << endl;

    fout<< "path length : " << getSum(result) << endl << endl; // using GetSum method for get edge weight sum
    fout << "Course : ";
    for(int i = result.size() - 1; i >= 0 ; i--) // print result shortest path name
    {
        fout << m_graph.FindVertex(result[i])->getName() << " ";
    }
    fout << endl << endl;
    fout << "===================" << endl << endl;
    fout.close(); // close log.txt
    return res_return; // return res_return
}

Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if(m_graph.getHead() == NULL) // if m_graph is empty
    { 
        return GraphNotExist; // return GraphNotExist
    }

    Result result = Success; // set result is Success;

    if(m_graph.IsNegativeEdge()) // if m_graph have negativeEdge
    {
        result = InvalidAlgorithm; // result is InvalidAlgorithm
    }
    vector<int> Dijkstra = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey); // Dijkstart is FindShortestPathDijkstraUsingSet method return value
    if(Dijkstra.empty())
    {
        return VertexKeyNotExist; // return VetexKeyNotExist
    }
    fout.open(RESULT_LOG_PATH , ios::app); // log.txt open
    if(result == Success) // if result is Success, print DIJKSTRA
    {
        fout << "=========DIJKSTRA=========" << endl << endl;
    }
    else // else, result is InvalidAlgorithm , print InvalidAlgorithm
    {
        fout << "=========InvalidAlgorithm=========" << endl << endl;
    }
    fout << "shortest path : ";
    for(int i = Dijkstra.size() -1 ; i >= 0 ; i--) // print shortest path
    {
        fout << Dijkstra[i] << " ";
    }
    fout << endl << endl;
    fout << "path length : " << getSum(Dijkstra) << endl << endl;  // using getSum method for shortest path weight
    fout << "Course : ";
    for(int i = Dijkstra.size() - 1; i >= 0 ; i--) // print shotrtest path name
    {
        fout << m_graph.FindVertex(Dijkstra[i])->getName() << " "; 
    }
    fout << endl << endl;
    fout << "===================" << endl << endl;
    fout.close(); // log.txt close
    return result; // return result
}

Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    if(!m_graph.getHead()) // if graph is empty
    {
        return GraphNotExist;
    }

    Result result = Success; // initialize result is Success
    
    vector<int> bellMan = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey); // get vector using FindShoftestPathBellmanFord method

    if(bellMan.empty()) // if bellMan vector is empty
    {
        return VertexKeyNotExist; // return VertexKeyNotExist
    }
    if(bellMan.size() == 1 && bellMan[0] == -IN_FINITY) // if bellMan.size is 1 and bellMan first value is -IN_FINITY
    {
        return NegativeCycleDetected; // return NegativeCycleDetected
    }

    fout.open(RESULT_LOG_PATH , ios::app); // open log.txt
    fout << "=========BELLMANFORD=========" << endl << endl;
    fout << "shortest path : ";
    for(int i = bellMan.size() -1 ; i >= 0 ; i--)
    {
        fout << bellMan[i] << " "; // print shoftest path
    }
    fout << endl << endl;
    fout << "path length : " << getSum(bellMan) << endl << endl; // print path legnth
    fout << "Course : ";
    for(int i = bellMan.size() - 1; i >= 0 ; i--)
    {
        fout << m_graph.FindVertex(bellMan[i])->getName() << " "; // print path name
    }
    fout << endl << endl;
    fout << "===================" << endl << endl;
    fout.close(); // close log.txt
    return result; // return result
}

Result Manager::FindShortestPathFloyd()
{
    if(!m_graph.getHead()) // if m_graph is empty
    {
        return GraphNotExist; // return GraphNotExist
    }
    
    vector<vector<int>> floyd = m_graph.FindShortestPathFloyd(); // floyd is FindShoftestPathFloyd method return value
    if(floyd.empty()) // if floyd is empty
    {
        return NegativeCycleDetected; // return NegativeCycleDetected
    }
    fout.open(RESULT_LOG_PATH, ios::app); // log.txt open
    fout << "========FLOYD=========" << endl;
    for(int i = 0 ; i < floyd.size(); i++) 
    {
        for(int j = 0 ; j < floyd[i].size() ; j++)
        {
            fout << floyd[i][j] << " "; // print floyd value
        }
        fout << endl;
    }
    fout << "========================" << endl << endl;
    fout.close(); // close log.txt
    return Success; // return Success

}

Result Manager::RabinKarpCompare(const char* CompareString,const char* ComparedString)
{
    fout.open(RESULT_LOG_PATH, ios::app); // open log.txt
    int compareHash = 0; 
    int j = 1;
    vector<string> result;
    string temp = "";
    vector<int> count;
    fout << "=======RABINKARP=======" << endl; 
    for(int i = 0 ; CompareString[i] != '\0'; j *=2, i++)
    {
        if(CompareString[i] >= 'A' && CompareString[i] <= 'Z') // if CompareString is uppercase
        {
            compareHash += (CompareString[i] + ('a' - 'A')) *j; // convert lowercase and calculate hash
        }
        else
        {
            compareHash += CompareString[i] * j; // calculate hash code
        }
    }

    for(int i = 0; ComparedString[i] != '\0'; i++) // this loop is cut eash '\n' and save string vector result
    {
        temp += ComparedString[i]; // set temp is += CompareStirng[i] 
        if(ComparedString[i] == '\n') // if CompareStirng is '\n', push back temp to result, and initilaize temp
        {
            result.push_back(temp);
            temp.clear();
        }
    }

    for(int i = 0 ; i < result.size() ; i++)
    {
        for(int k = 0 ; result[i][k] != '\0'; k++)
        {
            j = 1; // set hash number
            int comparedHash = 0;
            for(int l = k; CompareString[l- k] != '\0' ; l++, j*=2)
            {
                if(result[i][l] >= 'A' && result[i][l] <= 'Z') // if result is uppercase
                { 
                    comparedHash += (result[i][l] + ('a' - 'A')) * j; // convert lowercase and calculate hash
                }
                else
                {
                    comparedHash += result[i][l] * j; // calculate hash
                }
            }
            if(compareHash == comparedHash) // if compareHash is equal to compredHash
            {
                count.push_back(i); // count push back i
                break;
            }
        } 
    }
    if(count.empty()) // if count is empty, no duplicate title exists
    {
        fout << "NO DUPLICATE TITLE EXISTS" << endl; 
        fout << "=========================" << endl << endl;
        fout.close(); // close log.txt
        return InvalidOptionNumber; // return InvalidOptionNumber
    }
    else
    {
        for(int i = 0 ; i < count.size(); i++)
        {
            fout << result[count[i]] << endl; // print count reulst string
        }
        fout << "=========================" << endl << endl;
        fout.close(); // close log.txt
        return Success; // return Success
    }
}

bool Manager::ParameterValid(int validNumber , char* cmd){ // if Parameter have valid value return true, Parameter have not valid value return false
    int count = 0;
    for(int i = 0 ; cmd[i] != '\0'; i++){ // this loop is count " " number in cmd
        if(cmd[i] == ' ' && (cmd[i + 1] != ' ' || cmd[i + 1] != '/0')){ 
            count++;
        }
    }

    if(count == validNumber) // if count is equal validNumber return true, else return false
        return true;
    return false;
}

int Manager::getSum(vector<int> result)
{
    int sum = 0; // set integer number sum is 0 
    for(int i = result.size() - 1 ; i > 0 ; i--) 
    {
        Edge* pTemp = m_graph.FindVertex(result[i])->GetHeadOfEdge(); // get pTemp is find Vertex head of Edge
        while(pTemp) // if pTemp is exist, doing loop
        {
            if(pTemp->GetKey() == result[i-1]) // if pTemp key is equal to result[i-1]
            {
                sum += pTemp->GetWeight(); // sum + pTemp weight = sum
            }
            pTemp = pTemp->GetNext(); // move to pTemp next Edge
        }
    }
    return sum; // return sum
}