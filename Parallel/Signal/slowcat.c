#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define CPS     10
#define MAXSIZE CPS

static volatile int loop = 0;

static void alarm_handler(int sig)
{
    alarm(1);
    loop = 1;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    int srcfd, desfd = 1;
    int read_len, write_len, pos;
    char buf[MAXSIZE];

    signal(SIGALRM, alarm_handler);
    alarm(1);

    srcfd = open(argv[1], O_RDONLY);

    while (1)
    {
        while (!loop)
        {
            pause();
        }
        loop = 0;

        while ((read_len = read(srcfd, buf, MAXSIZE)) < 0)
        {
            perror("read()");
            break;
        }

        if (read_len == 0)
        {
            printf("read none");
            break;
        }

        pos = 0;
        while (read_len > 0)
        {
            write_len = write(desfd, buf + pos, read_len);
            if (write_len < 0)
            {
                perror("write()");
                exit(1);
            }
            pos += write_len;
            read_len -= write_len;
        }
    }
    
    close(srcfd);
    return 0;
}
