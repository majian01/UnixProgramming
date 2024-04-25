#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "mytbf.h"

#define THRNUM     4
#define CPS        1
#define BURST      5 
#define BUFSIZE    1024

static pthread_mutex_t mtx[THRNUM];

struct bucket_char_st
{
    struct mytbf_st* tbf;
    int num;
};

static int next(int n)
{
    if (n + 1 == THRNUM)
    {
        return 0;
    }
    return n + 1;
}

static void* thread_func(void* arg)
{
    struct bucket_char_st* tbf_num = (struct bucket_char_st*)arg;
    int c = 'a' + tbf_num->num ;
    int n = tbf_num->num;
    int size; //写入数据大小
    while (1)
    {
        pthread_mutex_lock(mtx+n);
        size = mytbf_fetchtoken(tbf_num->tbf, BUFSIZE);
        //这里不需要returntoken了
        write(1, &c, size);
        pthread_mutex_unlock((mtx+next(n)));
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t tid[THRNUM];
    int err;
    int i;
    struct bucket_char_st tbf_bucket[THRNUM];

    for (int i = 0; i < THRNUM; i++)
    {
        tbf_bucket[i].tbf = mytbf_init(CPS, BURST);
    }
    

    for (i = 0; i < THRNUM; i++)
    {
        int* n = malloc(sizeof(int));
        *n = i;

        pthread_mutex_init(mtx+i, NULL);
        
        pthread_mutex_lock(mtx+i);
        tbf_bucket[i].num = i;

        err = pthread_create(&tid[i], NULL, thread_func, (void*)&tbf_bucket[i]);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s", strerror(err));
            exit(1);
        }
    }
    pthread_mutex_unlock(mtx+0); // 解开打印A的那一把锁

    // alarm(3);

    for (int i = 0; i < THRNUM; i++)
    {
        mytbf_destroy(tbf_bucket[i].tbf);
    }

    for (int i = 0; i < THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}

