#ifndef _VERTEXSET_H_
#define _VERTEXSET_H_

#include <iostream>

class vertexSet
{
private:
	int* m_Parent;
	int m_Size;

public:
	vertexSet(int size)
	{
		m_Size = size;
		m_Parent = new int[m_Size]; // dynamic allocation
		for (int i = 0; i < m_Size; i++)
			m_Parent[i] = -1;
	}
	~vertexSet()
	{
		delete[] m_Parent;
	}

	int Find(int ver) // finding parent of ver
	{
		return m_Parent[ver];
	}

	void Union(int v1, int v2) // set parent of v2 to v1
	{
		m_Parent[v2] = v1;
	}
};
#endif
