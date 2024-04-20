#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        perror("too few args.\n");
        exit(1);
    }

    int fd;
    fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open()\n");
        exit(1);
    }

    lseek(fd, 5LL*1024LL*1024LL*1024LL-1LL, SEEK_SET);
    if (errno != 0)
    {
        perror("lseek()\n");
        exit(1);
    }

    write(fd, " ", 1);

    close(fd);

    exit(0);
}
