#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char const *argv[])
{

    int line_count = 1;
    char buf[BUFSIZE];

    int srcfd, desfd;
    int bytes_read;

    if (argc < 3)
    {
        perror("too few args.\n");
        exit(1);
    }

    srcfd = open(argv[1], O_RDONLY);
    desfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0601);

    while ((bytes_read = read(srcfd, buf, BUFSIZE)) != 0)
    {
        for (int i = 0; i < bytes_read; i++)
        {
            if (buf[i] == '\n')
            {
                line_count++;
            }

            if (line_count != 10)
            {
                write(desfd, &buf[i], 1);
            }
        }
    }

    close(srcfd);
    close(desfd);

    return 0;
}
