#include <iostream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include "heap.h"

using namespace std;

static inline int left(int n)
{
	return n << 1;
}

static inline int right(int n)
{
	return (n << 1)+1;
}

static inline int parent(int n)
{
	return n >> 1;
}

static inline void xchange(int array[], int a, int b)
{
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

static void inline adjust_tree(int array[], int idx, int len)
{
	int root_idx = idx;
	while(left(root_idx) < len)
	{
		int child_min_idx = left(root_idx);
		if(right(root_idx) <len)
		{
			if(array[child_min_idx] > array[right(root_idx)])
			{
				child_min_idx = right(root_idx);
			}
		}
		if(array[root_idx] > array[child_min_idx])
		{
			xchange(array, root_idx, child_min_idx);
			root_idx = child_min_idx;
		}
		else
		{
			break;
		}		
	}
	return;
}

static void heap_create(int array[], int len)
{
	for(int i = len-1; i >=0; --i)
	{
		adjust_tree(array ,i, len);
	}
}

heap::heap():m_length(0)
{
	return;
}

heap::heap(int array[], int len):m_length(len)
{
	int length = len;
	if(length > HEAP_LENGTH)
	{
		length = HEAP_LENGTH;
	}
	memcpy(m_array, array, length*sizeof(int));
	heap_create(m_array, length);
}

heap::heap(const heap& old_heap)
{
	m_length = old_heap.m_length;
	memcpy(m_array, old_heap.m_array, m_length*sizeof(int));
}

heap::~heap()
{
    return;
}

heap& heap::operator=(const heap& rhs)
{
    if(this != &rhs)
    {
        m_length = rhs.m_length;
        memcpy(m_array, rhs.m_array, m_length*sizeof(int));
        cout << "copy heap" << endl;
    }
    return *this;
}

ostream& operator<<(ostream& out, const heap& hp)
{
    out<<"length:"<<hp.m_length << endl;
    for(int i = 0; i < hp.m_length; ++i)
    {
        out << hp.m_array[i] << endl;
    }
    return out;
}

bool heap::insert(int d)
{
    if(m_length >= HEAP_LENGTH)
    {
        return false;
    }
    m_array[m_length++] = d;
    int start_idx = m_length-1;
    while(start_idx > 0)
    {
        if(m_array[parent(start_idx)] > m_array[start_idx])
        {
            xchange(m_array, parent(start_idx), start_idx);
            start_idx = parent(start_idx);
        }
        else
        {
            break;
        }
    }
    return true;
}

bool heap::pop(int& out_n)
{
    bool ret = false;
    if(m_length > 0)
    {
        out_n = m_array[0];
        m_array[0] = m_array[--m_length];
        adjust_tree(m_array, 0, m_length);
        ret = true;
    }
    return ret;
}

int main(int argc, char* argv[])
{
    heap p;
    srand((unsigned)time(NULL));
    for(int i = 0; i < 100; i ++)
    {
        p.insert(rand()%2000); 
    }
    heap s(p);
    int d;
    while(s.pop(d))
    {
        cout << d << endl; 
    }
    return 0;
}
