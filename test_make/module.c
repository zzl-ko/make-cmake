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
