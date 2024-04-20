/**
 * @file mydate.c
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
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define TIMESIZE 1024
#define FMTSIZE 1024

int main(int argc, char *argv[])
{
    time_t stamp;
    stamp = time(NULL);
    char timestr[TIMESIZE];
    char fmtstr[FMTSIZE];
    int c;
    FILE* fp;

    fmtstr[0] = '\0';

    if(stamp == (time_t)-1)
    {
        perror("time() failed.");
        exit(1);
    }
    struct tm* tm;
    tm = localtime(&stamp);

    while (1)
    {
        c = getopt(argc, argv, "-H:MSy:md");  //需要带参数的加上冒号
        if (c < 0)
        {
            break;
        }

        switch (c)
        {
        case 'H':
            if (strcmp(optarg, "12") == 0)
            {
                strncat(fmtstr, "%I(%P) ", FMTSIZE);
            }
            else if (strcmp(optarg, "24") == 0)
            {
                strncat(fmtstr, "%H ", FMTSIZE);
            }
            else
            {
                fprintf(stderr, "invalid argument H!\n");
                exit(1);
            }
            break;
        case 'M':
            strncat(fmtstr, "%M ", FMTSIZE);
            break;
        case 'S':
            strncat(fmtstr, "%S ", FMTSIZE);
            break;
        case 'y':
            if (strcmp(optarg, "2") == 0)
            {
                strncat(fmtstr, "%y ", FMTSIZE);
            }
            else if (strcmp(optarg, "4") == 0)
            {
                strncat(fmtstr, "%Y ", FMTSIZE);
            }
            else
            {
                fprintf(stderr, "invalid argument y!\n");
                exit(1);
            }
            break;
        case 'm':
            strncat(fmtstr, "%m ", FMTSIZE);
            break;
        case 'd':
            strncat(fmtstr, "%d ", FMTSIZE);
            break;
        case 1:
            if ((fp = fopen(argv[optind-1], "w")) == NULL)
            {
                perror("fopen failed.");
                fp = stdout;
            }
            break;
        default:
            break;
        }
        
    }

    strftime(timestr, TIMESIZE, fmtstr, tm);
    strncat(timestr, "\n", FMTSIZE);
    fputs(timestr, fp);
    if (fp != stdout)
    {
        fclose(fp);
    }

    return 0;
}

