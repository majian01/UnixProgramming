#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEFT  30000000
#define RIGHT 30000200
#define N     3


int main(int argc, char const *argv[])
{
    pid_t pid;

    for (int n = 0; n < N; n++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        
        if (pid == 0)
        {
            for (int32_t i = LEFT + n; i < RIGHT; i+=N)
            {
                int mark = 1;
                for (int32_t j = 2; j < i / 2; j++)
                {
                    if (i % j == 0)
                    {
                        mark = 0;
                        break;
                    }
                }
                if (mark == 1)
                {
                    printf("%d[%d] is a primer\n", i, n);
                }
            }
            exit(0);
        }
    }

    int st;
    for (int n = 0; n < N; n++)
    {
        wait(NULL);
    }
    
    return 0;
}
