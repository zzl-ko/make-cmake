#include <iostream>
#include "hello.hxx"
#include "module.h"
#include "calc/calc.h"
#include "utility/utility.h"

using namespace std;

#if 1
int main()
{	
	cout<< "Test program build by Makefile:\n"<<endl;

	#ifdef WIN32
	cout << "Has Define WIN32" << endl;
	#endif
	
	#ifdef UNIX
	cout << "Has Define UNIX" << endl;
	#endif
	
	#ifndef MAC
	cout << "Has UnDefine MAC" << endl;
	#endif
	
	#ifdef DEBUG
	cout << "Has Define DEBUG" << endl;
	#endif

	hello();
	module();
	cout<<"10+2"<<"="<<add(10,2)<<endl;
	cout<<"10-2"<<"="<<sub(10,2)<<endl;
	cout<<"10*2"<<"="<<mul(10,2)<<endl;
	cout<<"10/2"<<"="<<div(10,2)<<endl;
	int  num = 89757;
	char str[6] = "";
	my_itoa(num, str);
	cout<<"num["<<num<<"] -> str["<<str<<"]"<<endl;
	
	return 0;
}
#endif