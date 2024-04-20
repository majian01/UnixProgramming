#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define PATHSIZE 1024

static int dir_noloop(const char* pathname)
{
    char* position;
    position = strrchr(pathname, '/');
    if (position == NULL)
    {
        exit(1);
    }

    if(strcmp(position + 1, ".") == 0 || strcmp(position + 1, "..") == 0)
    {
        return 0;
    }
    return 1;
}

int64_t mydu(const char* path)
{
    DIR* dir;
    struct stat statbuf;
    struct dirent* dir_ret;
    char nextpath[PATHSIZE];
    int64_t total_len = 0;

    if (lstat(path, &statbuf) < 0)
    {
        perror("lstat error:");
        exit(1);
    }

    if (!S_ISDIR(statbuf.st_mode))
    {
        return statbuf.st_blocks;
    }
    else
    {
        dir = opendir(path);
        
        if (dir == NULL)
        {
            // 这里可能会因为权限问题导致opendir failed, 使用sudo执行即可
            fprintf(stderr, "opendir failed.\n");
            exit(1);
        }
        while((dir_ret = readdir(dir)) != NULL)
        {
            strncpy(nextpath, path, PATHSIZE);
            strncat(nextpath, "/", PATHSIZE);
            strncat(nextpath, dir_ret->d_name, PATHSIZE);
            if (dir_noloop(nextpath))
            {
                // puts(nextpath);
                total_len += mydu(nextpath);
            }
        }

        total_len += statbuf.st_blocks;

        closedir(dir);
    }

    return total_len;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "too few args.\n");
        exit(1);
    }
    
    printf("%ld kbits\n", mydu(argv[1]) / 2);
    
    return 0;
}
