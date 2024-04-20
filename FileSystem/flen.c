#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static off_t flen(const char* fname);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        perror("too few args.\n");
        exit(1);
    }

    printf("%lld\n", (long long)flen(argv[1]));

    exit(0);
}

static off_t flen(const char* fname)
{
    struct stat statbuf;
    if(stat(fname, &statbuf) < 0)
    {
        perror("stat failed.");
        exit(1);
    }
    return statbuf.st_size;
}