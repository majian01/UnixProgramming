#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

#define FILENAME "/tmp/out"

static int daemonlize(void)
{
    pid_t pid;
    int fd;

    pid = fork();
    if (pid < 0)
    {
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
    openlog("mydaemon", LOG_PID, LOG_DAEMON);

    if (daemonlize() < 0)
    {
        syslog(LOG_ERR, "daemonlize failed.");
        exit(EXIT_FAILURE);
    }
    else
    {
        syslog(LOG_INFO, "daemonlize successed.");
    }


    FILE* fp;
    fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        syslog(LOG_ERR, "fopen():%s ", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    int count = 1;
    while (1)
    {
        fprintf(fp, "%d\n", count++);
        fflush(fp);
        syslog(LOG_DEBUG, "%d is printed", count);
        sleep(1); // 每秒向文件写入一个数字
    }

    fclose(fp); //这里可以使用智能指针改进

    closelog();
    return 0;
}
