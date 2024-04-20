/**
 * @file 100day.c
 * @author majian
 * @brief 
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESIZE 1024

int main(int argc, char const *argv[])
{
    time_t stamp;
    stamp = time(NULL);
    char timestr[TIMESIZE];

    if(stamp == (time_t)-1)
    {
        perror("time() failed.");
        exit(1);
    }
    struct tm* tm;
    tm = localtime(&stamp);
    strftime(timestr, TIMESIZE, "Now: %Y-%m-%d", tm);
    puts(timestr);

    tm->tm_mday += 100;
    mktime(tm);
    strftime(timestr, TIMESIZE, "100days: %Y-%m-%d", tm);
    puts(timestr);
    
    return 0;
}

