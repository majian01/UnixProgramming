#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    pid_t pid;

    printf("begin.\n");

    fflush(NULL);   //非常重要  终端是行缓冲  文件是全缓冲

    pid = fork();

    if (pid < 0)
    {
        perror("fork error. ");
        exit(1);
    }

    if (pid == 0)
    {
        // sleep(1);
        printf("Im in child process. pid is %d.\n", getpid());
        printf("ppid is %d.\n", getppid());
    }
    else
    {
        printf("Im in parent process. pid is %d.\n", getpid());
    }
    
    // getchar();
    printf("end.\n");

    return 0;
}
