#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 1024

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    int srcfd, desfd;
    int read_len, write_len;
    char buf[MAXSIZE];

    srcfd = open(argv[1], O_RDONLY);
    desfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);

    while (1)
    {
        read_len = read(srcfd, buf, MAXSIZE);
        if (read_len < 0)
        {
            perror("read()");
            break;
        }
        else if (read_len == 0)
        {
            printf("read null");
            break;
        }
        
        write_len = write(desfd, buf, read_len);
        if (write_len < 0)
        {
            perror("write()");
        }
    }
    
    close(srcfd);
    close(desfd);
    return 0;
}
