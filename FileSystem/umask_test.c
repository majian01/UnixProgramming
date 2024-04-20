#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define RWRWRW (S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH)

int main(int argc, char const *argv[])
{
    umask(0);

    if (creat("Foo", RWRWRW) < 0)
    {
        perror("create file failed.\n");
        exit(1);
    }

    umask(S_IRGRP|S_IRGRP|S_IROTH|S_IWOTH);
    if (creat("Bar", RWRWRW) < 0)
    {
        perror("create file failed.\n");
        exit(1);
    }
    
    return 0;
}
