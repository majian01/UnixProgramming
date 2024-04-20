#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glob.h>
#include <fcntl.h>
#include <string.h>

#define PATHSIZE 1024

static int path_noloop(const char* pathname)
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

static int64_t mydu(const char* path)
{
    struct stat statbuf;
    int64_t total_len = 0;
    char nextpath[PATHSIZE];
    
    if(lstat(path, &statbuf) < 0)
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
        glob_t glob_ret;
        int err;
        
        strncpy(nextpath, path, PATHSIZE);
        strncat(nextpath, "/*", PATHSIZE);
        // puts(nextpath);
        err = glob(nextpath, 0, NULL, &glob_ret);
        if(err == 1 || err == 2)
        {
            fprintf(stderr, "glob err.\n");
            exit(1);
        }

        strcpy(nextpath, path);
        strncat(nextpath, "/.*", PATHSIZE);
        err = glob(nextpath, GLOB_APPEND, NULL, &glob_ret);
        if(err == 1 || err == 2)
        {
            fprintf(stderr, "glob err.\n");
            exit(1);
        }

        for (int i = 0; i < glob_ret.gl_pathc; i++)
        {
            
            if (path_noloop(glob_ret.gl_pathv[i]))
            {
                total_len += mydu(glob_ret.gl_pathv[i]);
            }
        }

        total_len += statbuf.st_blocks; //当前目录大小

        globfree(&glob_ret);

    }

    return total_len;
}


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage ...\n");
        exit(1);
    }
    
    printf("%ld Kbits\n", mydu(argv[1]) / 2);

    return 0;
}
