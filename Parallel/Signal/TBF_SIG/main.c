#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "mytbf.h"

#define CPS     10
#define MAXSIZE 1024 
#define BURST   100

static volatile int token = 0;

int main(int argc, char const *argv[])
{
    struct mytbf_st* tbf;
    if (argc < 2)
    {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    int srcfd, desfd = 1;
    int read_len, write_len, pos;
    char buf[MAXSIZE];
    int size;

    srcfd = open(argv[1], O_RDONLY);

    tbf = mytbf_init(CPS, BURST);
    if (tbf == NULL)
    {
        fprintf(stderr, "tbf init failed.");
        exit(1);
    }
    
    while (1)
    {
        size = mytbf_fetchtoken(tbf, MAXSIZE);
        if (size < 0)
        {
            fprintf(stderr, "fetch token failed:%s\n", strerror(-size));
            exit(1);
        }

        while ((read_len = read(srcfd, buf, size)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            perror("read()");
            exit(1);
        }

        if (read_len == 0)
        {
            printf("read none");
            break;
        }

        if (size - read_len > 0)
        {
            mytbf_returntoken(tbf, size - read_len);
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
    
    mytbf_destroy(tbf);
    close(srcfd);
    return 0;
}
