#ifndef _VERTEXSET_H_
#define _VERTEXSET_H_

#include <iostream>//vertexSet.h includes iostream header file

class vertexSet//declare and define the vertexSet class
{
private://declare the private members

	int* m_Parent;//vertex's parent(array)
	int m_Size;//graph's size
public://declare and define the public members
	vertexSet(int size) {//constructor of vertexSet class
		m_Size = size;
		m_Parent = new int[m_Size];//dynamic allocation
		for (int i = 0; i < m_Size; i++)//initialize
			m_Parent[i] = -1;//m_Parent array's value -1(initialize)
	}
	~vertexSet() {//destructor of vertexSet class
		delete m_Parent;//dynamic deallocation
	}

	int Find(int ver) {//function that find ver(input)'sthe root
		while (m_Parent[ver] != -1) {//if m_Parent is initialize value, exit the loop
			ver = m_Parent[ver];//ver = ver's parent
		}
		return ver;//ver return
	}

	void Union(int v1, int v2) {//function that add the two root
		m_Parent[v1] = v2;//v1's parent is v2
	}
};//end
#endif
