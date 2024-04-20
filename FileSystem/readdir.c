#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#define PATH "/etc"

int main(int argc, char const *argv[])
{
    DIR* dir;
    struct dirent* dir_ret; 
    

    dir = opendir(PATH);
    if (dir == NULL)
    {
        perror("open dir failed.");
        exit(1);
    }
    
    while ((dir_ret = readdir(dir)) != NULL)
    {
        puts(dir_ret->d_name);
    }

    closedir(dir);
    return 0;
}
