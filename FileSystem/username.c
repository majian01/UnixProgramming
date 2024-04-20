#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

// by using userid and return user name

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "too few args.\n");
        exit(1);
    }

    struct passwd* pass_ret;
    pass_ret = getpwuid(atoi(argv[1]));

    puts(pass_ret->pw_name);
    
    return 0;
}
