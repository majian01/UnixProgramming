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

    for (int j = 0; j < 1000; j++)
    {
        sigprocmask(SIG_BLOCK, &set, NULL);
        for (int i = 0; i < 5; i++)
        {
            write(fileno(stdout), "*", 1);
            sleep(1);
        }
        write(fileno(stdout), "\n", 1);
        sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
    sigprocmask(SIG_SETMASK, &save_set, NULL); //结束方法之前需要对信号进行恢复

    return 0;
}
