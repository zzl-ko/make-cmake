#include <iostream>
#include "hello.hxx"
#include "module.h"
// 如下“修正包含头文件路径的问题”之后，包含子目录中的头文件不用写全路径
#include "calc.h"
#include "utility.h"

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
	cout<<"include header's micro is " << TEST_HEADER_INCLUDE <<endl;
	
	return 0;
}
#endif