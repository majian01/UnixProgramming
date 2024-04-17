#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    close(1);
    if (argc < 2)
    {
        perror("argc < 2");
        exit(1);
    }
    
    int srcfd;
    srcfd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600); // 默认打开最小的，所以打开的是1
    if (srcfd < 0)
    {
        perror("open fail.\n");
        exit(1);
    }

    puts("hello world.");
    return 0;
}
