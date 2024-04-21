#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "/tmp/out"

static int daemonlize(void)
{
    pid_t pid;
    int fd;

    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        return -1;
    }

    if (pid > 0)
    {
        exit(0);
    }

    // 子进程继续执行
    fd = open("/dev/null", O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2)
    {
        close(fd);
    }

    setsid();
    chdir("/");

    return 0;
}

int main(int argc, char const *argv[])
{
    if (daemonlize() < 0)
    {
        fprintf(stderr, "Failed to daemonlize.\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp;
    fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    int count = 1;
    while (1)
    {
        fprintf(fp, "%d\n", count++);
        fflush(fp);
        sleep(1); // 每秒向文件写入一个数字
    }

    fclose(fp);
    return 0;
}
