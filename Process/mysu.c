#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "too few args.");
        exit(1);
    }

    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0)
    {
        setuid(atoi(argv[1]));
        execvp(argv[2], argv + 2);
        perror("exec()");
        exit(1);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
