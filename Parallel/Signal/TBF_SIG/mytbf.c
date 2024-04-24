#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>


#include "mytbf.h"
#define MYTBF_MAX  1024
// typedef void (*sighandler_t)(int);
struct sigaction sa_save;

struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
};

static struct mytbf_st* job[MYTBF_MAX];
static int inited = 0;

// static sighandler_t old_alarm_handler;

static int get_free_position()
{
    for (int i = 0; i < MYTBF_MAX; i++)
    {
        if (job[i] == NULL)
        {
            return i;
        }
    }
    
    return -1;
}

// static void alarm_handler(int sig)
static void alarm_action(int sig, siginfo_t* infop, void* unused)
{
    // alarm(1);

    if (infop->si_code != SI_KERNEL)
    {
        return;
    }

    for (int i = 0; i < TBF_MAX; i++)
    {
        if (job[i] != NULL)
        {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst)
            {
                job[i]->token = job[i]->burst;
            }
        }
    }
}

static void module_unload(void)
{
    // signal(SIGALRM, old_alarm_handler);
    // alarm(0);

    struct itimerval itv;

    if(sigaction(SIGALRM, &sa_save, NULL) < 0)
    {
        perror("sigaction():");
        exit(1);
    }

    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
    {
        perror("setitimer()");
        exit(1);
    }

    for (int i = 0; i < TBF_MAX; i++)
    {
        free(job[i]);
    }
}

static void module_load(void)
{
    struct itimerval itv;

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGALRM);
    sa.sa_sigaction = alarm_action;
    sa.sa_flags = SA_SIGINFO; //意味着使用sigaction取代sighandler

    if(sigaction(SIGALRM, &sa, &sa_save) < 0)
    {
        perror("sigaction():");
        exit(1);
    }

    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
    {
        perror("setitimer()");
        exit(1);
    }
    
    // old_alarm_handler = signal(SIGALRM, alarm_handler);
    // alarm(1);

    atexit(module_unload);
}

static int min(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st* me;
    int pos;

    if (inited == 0)
    {
        module_load();
        inited = 1;
    }
    

    pos = get_free_position();
    if (pos < 0)
    {
        return NULL;
    }

    me = malloc(sizeof(*me));
    if (me == NULL)
    {
        return NULL;
    }

    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    me->pos = pos;
    job[pos] = me;
    return me;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    struct mytbf_st* me = ptr;
    int n;

    if (size <= 0)
    {
        return -EINVAL;
    }
    
    while (me->token <= 0)
    {
        pause();
    }

    n = min(me->token, size);
    me->token -= n;
    return n;
}

int mytbf_returntoken(mytbf_t* ptr, int size)
{
    struct mytbf_st* me = ptr;

    if (size < 0)
    {
        return -EINVAL;
    }
    
    me->token += size;
    if (me->token > me->burst)
    {
        me->token = me->burst;
    }

    return size;
}

int mytbf_destroy(mytbf_t* ptr)
{
    struct mytbf_st* me = ptr;
    job[me->pos] = NULL;
}



