#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TIMELOG "time_log"
#define BUFSIZE 1024


//使用库函数实现

int main(int argc, char const *argv[])
{
    FILE* file;
    char buf[BUFSIZE];
    int line_count = 0;
    file = fopen(TIMELOG, "a+");
    if (file == NULL)
    {
        perror("fopen failed.");
        exit(1);
    }
    rewind(file);
    while (fgets(buf, BUFSIZE, file) != NULL)
    {
        line_count++;
    }

    time_t stamp;
    struct tm* current_time;

    while (1)
    {
        time(&stamp);
        current_time = localtime(&stamp);
        // fprintf(file, "%-4d%d-%d-%d %d:%d:%d\n", ++line_count, current_time->tm_year + 1900, current_time->tm_mon + 1, current_time->tm_mday \
        //                                     , current_time->tm_hour, current_time->tm_min, current_time->tm_sec);  // 实现1
        strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", current_time); // 实现2
        fprintf(file, "%-4d%s", ++line_count, buf);
        fflush(file);
        sleep(1);
    }

    fclose(file);
    
    return 0;
}
