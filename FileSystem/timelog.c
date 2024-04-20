#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define TIMELOG "time_log"
#define BUFSIZE 1024

// 使用系统调用实现

void count_line(int fd, int* line_count)
{
    char sigle_char;
    while (read(fd, &sigle_char, 1) > 0)
    {
        if (sigle_char == '\n')
        {
            (*line_count)++;
        }
    }
}

int main(int argc, char const *argv[])
{
    int fd;
    char buf[BUFSIZE];
    char linebuf[BUFSIZE];
    fd = open(TIMELOG, O_RDWR|O_CREAT|O_APPEND, 0600);
    if (fd < 0)
    {
        perror("open failed:");
        exit(1);
    }

    int line_count = 0;
    count_line(fd, &line_count);

    time_t current_time;
    struct tm* tm;
    
    while (1)
    {
        time(&current_time);
        tm = localtime(&current_time);
        strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tm);
        sprintf(linebuf, "%-4d%s", ++line_count, buf);
        write(fd, linebuf, strlen(linebuf));
        sleep(1);
    }
    
    close(fd);
    
    return 0;
}
