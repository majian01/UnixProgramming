#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>


int main(int argc, char const *argv[])
{
    pid_t pid;
    puts("begin.\n");
    fflush(NULL);

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        execl("/bin/date", "date", "+%s", NULL);
    }

    wait(NULL);

    puts("end.\n");
    
    return 0;
}
