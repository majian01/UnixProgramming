#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define PATTERN "/etc/a*.conf"
#define PATTERN "*"

int errfunc_(const char* path, int num)
{
    puts(path);
    fprintf(stderr, "Error message:%s\n", strerror(num));
    return 0;
}

int main(int argc, char const *argv[])
{
    glob_t glob_ret;
    int err;
    err = glob(PATTERN, 0, errfunc_, &glob_ret);
    if (err)
    {
        printf("Error code is %d \n", err);
        exit(1);
    }

    for (int i = 0; i < glob_ret.gl_pathc; i++)
    {
        puts(glob_ret.gl_pathv[i]);
    }

    globfree(&glob_ret);
    
    return 0;
}
