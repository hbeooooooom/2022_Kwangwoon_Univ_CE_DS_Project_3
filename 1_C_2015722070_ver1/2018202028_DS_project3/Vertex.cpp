#include "Vertex.h"

Vertex::Vertex()
{
    m_key = 0; // initialize m_key
    m_size = 0; // initialize m_size
    m_pEHead = NULL; // initialize m_pEHEad
    m_pNext = NULL; // initialize m_pNext
    name = ""; // initialize name
}

Vertex::Vertex(int key)
{
    m_key = key; // initilize m_key to key
    m_size = 0; // initialize m_size
    m_pEHead = NULL; // initilize m_pEHead 
    m_pNext = NULL; // initialize m_pNext
    name = ""; // initialize name
}

Vertex::~Vertex()
{
    m_key = 0;
    m_size = 0;
    m_pEHead = 0;
    m_pNext = NULL;
    name.clear();
}

void Vertex::SetNext(Vertex* pNext)
{
    m_pNext = pNext; // change value m_pNext to pNext
}

int Vertex::GetKey() const
{ 
    return m_key; // return m_key value
}

Vertex* Vertex::GetNext() const
{
    return m_pNext; // return m_pNext value
}

int Vertex::Size() const
{
    return m_size; // retrun m_size value
}

void Vertex::AddEdge(int edgeKey, int weight)
{
    if(!m_pEHead) // if m_pEHaed is empty
    {
        Edge* pNew = new Edge(edgeKey, weight); // allocate new Edge node
        m_pEHead = pNew; // set m_pEHead
    }
    else
    {
        Edge* pHead = m_pEHead; // pHead is m_pEHead
        while(pHead->GetNext()) // move pHead to end
        {
            pHead = pHead->GetNext(); // move to pHead next
        }
        Edge* pNew = new Edge(edgeKey, weight); // allocate new Edge node
        pHead->SetNext(pNew); // set pHead next is new allocate Edge node
    }
}

Edge* Vertex::GetHeadOfEdge() const
{
    return m_pEHead; // return m_pEHEad value
}

void Vertex::Clear()
{
    Edge* pTemp = GetHeadOfEdge(); // get pTemp head of edge
    if(pTemp)
    {
        Edge* pNext = pTemp->GetNext(); // pNext is pTemp next
        while(pNext) 
        {
            delete pTemp; //deallocate pTemp
            pTemp = pNext; // pTemp is pNext
            pNext = pNext->GetNext(); // pNext move next
        }
        delete pTemp; // deallocate pTemp
    }
}

void Vertex::setName(std::string name)
{
    this->name = name; // chage value name to parameter name
}

std::string Vertex::getName()
{
    return name; // return name
}