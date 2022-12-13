#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>
#include <queue>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log
    const char* ERROR_LOG_PATH = "log.txt";

    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log
    std::ofstream ferr;
    
    // graph instance to manage the vertics.
    Graph *m_graph;

    // srings to compare by Rabin-Karp Algorithms
    vector<string> strings;
    vector<string> founded;

public:
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result);

private:
    Result Load(const char* filepath);
    Result Print();
    Result FindPathBfs();
    Result FindShortestPathDijkstraUsingSet();
    Result FindShortestPathBellmanFord();
    Result FindShortestPathFloyd();
    Result RabinKarpCompare(string CompareString, string ComparedString);
};

#endif
