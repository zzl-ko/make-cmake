#include "module.h"

#ifndef KERNEL_MODULE
#include <stdio.h>
#include <pthread.h>

void *thread_handlr(void *arg)
{
	printf("This thread handler function\n");
	return NULL;
}

void module()
{
	int ret = 0;
    pthread_t tid;

    ret = pthread_create(&tid, NULL, thread_handlr, NULL);
    if(0 != ret)
    {
        printf("pthread_create error\n");
        return;
    }
    printf("Thread created succ: tid[%ld],ret[%d]\n", tid, ret);
    //pthread_detach(tid);
    pthread_join(tid, NULL);

	printf("This should be a module of kernel!\n");
}

#else // KERNEL_MODULE

#include <linux/module.h>
#include <linux/init.h>

#include "calc/calc.h"
#include "utility/utility.h"

/* 设备驱动模块加载函数 */
static int __init demo_init(void)
{
	int  num = 89757;
	char str[6] = "";

	printk("[kernel space]: demo_init\n");
	my_itoa(num, str);
	printk("[kernel space]: num[%d] -> str[%s]\n", num, str);
	printk("[kernel space]: 10+2=%d\n", add(10,2) );
	printk("[kernel space]: 10-2=%d\n", sub(10,2) );
	printk("[kernel space]: 10*2=%d\n", mul(10,2) );
	printk("[kernel space]: 10/2=%d\n", div(10,2) );
	
	return 0;
}
 
/* 模块卸载函数 */
static void __exit demo_exit(void)
{
	printk("[kernel space]: demo_exit\n");
	printk("[kernel space]: include header's micro is %d\n", TEST_HEADER_INCLUDE);
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Great Hero");
MODULE_VERSION("v1.0.0");
MODULE_DESCRIPTION("demo");
MODULE_ALIAS("demo");
#endif // end KERNEL_MODULE
