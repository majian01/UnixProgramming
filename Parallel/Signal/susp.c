/**
 * @file susp.c
 * @author majian 
 * @brief 信号驱动程序
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


void star_signal(int sig)
{
    if (sig = SIGINT)
    {
        printf("get SIGINT\n");
    }
}

int main(int argc, char const *argv[])
{
    sigset_t set, old_set, save_set;

    signal(SIGINT, star_signal);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, &save_set); //进方法之前先要保存之前的信号处理状态
    sigprocmask(SIG_BLOCK, &set, &old_set);

    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            write(fileno(stdout), "*", 1);
            sleep(1);
        }
        write(fileno(stdout), "\n", 1);
        sigset_t tmpset;
        // sigprocmask(SIG_SETMASK, &old_set, &tmpset); 
        //由于sigprocmask和pause属于非原子的。
        //其中也存在多个中断，因此到pause时，中断不会打到pause上，不会唤醒程序
        // pause();
        // sigprocmask(SIG_SETMASK, &tmpset, NULL);

        sigsuspend(&old_set); //这句话相当于上面三句话的原子操作
    }
    sigprocmask(SIG_SETMASK, &save_set, NULL); //结束方法之前需要对信号进行恢复

    return 0;
}
