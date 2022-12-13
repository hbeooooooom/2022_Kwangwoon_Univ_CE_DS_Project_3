#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"

class Vertex
{
private:
    int m_key;          // the key of this vertex
    int m_size;         // the number of the edges from this vertex to others
    Edge* m_pEHead;     // the head pointer for the linked list of the edges
    Vertex* m_pNext;    // the next pointer for the linked list of the vertics

public:
    Vertex();           // constructor
    Vertex(int key);    // copy of constructor
    ~Vertex();          // destructor
    void SetKey(int key);           // set key of this vertex
    void SetNext(Vertex* pNext);    // set the next pointer of this vertex
    int GetKey() const;             // get the key of this vertex
    Vertex* GetNext() const;        // get the next pointer of this vertex
    int Size() const;               // get the number of the edges
    void AddEdge(int edgeKey, int weight);  // add edge with edgeNum at the end of the linked list for the edges / param edgeKey: the key of the vertex for the edge, param weight: the weight of the edge
    Edge* GetHeadOfEdge() const;    // get the head pointer of the edge
    void Clear();                   // memory free for edges
};

#endif
