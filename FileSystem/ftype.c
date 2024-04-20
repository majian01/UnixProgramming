#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int ftype(const char* fname)
{
    struct stat statbuf;
    if(stat(fname, &statbuf) < 0)
    {
        perror("stat()\n");
        exit(1);
    }

    char ret_type;
    if(S_ISREG(statbuf.st_mode))
    {
        ret_type = '-';
    }
    else if (S_ISDIR(statbuf.st_mode))
    {
        ret_type = 'd';
    }
    else if (S_ISCHR(statbuf.st_mode))
    {
        ret_type = 'c';
    }
    else if (S_ISBLK(statbuf.st_mode))
    {
        ret_type = 'b';
    }
    else if (S_ISFIFO(statbuf.st_mode))
    {
        ret_type = 'p';
    }
    else if (S_ISSOCK(statbuf.st_mode))
    {
        ret_type = 's';
    }
    else if (S_ISLNK(statbuf.st_mode))
    {
        ret_type = 'l';
    }
    else
    {
        perror("not a support file type.");
        exit(1);
    }
    return ret_type;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "too few args.\n");
        exit(1);
    }

    printf("%c\n", ftype(argv[1]));
    
    exit(0);
}
