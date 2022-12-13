#include "Vertex.h"
using namespace std;

Vertex::Vertex()
{
    m_key = 0;
    m_size = 0;
    m_pEHead = NULL;
    m_pNext = NULL;
}

Vertex::Vertex(int key)
{

}

Vertex::~Vertex()
{

}

void Vertex::SetKey(int key)
{
    m_key = key;
}

void Vertex::SetNext(Vertex* pNext)
{
    m_pNext = pNext;
}

int Vertex::GetKey() const
{
    return m_key;
}

Vertex* Vertex::GetNext() const
{
    return m_pNext;
}

int Vertex::Size() const
{
    return m_size;
}


void Vertex::AddEdge(int edgeKey, int weight)
{
    Vertex *v = new Vertex;
    Edge *e = new Edge;
    e->SetKey(edgeKey);
    e->SetWeight(weight);

    if(m_pEHead == NULL){
        m_pEHead = e;
    }
    else{
        Edge *temp = m_pEHead;
        while(temp->GetNext() != NULL)
            temp = temp->GetNext();
        temp->SetNext(e);
    }
    m_size++;
}

Edge* Vertex::GetHeadOfEdge() const
{
    return m_pEHead;
}

void Vertex::Clear()
{
    
}