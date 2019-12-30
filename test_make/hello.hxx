#ifndef HELLO_H
#define HELLO_H

#include "module.h"
#include <iostream>
using namespace std;

class CHello
{
public:
	CHello()
	{
		cout << "Hello, I'm coming!" << endl;
		idx = 0;
	}
	~CHello()
	{
		cout << "Bye, I'll leaving!" << endl;
	}

	void say_hello();

	int getIdx(void)
	{
		return idx;
	}
	void setIdx(int idx)
	{
		this->idx = idx;
	}
	
private:
	int idx;
};

extern void hello();

#endif // end HELLO_H
