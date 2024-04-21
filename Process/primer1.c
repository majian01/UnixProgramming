#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>

#define LEFT  30000000
#define RIGHT 30000200


int main(int argc, char const *argv[])
{
    pid_t pid;
    for (int32_t i = LEFT; i < RIGHT; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }

        if (pid == 0)
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
                printf("%d is a primer\n", i);
            }

            // sleep(100);
            exit(0);
        }
    }
    // sleep(100);
    return 0;
}
