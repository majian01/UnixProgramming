#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        perror("argc < 2");
        exit(1);
    }
    
    int srcfd;
    srcfd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if (srcfd < 0)
    {
        perror("dup fail.\n");
        exit(1);
    }
    dup2(srcfd, 1);

    puts("hello world.");
    return 0;
}
