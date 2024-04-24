#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static int loop = 1;

static void alarm_handler(int sig)
{
    loop = 0;
}

int main(int argc, char const *argv[])
{
    int64_t count;
    alarm(5);
    signal(SIGALRM, alarm_handler);
    while (loop)
    {
        count++;
    }
    printf("%ld\n", count);
    
    return 0;
}
