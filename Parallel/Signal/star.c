#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

void star_signal(int sig)
{
    if (sig = SIGINT)
    {
        printf("get SIGINT\n");
    }
}

int main(int argc, char const *argv[])
{

    // signal(SIGINT, star_signal);
    signal(SIGINT, SIG_IGN);

    for (int i = 0; i < 10; i++)
    {
        write(fileno(stdout), "*", 1);
        sleep(1);
    }
    
    return 0;
}
