#include "hello.hxx"

void CHello::say_hello()
{
	setIdx(5);
	cout << "idx[" << getIdx() << "]: Hello, World!" << endl;
}

void hello()
{
	CHello hi;

	hi.say_hello();

	cout << "TEST_HEADER_INCLUDE: " << TEST_HEADER_INCLUDE << endl;
}
