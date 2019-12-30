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

/* 
动态或静态库的链接使用说明：
1. 参见Makefile, 修改COM_TYPE变量可编译生成动态库libdemo.so或静态库libdemo.a
2. 使用如下命令链接库生成可执行程序
g++ main.cpp -L.bin/ -ldemo -o a.out
3. 执行 ./a.out (如果是链接的动态库，这样执行通常会报如下错误)
“error while loading shared libraries: libdemo.so: cannot open shared object file: No such file or directory”
有三种解决办法，如下：
1）指定链接库路径即可: export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./bin:.
2）保证只有静态库存在（当动态库或静态库同时存在时，使用上述方式将默认链接动态库，程序运行时才会去加载）
3）强制链接静态库: g++ main.cpp -L.bin/ -l:libdemo.a -o b.out
注：相比于动态链接，使用静态链接方式编译出的程序体积将更大
参考：（同时有.so和.a)让gcc强制链接静态库
https://blog.csdn.net/youqika/article/details/54617525
 */
 