#include "Edge.h"

Edge::Edge()
{
    m_key = 0; // initialize m_key 
    m_weight = 0; // initialize m_weight
    m_pNext = NULL; // initialize m_pNext
}

	/// copy constructor
Edge::Edge(int key, int weight)
{
    m_key = key; // initilize m_key to key
    m_weight = weight; // initialize m_wegith to weight
    m_pNext = NULL; // initialize m_pNext
}

   /// set the next pointer of this edge
void Edge::SetNext(Edge* pNext)
{
    this->m_pNext = pNext; // change m_pNext value to pNext 
}

   /// get the key of this edge
int Edge::GetKey() const
{
    return m_key; // return m_key value
}

/// get the weight of this edge
int Edge::GetWeight() const
{
    return m_weight; // resturn m_weight value
}

/// get the next pointer of this edge
Edge* Edge::GetNext() const
{
    return m_pNext; // return m_pNext value
}