#ifndef __HEAP_H_
#define __HEAP_H_
#include <ostream>
#define HEAP_LENGTH 1024
class heap
{
    friend std::ostream& operator<<(std::ostream&, const heap&);
public:
	heap();
	heap(int a[], int n);
	heap(const heap&);
	heap& operator=(const heap&);
	~heap();
	bool insert(int);
	bool pop(int&);
private:
	int m_length;
	int m_array[HEAP_LENGTH];
};
#endif

